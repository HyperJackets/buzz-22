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

    //These methods control hardware.
    void load(void);
    void launch(void);
    void brake(void);
    void crawl(void);

    void step(void); //checks its state machine's state, and calls one of the 4 methods as appropriate
};
#endif