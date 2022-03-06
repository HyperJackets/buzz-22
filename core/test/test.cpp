#include "C:\SEAN\HyperJackets\buzz-22\core\src\CStateMachine.hpp"
#include <iostream>

void displayInfo(CStateMachine* pSM)
{
    std::cout << "Current velocity is " << pSM->getVelocity() << std::endl;
    std::cout << "Current acceleration is " << pSM->getAccel() << std::endl;
    std::cout << "Current battery temp is " << pSM->getBatteryTemp() << std::endl;
    std::cout << "Current motor temp is " << pSM->getMotorTemp() << std::endl;
    std::cout << "Current distance is " << pSM->getCurrentDist() << std::endl;
}

void displayStatesAndEngagements(CStateMachine* pSM)
{
    
}

int main(int, char**) {
    std::cout << "----------Testing State Machine----------" << std::endl;
    CStateMachine* mySM1 = new CStateMachine();
    //NOTE: Instead of printing, I should use asserts to check if conditions are what we expect.
    displayInfo(mySM1);
    std::cout << "----------Done testing----------" << std::endl;
}
