#pragma once
#ifndef POD_H
#define POD_H

#include "core/networking/POD.grpc.pb.h"
#include "state_machine.h"

// This class simulates the pod, and has method skeletons that actually make the
// pod move and go through its various stages.
class Pod {
private:
  StateMachine *m_pStateMachine = new StateMachine();

public:
  // get methods
  StateMachine *getStateMachine(void) { return this->m_pStateMachine; }

  // These methods control hardware that deal with batteries, motors, braking,
  // propulsion, etc. We should get in touch with the hardware people and
  // VD/aero about the exact implementation.
  void load(void);
  void launch(void);
  void brake(void);
  void crawl(void);

  void handle_packet(pod_networking::PODPacket *packet);

  // This method checks the pod's state machine's state, and calls one of
  // the 4 methods as appropriate.
  void step(void);
};
#endif
