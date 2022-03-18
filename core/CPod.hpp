#pragma once
#ifndef C_POD_HPP
#define C_POD_HPP

#include "CStateMachine.hpp"

//This class simulates the pod, and has method skeletons that actually make the pod move and go through its various stages.
class CPod
{
private:
    CStateMachine* m_pStateMachine = new CStateMachine();

public:
    //get methods
    CStateMachine* getStateMachine(void) {return this->m_pStateMachine;}

    //These methods control hardware that deal with batteries, motors, braking, propulsion, etc. We should get in touch with the hardware people and VD/aero about the exact implementation.
    void load(void);
    void launch(void);
    void brake(void);
    void crawl(void);

    //This method checks the pod's state machine's state, and calls one of the 4 methods as appropriate.
    void step(void); 
};
#endif