#include "C:\SEAN\HyperJackets\buzz-22\core\src\CStateMachine.hpp"
#include <iostream>
#include <cassert>

void initialCheck(CStateMachine* pSM)
{
    assert(pSM->getVelocity() == 0);
    assert(pSM->getAccel() == 0);
    assert(pSM->getBatteryTemp() == 50);
    assert(pSM->getMotorTemp() == 50);
    assert(pSM->getCurrentDist() == 0);
    assert(pSM->getHealth());
    assert(pSM->getLocalizationHealth());
    assert(!pSM->getBreakEngagement());
    assert(!pSM->getMotorEngagement());
    assert(!pSM->getLocalizationEngagement());
    assert(pSM->getBMSEngagement());
    assert(pSM->getCommunicationsEngagement());
    assert(pSM->getCurrState() == UNLOADED);
}

void displayStatesAndEngagements(CStateMachine* pSM)
{
    
}

int main(int, char**) {
    std::cout << "----------Testing State Machine----------" << std::endl;
    CStateMachine* mySM1 = new CStateMachine();
    //NOTE: Instead of printing, I should use asserts to check if conditions are what we expect.
    //displayInfo(mySM1);
    initialCheck(mySM1);

    std::cout << "----------Done testing----------" << std::endl;
}
