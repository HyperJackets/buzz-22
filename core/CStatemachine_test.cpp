#include "CPod.hpp"
#include "gtest/gtest.h"
#include <iostream>

void initialCheck(CStateMachine *pSM) {
  // check numerical data
  EXPECT_EQ(pSM->getVelocity(), 0);
  EXPECT_EQ(pSM->getAccel(), 0);
  EXPECT_EQ(pSM->getBatteryTemp(), 50);
  EXPECT_EQ(pSM->getMotorTemp(), 50);
  EXPECT_EQ(pSM->getCurrentDist(), 0);

  // check states and engagements
  EXPECT_EQ(pSM->getHealth(), true);
  EXPECT_EQ(pSM->getLocalizationHealth(), true);
  EXPECT_EQ(!pSM->getBrakeEngagement(), true);
  EXPECT_EQ(!pSM->getMotorEngagement(), true);
  EXPECT_EQ(!pSM->getLocalizationEngagement(), true);
  EXPECT_EQ(pSM->getBMSEngagement(), true);
  EXPECT_EQ(pSM->getCommunicationsEngagement(), true);
  EXPECT_EQ(pSM->getCurrState(), UNLOADED);
}

// This method asserts that the pod's current state is UNLOADED.
void assertUnloaded(CStateMachine *pSM) {
  EXPECT_EQ(pSM->getCurrState(), UNLOADED);
  EXPECT_EQ(pSM->getBrakeEngagement(), false);
  EXPECT_EQ(pSM->getMotorEngagement(), false);
  EXPECT_EQ(pSM->getLocalizationEngagement(), false);
  EXPECT_EQ(pSM->getBMSEngagement(), true);
  EXPECT_EQ(pSM->getCommunicationsEngagement(), true);
}

// This method asserts that the pod's current state is LOADED.
void assertLoaded(CStateMachine *pSM) {
  EXPECT_EQ(pSM->getCurrState(), LOADED);
  EXPECT_EQ(pSM->getBrakeEngagement(), false);
  EXPECT_EQ(pSM->getMotorEngagement(), false);
  EXPECT_EQ(pSM->getLocalizationEngagement(), false);
  EXPECT_EQ(pSM->getBMSEngagement(), false);
  EXPECT_EQ(pSM->getCommunicationsEngagement(), true);
}

// This method asserts that the pod's current state is SAFE_TO_APPROACH.
void assertSafeToApproach(CStateMachine *pSM) {
  EXPECT_EQ(pSM->getCurrState(), SAFE_TO_APPROACH);
  EXPECT_EQ(pSM->getBrakeEngagement(), false);
  EXPECT_EQ(pSM->getMotorEngagement(), false);
  EXPECT_EQ(pSM->getLocalizationEngagement(), true);
  EXPECT_EQ(pSM->getBMSEngagement(), true);
  EXPECT_EQ(pSM->getCommunicationsEngagement(), true);
}

// This method asserts that the pod's current state is READY_TO_LAUNCH.
void assertReadyToLaunch(CStateMachine *pSM) {
  EXPECT_EQ(pSM->getCurrState(), READY_TO_LAUNCH);
  EXPECT_EQ(pSM->getBrakeEngagement(), false);
  EXPECT_EQ(pSM->getMotorEngagement(), false);
  EXPECT_EQ(pSM->getLocalizationEngagement(), true);
  EXPECT_EQ(pSM->getBMSEngagement(), true);
  EXPECT_EQ(pSM->getCommunicationsEngagement(), true);
}

// This method asserts that the pod's current state is LAUNCHING.
void assertLaunching(CStateMachine *pSM) {
  EXPECT_EQ(pSM->getCurrState(), LAUNCHING);
  EXPECT_EQ(pSM->getBrakeEngagement(), false);
  EXPECT_EQ(pSM->getMotorEngagement(), true);
  EXPECT_EQ(pSM->getLocalizationEngagement(), true);
  EXPECT_EQ(pSM->getBMSEngagement(), true);
  EXPECT_EQ(pSM->getCommunicationsEngagement(), true);
}

// This method asserts that the pod's current state is BREAKING.
void assertBraking(CStateMachine *pSM) {
  EXPECT_EQ(pSM->getCurrState(), BRAKING);
  EXPECT_EQ(pSM->getBrakeEngagement(), true);
  EXPECT_EQ(pSM->getMotorEngagement(), false);
  EXPECT_EQ(pSM->getLocalizationEngagement(), true);
  EXPECT_EQ(pSM->getBMSEngagement(), true);
  EXPECT_EQ(pSM->getCommunicationsEngagement(), true);
}

// This method asserts that the pod's current state is CRAWLING.
void assertCrawling(CStateMachine *pSM) {
  EXPECT_EQ(pSM->getCurrState(), CRAWLING);
  EXPECT_EQ(pSM->getBrakeEngagement(), false);
  EXPECT_EQ(pSM->getMotorEngagement(), true);
  EXPECT_EQ(pSM->getLocalizationEngagement(), true);
  EXPECT_EQ(pSM->getBMSEngagement(), true);
  EXPECT_EQ(pSM->getCommunicationsEngagement(), true);
}

// This method asserts that the pod's current state is FAULT.
void assertFault(CStateMachine *pSM) {
  EXPECT_EQ(pSM->getCurrState(), FAULT);
  EXPECT_EQ(pSM->getBrakeEngagement(), true);
  EXPECT_EQ(pSM->getMotorEngagement(), false);
  EXPECT_EQ(pSM->getLocalizationEngagement(), true);
  EXPECT_EQ(pSM->getBMSEngagement(), true);
  EXPECT_EQ(pSM->getCommunicationsEngagement(), true);
}

// This method simulates the pod being in all good condition.
TEST(PodHealth, HealthyCycle) {
  CStateMachine *pSM = new CStateMachine();
  assertUnloaded(pSM);

  pSM->step();
  pSM->setIsUnloaded(false); // This simulates the GUI setting the state to
                             // loaded (i.e. no longer unloaded).
  assertLoaded(pSM);

  pSM->step();
  assertSafeToApproach(pSM);

  pSM->step();
  assertReadyToLaunch(pSM);

  pSM->step();
  pSM->setIsReadyToLaunch(
      true); // This simulates the GUI setting the state to ready to launch.
  assertLaunching(pSM);

  pSM->setVelocity(15);
  pSM->setAccel(3);
  pSM->setCurrentDist(70);

  pSM->step();
  assertBraking(pSM);

  pSM->step();
  assertCrawling(pSM);
}

// This method simulates the pod having a health fault, which should transition
// its state to FAULT.
TEST(PodHealth, ExpectFault) {
  CStateMachine *pSM = new CStateMachine();
  assertUnloaded(pSM);

  pSM->step();
  pSM->setIsUnloaded(false); // This simulates the GUI setting the state to
                             // loaded (i.e. no longer unloaded).
  assertLoaded(pSM);

  pSM->step();
  assertSafeToApproach(pSM);

  pSM->step();
  assertReadyToLaunch(pSM);

  pSM->step();
  pSM->setIsReadyToLaunch(
      true); // This simulates the GUI setting the state to ready to launch.
  assertLaunching(pSM);

  pSM->setVelocity(15);
  pSM->setAccel(3);
  pSM->setCurrentDist(60);
  pSM->setHealth(false);
  EXPECT_EQ(pSM->isHealthy(), false);
  pSM->step();
  assertFault(pSM);
}

// This method simulates the pod having a temperature fault, which should
// transition its state to FAULT.
TEST(PodHealth, TemperatureFault) {
  CStateMachine *pSM = new CStateMachine();
  assertUnloaded(pSM);

  pSM->step();
  pSM->setIsUnloaded(false); // This simulates the GUI setting the state to
                             // loaded (i.e. no longer unloaded).
  assertLoaded(pSM);

  pSM->step();
  assertSafeToApproach(pSM);

  pSM->step();
  assertReadyToLaunch(pSM);

  pSM->setBatteryTemp(103);
  EXPECT_EQ(pSM->temperatureCheck(), false);
  pSM->step();
  assertFault(pSM);
}

// This method simulates the pod having a distance fault, which should
// transition its state to FAULT.
TEST(PodHealth, DistanceFault) {
  CStateMachine *pSM = new CStateMachine();
  assertUnloaded(pSM);

  pSM->step();
  pSM->setIsUnloaded(false); // This simulates the GUI setting the state to
                             // loaded (i.e. no longer unloaded).
  assertLoaded(pSM);

  pSM->step();
  assertSafeToApproach(pSM);

  pSM->step();
  assertReadyToLaunch(pSM);

  pSM->step();
  pSM->setIsReadyToLaunch(
      true); // This simulates the GUI setting the state to ready to launch.
  assertLaunching(pSM);

  pSM->setVelocity(15);
  pSM->setAccel(3);
  pSM->setCurrentDist(175);
  pSM->step();
  assertFault(pSM);
}

// This method simulates the pod transitioning from LOADED to CRAWLING.
TEST(PodState, LoadedToCrawling) {
  CStateMachine *pSM = new CStateMachine();
  assertUnloaded(pSM);

  std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
  pSM->step();
  pSM->setIsUnloaded(false); // This simulates the GUI setting the state to
                             // loaded (i.e. no longer unloaded).
  assertLoaded(pSM);

  pSM->setCurrentDist(151);
  pSM->step();
  assertCrawling(pSM);
}

// This method simulates the pod transitioning from LOADED to BREAKING.
TEST(PodState, LoadedToBreaking) {
  CStateMachine *pSM = new CStateMachine();
  assertUnloaded(pSM);

  pSM->step();
  pSM->setIsUnloaded(false); // This simulates the GUI setting the state to
                             // loaded (i.e. no longer unloaded).
  assertLoaded(pSM);

  pSM->setCurrentDist(150);
  pSM->step();
  assertBraking(pSM);
}

TEST(PodState, StartUnloaded) {
  CPod *pPod = new CPod();
  assertUnloaded(pPod->getStateMachine());
}
