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
void CStateMachine::handleFault(void) 
{
	this->setBreakEngagement(true);
	this->setMotorEngagement(false);
	this->setLocalizationEngagement(true);
	this->setBMSEngagement(true);
	this->setCommunicationsEngagement(true);
}

bool CStateMachine::hasFinishedTrack(void) const
{
	return this->getCurrentDist() > EXCEEDED_DIST;
}

bool CStateMachine::isHealthy(void) const
{
	return this->getHealth() && this->getLocalizationHealth();
}

bool CStateMachine::isMoving(void) const
{
	return this->getVelocity() != 0 || this->getAccel() != 0;
}

bool CStateMachine::hasMoved(void) const
{
	return this->getCurrentDist() != 0;
}

bool CStateMachine::temperatureCheck(void) const
{
	return this->getBatteryTemp() < THRESHOLD && this->getMotorTemp() < THRESHOLD;
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

//This method goes through the various stages of the control system. 
void CStateMachine::step(void)
{
	//fault condition
	if (!this->isHealthy() || !this->temperatureCheck() || this->hasFinishedTrack())
	{
		this->updateState(FAULT);
		this->handleFault();
		return;
	} 
	else if (this->getCurrState() == UNLOADED && this->isUnloaded())
	{
		this->updateState(LOADED);
		//Manually set state to loaded via manual GUI control.
		//...
	}
	else if (this->getCurrState() == LOADED)
	{
		if (this->getCurrentDist() > TRACK_DIST)
		{
			this->updateState(CRAWLING);
			this->setMotorEngagement(true);
			this->setLocalizationEngagement(true);
		}
		else if (this->getCurrentDist() == TRACK_DIST)
		{
			this->updateState(BREAKING);
			this->setBreakEngagement(true);
			this->setLocalizationEngagement(true);
		}
		else
		{
			this->updateState(SAFE_TO_APPROACH);
			this->setLocalizationEngagement(true);
		}		
	} 
	else if (this->getCurrState() == SAFE_TO_APPROACH && !this->isMoving())
	{
		this->updateState(READY_TO_LAUNCH);
		//...
	}
	else if (this->getCurrState() == READY_TO_LAUNCH && !this->isReadyToLaunch())
	{
		this->updateState(LAUNCHING);
		this->setMotorEngagement(true);
		//Manually set state to launching via manual GUI control.
		//...
	}
	else if (this->getCurrState() == LAUNCHING && (this->getCurrentDist() >= BREAK_DIST || this->getCurrentDist() == TRACK_DIST))
	{
		this->updateState(BREAKING);
		this->setBreakEngagement(true);
		this->setMotorEngagement(false);
		//...
	}
	else if (this->getCurrState() == BREAKING && this->getCurrentDist() < TRACK_DIST)
	{
		this->updateState(CRAWLING);
		this->setBreakEngagement(false);
		this->setMotorEngagement(true);
		//...
		return;
	}
}

void CStateMachine::goThroughControlSystem(void)
{
	while (this->getCurrState() != FAULT)
	{
		this->step();
	}
}