//
//#pragma once
#include "CStateMachine.hpp"


//added a test comment on line 5
// line 6 comment
//condition checks
bool CStateMachine::fault(void) const
{
	return !this->getHealth() || !this->getLocalizationHealth() || this->getBatteryTemp() >= THRESHOLD || this->getMotorTemp() >= THRESHOLD || this->getCurrentDist() >= TRACK_DIST;
}

bool CStateMachine::causeForConcern(void) const
{
	return this->getVelocity() != 0 || this->getAccel() != 0 || this->getBatteryTemp() >= THRESHOLD || this->getMotorTemp() >= THRESHOLD || this->getCurrentDist() != 0 || !this->getLocalizationHealth();
}

bool CStateMachine::readyToLaunch(void) const
{
	return !this->getBreakEngagement() && !this->getMotorEngagement() && this->getLocalizationEngagement() && this->getBMSEngagement() && this->getCommunicationsEngagement();
}

bool CStateMachine::launching(void) const
{
	return !this->getBreakEngagement() && this->getMotorEngagement() && this->getLocalizationEngagement() && this->getBMSEngagement() && this->getCommunicationsEngagement();
}

bool CStateMachine::breaking(void) const
{
	return this->getBreakEngagement() && !this->getMotorEngagement() && this->getLocalizationEngagement() && this->getBMSEngagement() && this->getCommunicationsEngagement();
}

<<<<<<< Updated upstream:core/CStateMachine.cpp
void CStateMachine::step(void)
{
	if (this->getCurrState() == LOADED)
=======
void CStateMachine::setState_safeToApproach(void)
{
	this->m_bLocalization = true;
}

void CStateMachine::setState_launching(void)
{
	this->m_bMotor = true;
}

void CStateMachine::setState_breaking(void)
{
	this->m_bBreak = true;
	this->m_bMotor = false;
}

void CStateMachine::setState_crawling(void)
{
	this->m_bBreak = false;
	this->m_bMotor = true;
}

//Note that we should only go through this method if the pod is NOT at fault.
void CStateMachine::step(void)
{
	if (this->getCurrState() == UNLOADED && !this->causeForConcern())
	{
		this->updateState(LOADED);
		//Manually transition the pod to loaded?
	}

	if (this->getCurrState() == LOADED && !this->causeForConcern())
>>>>>>> Stashed changes:core/src/CStateMachine.cpp
	{
		this->updateState(SAFE_TO_APPROACH);
		this->setState_safeToApproach();
		//...
	}

	if (this->getCurrState() == SAFE_TO_APPROACH)
	{
		this->updateState(READY_TO_LAUNCH);
		this->setState_launching();
		//Manually launch the pod via manual GUI control.
		//...
	}

	if ((this->getCurrentDist() >= BREAK_DIST || this->getCurrentDist() == TRACK_DIST) && this->getCurrState() == LAUNCHING)
	{
		this->updateState(BREAKING);
		this->setState_breaking();
		//...
	}

	if (this->getCurrentDist() < TRACK_DIST && this->getCurrState() == BREAKING)
	{
		this->updateState(CRAWLING);
		this->setState_crawling();
		//...
		return;
	}
}

void CStateMachine::goThroughControlSystem(void)
{
<<<<<<< Updated upstream:core/CStateMachine.cpp
	while (!this->fault() && !this->causeForConcern())
	{
		this->step();
	}
}
=======
	this->step();
	// while (!this->fault())
	// {
	// 	this->step();
	// }
}
>>>>>>> Stashed changes:core/src/CStateMachine.cpp
