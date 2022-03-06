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

    //check other conditions
    assert(!pSM->fault());
    assert(!pSM->causeForConcern());
}

int main(int, char**) {
    std::cout << "----------Testing State Machine----------" << std::endl;

    CStateMachine* mySM1 = new CStateMachine();
    //NOTE: Instead of printing, I should use asserts to check if conditions are what we expect.
    initialCheck(mySM1);
    std::cout << "Going through control system" << std::endl;
    mySM1->goThroughControlSystem();

    std::cout << "----------Done testing----------" << std::endl;
}
