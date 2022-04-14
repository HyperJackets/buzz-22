#include "pod.h"

// Note that the following methods (load, launch, brake, crawl) will only be
// called by CPod's step method when its state machine is in certain states.
// Here we will have code that works with the hardware, motor, braking,
// propulsion, etc.
void Pod::load(void) { this->getStateMachine()->step(); }

void Pod::launch(void) { this->getStateMachine()->step(); }

void Pod::brake(void) { this->getStateMachine()->step(); }

void Pod::crawl(void) { this->getStateMachine()->step(); }

void Pod::step(void) {
  if (this->getStateMachine()->getCurrState() == UNLOADED) {
    this->load();
  } else if (this->getStateMachine()->getCurrState() == READY_TO_LAUNCH) {
    this->launch();
  } else if (this->getStateMachine()->getCurrState() == LAUNCHING) {
    this->brake();
  } else if (this->getStateMachine()->getCurrState() == BRAKING) {
    this->crawl();
  }
}
