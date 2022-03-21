package main

import (
	"context"
	"log"
	"net"

	pb "github.com/HyperJackets/buzz-22/networking/PODProto"
	"google.golang.org/grpc"
)

type PODServer struct {
	pb.UnimplementedPODTelemetryServer
}

func (p *PODServer) PODPacketRequest(ctx context.Context, ack *pb.Ack) (*pb.PODPacket, error) {
	log.Println("Sending empty packet request!")
	return &pb.PODPacket{}, nil
}

func main() {
	lis, err := net.Listen("tcp", ":8000")
	if err != nil {
		log.Fatalf("Failed to listen on port 8000: %v", err)
	}

	s := grpc.NewServer()

	pb.RegisterPODTelemetryServer(s, &PODServer{})

	if err := s.Serve(lis); err != nil {
		log.Fatalf("Failed to serve gRPC server over port 8000: %v", err)
	}
}
