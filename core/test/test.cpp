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
    CStateMachine* pSM = new CStateMachine();
    assert(pSM->getCurrState() == UNLOADED);

    std::cout << "Transition from UNLOADED to LOADED:" << std::endl;
    pSM->step();
    pSM->setIsUnloaded(false); //This simulates the GUI setting the state to loaded (i.e. no longer unloaded).
    assert(pSM->getCurrState() == LOADED);

    std::cout << "Transition from LOADED to SAFE_TO_APPROACH:" << std::endl;
    pSM->step();
    assert(pSM->getCurrState() == SAFE_TO_APPROACH);
    assert(pSM->getLocalizationEngagement());

    std::cout << "Transition from SAFE_TO_APPROACH to READY_TO_LAUNCH:" << std::endl;
    pSM->step();
    assert(pSM->getCurrState() == READY_TO_LAUNCH);

    std::cout << "Transition from READY_TO_LAUNCH to LAUNCHING:" << std::endl;
    pSM->step();
    pSM->setIsReadyToLaunch(true); //This simulates the GUI setting the state to ready to launch.
    //assert(pSM->getCurrState() == LAUNCHING);
    std::cout << pSM->getCurrState() << std::endl;
    assert(pSM->getMotorEngagement());

}

int main(int, char**) {
    std::cout << "----------Testing State Machine----------" << std::endl;

    // CStateMachine* mySM1 = new CStateMachine();
    // //NOTE: Instead of printing, I should use asserts to check if conditions are what we expect.
    // initialCheck(mySM1);
    std::cout << "Going through control system" << std::endl;

    //Step once, and make sure that all variables are what we EXPECT to see. Also change boolean GUI variables and numerical data.
    testAllGood();

    std::cout << "----------Done testing----------" << std::endl;
}
