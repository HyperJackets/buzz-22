package main

import (
	"context"
	"log"
	"time"

	pb "github.com/HyperJackets/buzz-22/networking/PODProto"
	"google.golang.org/grpc"
)

const (
	address = "localhost:8000"
)

func main() {
	conn, err := grpc.Dial(address, grpc.WithInsecure(), grpc.WithBlock())

	if err != nil {
		log.Fatalf("got err triyng to dial conn: %v", err)
	}

	defer conn.Close()

	c := pb.NewPODTelemetryClient(conn)

	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	ack := pb.Ack{Status: pb.Ack_OK}
	response, err := c.PODPacketRequest(ctx, &ack)

	if err != nil {
		log.Fatalf("got error sending message: %v", err)
	}

	log.Printf("server response: %v", response)
}
