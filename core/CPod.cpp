#include "CPod.hpp"

// Note that the following methods (load, launch, brake, crawl) will only be
// called by CPod's step method when its state machine is in certain states.
// Here we will have code that works with the hardware, motor, braking,
// propulsion, etc.
void CPod::load(void) { this->getStateMachine()->step(); }

void CPod::launch(void) { this->getStateMachine()->step(); }

void CPod::brake(void) { this->getStateMachine()->step(); }

void CPod::crawl(void) { this->getStateMachine()->step(); }

void CPod::step(void) {
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
