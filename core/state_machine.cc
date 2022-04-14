#include "state_machine.h"

// constructor
StateMachine::StateMachine() {
  // initialize numerical data
  this->m_fVelocity = 0;
  this->m_fAccel = 0;
  // These values might not be accurated and might need to be updated later.
  this->m_fBatteryTemp = 50;
  this->m_fMotorTemp = 50;
  this->m_fCurrentDist = 0;

  // initialize states and engagements
  this->m_bHealth = true;
  this->m_bLocalizationHealth = true;
  this->m_bBrake = false;
  this->m_bMotor = false;
  this->m_bLocalization = false;
  this->m_bBMS = true;
  this->m_bCommunications = true;
  this->m_currState = UNLOADED;
}

// condition checks
void StateMachine::handleFault(void) {
  this->setBrakeEngagement(true);
  this->setMotorEngagement(false);
  this->setLocalizationEngagement(true);
  this->setBMSEngagement(true);
  this->setCommunicationsEngagement(true);
}

bool StateMachine::hasFinishedTrack(void) const {
  return this->getCurrentDist() > EXCEEDED_DIST;
}

bool StateMachine::isHealthy(void) const {
  return this->getHealth() && this->getLocalizationHealth();
}

bool StateMachine::isMoving(void) const {
  return this->getVelocity() != 0 || this->getAccel() != 0;
}

bool StateMachine::hasMoved(void) const { return this->getCurrentDist() != 0; }

bool StateMachine::temperatureCheck(void) const {
  return this->getBatteryTemp() < THRESHOLD && this->getMotorTemp() < THRESHOLD;
}

bool StateMachine::readyToLaunch(void) const {
  return !this->getBrakeEngagement() && !this->getMotorEngagement() &&
         this->getLocalizationEngagement() && this->getBMSEngagement() &&
         this->getCommunicationsEngagement();
}

bool StateMachine::launching(void) const {
  return !this->getBrakeEngagement() && this->getMotorEngagement() &&
         this->getLocalizationEngagement() && this->getBMSEngagement() &&
         this->getCommunicationsEngagement();
}

bool StateMachine::braking(void) const {
  return this->getBrakeEngagement() && !this->getMotorEngagement() &&
         this->getLocalizationEngagement() && this->getBMSEngagement() &&
         this->getCommunicationsEngagement();
}

// This method goes through the various stages of the control system.
void StateMachine::step(void) {
  // fault condition
  if (!this->isHealthy() || !this->temperatureCheck() ||
      this->hasFinishedTrack()) {
    this->updateState(FAULT);
    this->handleFault();
    return;
  } else if (this->getCurrState() == UNLOADED && this->isUnloaded()) {
    this->updateState(LOADED);
    // Manually set state to loaded via manual GUI control.
    //...
  } else if (this->getCurrState() == LOADED) {
    if (this->getCurrentDist() > TRACK_DIST) {
      this->updateState(CRAWLING);
      this->setMotorEngagement(true);
      this->setLocalizationEngagement(true);
    } else if (this->getCurrentDist() == TRACK_DIST) {
      this->updateState(BRAKING);
      this->setBrakeEngagement(true);
      this->setLocalizationEngagement(true);
    } else {
      this->updateState(SAFE_TO_APPROACH);
      this->setLocalizationEngagement(true);
    }
  } else if (this->getCurrState() == SAFE_TO_APPROACH && !this->isMoving()) {
    this->updateState(READY_TO_LAUNCH);
    //...
  } else if (this->getCurrState() == READY_TO_LAUNCH &&
             !this->isReadyToLaunch()) {
    this->updateState(LAUNCHING);
    this->setMotorEngagement(true);
    // Manually set state to launching via manual GUI control.
    //...
  } else if (this->getCurrState() == LAUNCHING &&
             (this->getCurrentDist() >= BREAK_DIST ||
              this->getCurrentDist() == TRACK_DIST)) {
    this->updateState(BRAKING);
    this->setBrakeEngagement(true);
    this->setMotorEngagement(false);
    //...
  } else if (this->getCurrState() == BRAKING &&
             this->getCurrentDist() < TRACK_DIST) {
    this->updateState(CRAWLING);
    this->setBrakeEngagement(false);
    this->setMotorEngagement(true);
    //...
    return;
  }
}

void StateMachine::goThroughControlSystem(void) {
  while (this->getCurrState() != FAULT) {
    this->step();
  }
}
