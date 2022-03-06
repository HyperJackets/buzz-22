#pragma once
#include "CStateMachine.hpp"

//constructor
CStateMachine::CStateMachine() 
{
	//initialize numerical data
	this->m_fVelocity = 0;
	this->m_fAccel = 0;
	//These values might not be accurated and might need to be updated later.
	this->m_fBatteryTemp = 50; 
	this->m_fMotorTemp = 50;
	this->m_fCurrentDist = 0;

	//initialize states and engagements
	this->m_bHealth = true;
	this->m_bLocalizationHealth = true;
	this->m_bBreak = false;
	this->m_bMotor = false;
	this->m_bLocalization = false;
	this->m_bBMS = true;
	this->m_bCommunications = true;
	this->m_currState = UNLOADED;
}

//condition checks
bool CStateMachine::fault(void) const
{
	return this->getBreakEngagement() && !this->getMotorEngagement() && this->getLocalizationEngagement() && this->getBMSEngagement() && this->getCommunicationsEngagement();
}

bool CStateMachine::causeForConcern(void) const
{
	return this->getVelocity() != 0 || this->getAccel() != 0 || this->getBatteryTemp() >= THRESHOLD || this->getMotorTemp() >= THRESHOLD 
		|| this->getCurrentDist() != 0 || !this->getLocalizationHealth();
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

void CStateMachine::setState_safeToApproach(void)
{
	this->setLocalizationEngagement(true);
}

void CStateMachine::setState_launching(void)
{
	this->setMotorEngagement(true);
}

void CStateMachine::setState_breaking(void)
{
	this->setBreakEngagement(true);
	this->setMotorEngagement(false);
}

void CStateMachine::setState_crawling(void)
{
	this->setBreakEngagement(false);
	this->setMotorEngagement(true);
}

//This method goes through the various stages of the control system. 
void CStateMachine::step(void)
{
	if (this->getCurrState() == UNLOADED && !this->causeForConcern())
	{
		this->updateState(LOADED);
	}

	if (this->getCurrState() == LOADED && !this->causeForConcern())
	{
		this->updateState(SAFE_TO_APPROACH);
		//Manually set state to loaded via manual GUI control?
		//...
	}

	if (this->getCurrState() == SAFE_TO_APPROACH && !this->causeForConcern())
	{
		this->updateState(READY_TO_LAUNCH);
		this->setState_safeToApproach();
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
	if (!this->fault()) 
	{
		this->step();
	}
	// while (!this->fault() && !this->causeForConcern())
	// {
	// 	this->step();
	// }
}