#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "networking/POD.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using pod_networking::Ack;
using pod_networking::PODPacket;
using pod_networking::PODPacket_State;
using pod_networking::PODTelemetry;

class PODServiceImpl final : public PODTelemetry::Service {
  Status PODPacketRequest(ServerContext *context, const Ack *request,
                          PODPacket *response) override {
    std::cout << "Got packet request " << request->status() << std::endl;
    response->set_state(pod_networking::PODPacket_State_FAULT);
    return Status::OK;
  }
};

void RunServer() {
  std::string address = "0.0.0.0";
  std::string port = "8000";
  std::string server_address = address + ":" + port;

  PODServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char **argv) {
  RunServer();

  return 0;
}
