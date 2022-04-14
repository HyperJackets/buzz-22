#include "server.h"
#include "core/networking/POD.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <string>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using pod_networking::Ack;
using pod_networking::PODPacket;
using pod_networking::PODPacket_State;
using pod_networking::PODTelemetry;

class PODServiceImpl final : public PODTelemetry::Service {
public:
  bool is_pod_null() { return pod == nullptr; }
  void set_pod(Pod *pod) {
    if (!is_pod_null()) {
      std::cout << "[POD Server - WARNING] resolved pod reference was changed!"
                << std::endl;
    }

    this->pod = pod;
  }

private:
  Pod *pod;

  Status PODPacketRequest(ServerContext *context, const Ack *request,
                          PODPacket *response) override {
    if (is_pod_null())
      return Status(grpc::StatusCode::FAILED_PRECONDITION,
                    "CPod instance is null");

    // Our update was acknowledged to fault
    if (request->status() == Ack::FAULT) {
      pod->getStateMachine()->setHealth(false);
    }

    pod->handle_packet(response);

    return Status::OK;
  }
};

void runServer(Pod *pod) {
  std::string address = "0.0.0.0";
  std::string port = "8000";
  std::string server_address = address + ":" + port;

  PODServiceImpl service;
  service.set_pod(pod);

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}
