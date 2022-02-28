#pragma once
#include "CStateMachine.hpp"

//constructor
CStateMachine::CStateMachine() 
{
	this->m_fVelocity = 0;
	this->m_fAccel = 0;
	//These values might not be accurated and might need to be updated later.
	this->m_fBatteryTemp = 50; 
	this->m_fMotorTemp = 50;
	this->m_fCurrentDist = 0;
	this->m_currState = UNLOADED;
}

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

void CStateMachine::step(void)
{
	if (this->getCurrState() == LOADED)
	{
		this->updateState(SAFE_TO_APPROACH);
		//...
	}

	if (this->getCurrState() == SAFE_TO_APPROACH)
	{
		this->updateState(READY_TO_LAUNCH);
		//Manually launch the pod via manual GUI control.
		//...
	}

	if ((this->getCurrentDist() >= BREAK_DIST || this->getCurrentDist() == TRACK_DIST) && this->getCurrState() == LAUNCHING)
	{
		this->updateState(BREAKING);
		//...
	}

	if (this->getCurrentDist() < TRACK_DIST && this->getCurrState() == BREAKING)
	{
		this->updateState(CRAWLING);
		//...
	}
}

void CStateMachine::goThroughControlSystem(void)
{
	while (!this->fault() && !this->causeForConcern())
	{
		this->step();
	}
}