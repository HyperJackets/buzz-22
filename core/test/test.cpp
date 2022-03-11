#include "C:\SEAN\HyperJackets\buzz-22\core\src\CStateMachine.hpp"
#include <iostream>
#include <cassert>

void initialCheck(CStateMachine* pSM)
{
    //check numerical data
    assert(pSM->getVelocity() == 0);
    assert(pSM->getAccel() == 0);
    assert(pSM->getBatteryTemp() == 50);
    assert(pSM->getMotorTemp() == 50);
    assert(pSM->getCurrentDist() == 0);

    //check states and engagements
    assert(pSM->getHealth());
    assert(pSM->getLocalizationHealth());
    assert(!pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(!pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());
    assert(pSM->getCurrState() == UNLOADED);
}

//This method asserts that the pod's current state is UNLOADED.
void assertUnloaded(CStateMachine* pSM)
{
    assert(pSM->getCurrState() == UNLOADED);
    assert(!pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(!pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());
}

//This method asserts that the pod's current state is LOADED.
void assertLoaded(CStateMachine* pSM)
{
    assert(pSM->getCurrState() == LOADED);
    assert(!pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(!pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());
}

//This method asserts that the pod's current state is SAFE_TO_APPROACH.
void assertSafeToApproach(CStateMachine* pSM)
{
    assert(pSM->getCurrState() == SAFE_TO_APPROACH);
    assert(!pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());
}

//This method asserts that the pod's current state is READY_TO_LAUNCH.
void assertReadyToLaunch(CStateMachine* pSM)
{
    assert(pSM->getCurrState() == READY_TO_LAUNCH);
    assert(!pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());
}

//This method asserts that the pod's current state is LAUNCHING.
void assertLaunching(CStateMachine* pSM)
{
    assert(pSM->getCurrState() == LAUNCHING);
    assert(!pSM->getBreakEngagement());
    assert(pSM->getMotorEngagement());
    assert(pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());
}

//This method asserts that the pod's current state is BREAKING.
void assertBreaking(CStateMachine* pSM)
{
    assert(pSM->getCurrState() == BREAKING);
    assert(pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());
}

//This method asserts that the pod's current state is CRAWLING.
void assertCrawling(CStateMachine* pSM)
{
    assert(pSM->getCurrState() == CRAWLING);
    assert(!pSM->getBreakEngagement());
    assert(pSM->getMotorEngagement());
    assert(pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());
}

//This method asserts that the pod's current state is FAULT.
void assertFault(CStateMachine* pSM)
{
    assert(pSM->getCurrState() == FAULT);
    assert(pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());
}

//This method simulates the pod being in all good condition.
void testAllGood()
{
    std::cout << "------Testing all good case------" << std::endl;
    
    CStateMachine* pSM = new CStateMachine();
    assertUnloaded(pSM);

    std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
    pSM->step();
    pSM->setIsUnloaded(false); //This simulates the GUI setting the state to loaded (i.e. no longer unloaded).
    assertLoaded(pSM);

    std::cout << "Transition from LOADED to SAFE_TO_APPROACH:" << std::endl;
    pSM->step();
    assertSafeToApproach(pSM);

    std::cout << "Transition from SAFE_TO_APPROACH to READY_TO_LAUNCH:" << std::endl;
    pSM->step();
    assertReadyToLaunch(pSM);

    std::cout << "Transition from READY_TO_LAUNCH to LAUNCHING:" << std::endl;
    pSM->step();
    pSM->setIsReadyToLaunch(true); //This simulates the GUI setting the state to ready to launch.
    assertLaunching(pSM);

    pSM->setVelocity(15);
    pSM->setAccel(3);
    pSM->setCurrentDist(70);

    std::cout << "Transition from LAUNCHING to BREAKING:" << std::endl;
    pSM->step();
    assertBreaking(pSM);

    std::cout << "Transition from BREAKING to CRAWLING:" << std::endl; 
    pSM->step();
    assertCrawling(pSM);

    std::cout << "------Done testing all good case------" << std::endl << std::endl;
}

//This method simulates the pod having a health fault, which should transition its state to FAULT.
void testHealthFault()
{
    std::cout << "------Testing health fault case------" << std::endl;

    CStateMachine* pSM = new CStateMachine();
    assertUnloaded(pSM);

    std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
    pSM->step();
    pSM->setIsUnloaded(false); //This simulates the GUI setting the state to loaded (i.e. no longer unloaded).
    assertLoaded(pSM);

    std::cout << "Transition from LOADED to SAFE_TO_APPROACH:" << std::endl;
    pSM->step();
    assertSafeToApproach(pSM);

    std::cout << "Transition from SAFE_TO_APPROACH to READY_TO_LAUNCH:" << std::endl;
    pSM->step();
    assertReadyToLaunch(pSM);

    std::cout << "Transition from READY_TO_LAUNCH to LAUNCHING:" << std::endl;
    pSM->step();
    pSM->setIsReadyToLaunch(true); //This simulates the GUI setting the state to ready to launch.
    assertLaunching(pSM);

    pSM->setVelocity(15);
    pSM->setAccel(3);
    pSM->setCurrentDist(60);
    pSM->setHealth(false);
    assert(!pSM->isHealthy());
    pSM->step();
    assertFault(pSM);

    std::cout << "------Done testing health fault case------" << std::endl << std::endl;
}

//This method simulates the pod having a temperature fault, which should transition its state to FAULT.
void testTempFault()
{
    std::cout << "------Testing temp fault case------" << std::endl;

    CStateMachine* pSM = new CStateMachine();
    assertUnloaded(pSM);

    std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
    pSM->step();
    pSM->setIsUnloaded(false); //This simulates the GUI setting the state to loaded (i.e. no longer unloaded).
    assertLoaded(pSM);

    std::cout << "Transition from LOADED to SAFE_TO_APPROACH:" << std::endl;
    pSM->step();
    assertSafeToApproach(pSM);

    std::cout << "Transition from SAFE_TO_APPROACH to READY_TO_LAUNCH:" << std::endl;
    pSM->step();
    assertReadyToLaunch(pSM);

    pSM->setBatteryTemp(103);
    assert(!pSM->temperatureCheck());
    pSM->step();
    assertFault(pSM);

    std::cout << "------Done testing temp fault case------" << std::endl << std::endl;
}

//This method simulates the pod having a distance fault, which should transition its state to FAULT.
void testDistFault()
{
    std::cout << "------Testing distance fault case------" << std::endl;

    CStateMachine* pSM = new CStateMachine();
    assertUnloaded(pSM);

    std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
    pSM->step();
    pSM->setIsUnloaded(false); //This simulates the GUI setting the state to loaded (i.e. no longer unloaded).
    assertLoaded(pSM);

    std::cout << "Transition from LOADED to SAFE_TO_APPROACH:" << std::endl;
    pSM->step();
    assertSafeToApproach(pSM);

    std::cout << "Transition from SAFE_TO_APPROACH to READY_TO_LAUNCH:" << std::endl;
    pSM->step();
    assertReadyToLaunch(pSM);

    std::cout << "Transition from READY_TO_LAUNCH to LAUNCHING:" << std::endl;
    pSM->step();
    pSM->setIsReadyToLaunch(true); //This simulates the GUI setting the state to ready to launch.
    assertLaunching(pSM);

    pSM->setVelocity(15);
    pSM->setAccel(3);
    pSM->setCurrentDist(175);
    pSM->step();
    assertFault(pSM);

    std::cout << "------Done testing distance fault case------" << std::endl << std::endl;
}

//This method simulates the pod transitioning from LOADED to CRAWLING.
void testTransitionFromLoadedToCrawling()
{
    std::cout << "------Testing transition from LOADED to CRAWLING case------" << std::endl;

    CStateMachine* pSM = new CStateMachine();
    assertUnloaded(pSM);

    std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
    pSM->step();
    pSM->setIsUnloaded(false); //This simulates the GUI setting the state to loaded (i.e. no longer unloaded).
    assertLoaded(pSM);

    pSM->setCurrentDist(151);
    std::cout << "Transition from LOADED to CRAWLING:" << std::endl;
    pSM->step();
    assertCrawling(pSM);
}



int main(int, char**) {
    std::cout << "----------Testing State Machine----------" << std::endl << std::endl;

    //NOTE: Instead of printing, I should use asserts to check if conditions are what we expect.

    //Step once, and make sure that all variables are what we EXPECT to see. Also manually change boolean GUI variables and numerical data.
    testAllGood();
    testHealthFault();
    testTempFault();
    testDistFault();
    testTransitionFromLoadedToCrawling();

    std::cout << "----------Done testing----------" << std::endl;
}
