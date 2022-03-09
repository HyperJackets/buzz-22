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

void testAllGood()
{
    std::cout << "------Testing all good case------" << std::endl;
    
    CStateMachine* pSM = new CStateMachine();
    assert(pSM->getCurrState() == UNLOADED);

    std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
    pSM->step();
    pSM->setIsUnloaded(false); //This simulates the GUI setting the state to loaded (i.e. no longer unloaded).
    assert(pSM->getCurrState() == LOADED);

    std::cout << "Transition from LOADED to SAFE_TO_APPROACH:" << std::endl;
    pSM->step();
    assert(pSM->getLocalizationEngagement());

    std::cout << "Transition from SAFE_TO_APPROACH to READY_TO_LAUNCH:" << std::endl;
    pSM->step();
    assert(pSM->getCurrState() == READY_TO_LAUNCH);

    std::cout << "Transition from READY_TO_LAUNCH to LAUNCHING:" << std::endl;
    pSM->step();
    pSM->setIsReadyToLaunch(true); //This simulates the GUI setting the state to ready to launch.
    assert(pSM->getCurrState() == LAUNCHING);
    assert(pSM->getMotorEngagement());

    pSM->setVelocity(15);
    pSM->setAccel(3);
    pSM->setCurrentDist(60);

    std::cout << "Transition from LAUNCHING to BREAKING:" << std::endl;
    pSM->step();
    assert(pSM->getCurrState() == BREAKING);
    assert(pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());

    std::cout << "Transition from BREAKING to CRAWLING:" << std::endl; 
    pSM->step();
    assert(pSM->getCurrState() == CRAWLING);
    assert(!pSM->getBreakEngagement());
    assert(pSM->getMotorEngagement());

    std::cout << "------Done testing all good case------" << std::endl << std::endl;
}

void testHealthFault()
{
    std::cout << "------Testing health fault case------" << std::endl;

    CStateMachine* pSM = new CStateMachine();
    assert(pSM->getCurrState() == UNLOADED);

    std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
    pSM->step();
    pSM->setIsUnloaded(false); //This simulates the GUI setting the state to loaded (i.e. no longer unloaded).
    assert(pSM->getCurrState() == LOADED);

    std::cout << "Transition from LOADED to SAFE_TO_APPROACH:" << std::endl;
    pSM->step();
    assert(pSM->getLocalizationEngagement());

    std::cout << "Transition from SAFE_TO_APPROACH to READY_TO_LAUNCH:" << std::endl;
    pSM->step();
    assert(pSM->getCurrState() == READY_TO_LAUNCH);

    std::cout << "Transition from READY_TO_LAUNCH to LAUNCHING:" << std::endl;
    pSM->step();
    pSM->setIsReadyToLaunch(true); //This simulates the GUI setting the state to ready to launch.
    assert(pSM->getCurrState() == LAUNCHING);
    assert(pSM->getMotorEngagement());

    pSM->setVelocity(15);
    pSM->setAccel(3);
    pSM->setCurrentDist(60);
    pSM->setHealth(false);
    assert(!pSM->isHealthy());
    pSM->step();
    assert(pSM->getCurrState() == FAULT);
    assert(pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());

    std::cout << "------Done testing health fault case------" << std::endl << std::endl;
}

void testTempFault()
{
    std::cout << "------Testing temp fault case------" << std::endl;

    CStateMachine* pSM = new CStateMachine();
    assert(pSM->getCurrState() == UNLOADED);

    std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
    pSM->step();
    pSM->setIsUnloaded(false); //This simulates the GUI setting the state to loaded (i.e. no longer unloaded).
    assert(pSM->getCurrState() == LOADED);

    std::cout << "Transition from LOADED to SAFE_TO_APPROACH:" << std::endl;
    pSM->step();
    assert(pSM->getLocalizationEngagement());

    std::cout << "Transition from SAFE_TO_APPROACH to READY_TO_LAUNCH:" << std::endl;
    pSM->step();
    assert(pSM->getCurrState() == READY_TO_LAUNCH);

    pSM->setBatteryTemp(103);
    assert(!pSM->temperatureCheck());
    pSM->step();
    assert(pSM->getCurrState() == FAULT);
    assert(pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());

    std::cout << "------Done testing temp fault case------" << std::endl << std::endl;
}

void testDistFault()
{
    std::cout << "------Testing distance fault case------" << std::endl;

    CStateMachine* pSM = new CStateMachine();
    assert(pSM->getCurrState() == UNLOADED);

    std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
    pSM->step();
    pSM->setIsUnloaded(false); //This simulates the GUI setting the state to loaded (i.e. no longer unloaded).
    assert(pSM->getCurrState() == LOADED);

    std::cout << "Transition from LOADED to SAFE_TO_APPROACH:" << std::endl;
    pSM->step();
    assert(pSM->getLocalizationEngagement());

    std::cout << "Transition from SAFE_TO_APPROACH to READY_TO_LAUNCH:" << std::endl;
    pSM->step();
    assert(pSM->getCurrState() == READY_TO_LAUNCH);

    std::cout << "Transition from READY_TO_LAUNCH to LAUNCHING:" << std::endl;
    pSM->step();
    pSM->setIsReadyToLaunch(true); //This simulates the GUI setting the state to ready to launch.
    assert(pSM->getCurrState() == LAUNCHING);
    assert(pSM->getMotorEngagement());

    pSM->setVelocity(15);
    pSM->setAccel(3);
    pSM->setCurrentDist(120);
    pSM->step();
    assert(pSM->getCurrState() == FAULT);
    assert(pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());

    std::cout << "------Done testing distance fault case------" << std::endl << std::endl;
}

int main(int, char**) {
    std::cout << "----------Testing State Machine----------" << std::endl << std::endl;

    //NOTE: Instead of printing, I should use asserts to check if conditions are what we expect.

    //Step once, and make sure that all variables are what we EXPECT to see. Also manually change boolean GUI variables and numerical data.
    testAllGood();
    testHealthFault();
    testTempFault();
    testDistFault();

    std::cout << "----------Done testing----------" << std::endl;
}
