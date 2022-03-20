package main

import (
	pod_pb "github.com/HyperJackets/buzz-22/proto"
)

type PODServer struct {
	pod_pb.UnimplementedPODTelemetryServer
}

func (p *PODServer) PODPacketRequest(ack *pod_pb.Ack) (*pod_pb.PODPacket, error) {
	return nil, nil
}

func main() {

}
