//HyperJackets State Machine v1.0
//Author: Sean Liu
//Language Used: C++
#pragma once
#ifndef C_STATE_MACHINE_HPP
#define C_STATE_MACHINE_HPP

enum State { UNLOADED, LOADED, FAULT, SAFE_TO_APPROACH, READY_TO_LAUNCH, LAUNCHING, CRAWLING, BREAKING };

class CStateMachine
{
private:
	//member variables
	//Note that m_ in front of a variable name means that it is a member variable, and f means that it's a float (decimal), and b means that it's a boolean.
	double m_fVelocity, m_fAccel, m_fBatteryTemp, m_fMotorTemp, m_fCurrentDist;
	bool m_bHealth, m_bLocalizationHealth;
	bool m_bBreak, m_bMotor, m_bLocalization, m_bBMS, m_bCommunications; //These variables denote if the interface is engaged or not.
	State m_currState;

	//constants
	static const int THRESHOLD = 100, EXCEEDED_DIST = 100, TRACK_DIST = 100, BREAK_DIST = 100;

public:
	//constructor
	CStateMachine();

	//methods
	//For now we are just doing temporary placeholder values. These should be changed and integrated with hardware later.
	double getVelocity(void) const { return this->m_fVelocity; }
	double getAccel(void) const { return this->m_fAccel; }
	double getBatteryTemp(void) const { return this->m_fBatteryTemp; }
	double getMotorTemp(void) const { return this->m_fBatteryTemp; }
	double getCurrentDist(void) const { return this->m_fCurrentDist; }
	bool getHealth(void) const { return this->m_bHealth; }
	bool getLocalizationHealth(void) const { return this->m_bLocalizationHealth; }
	bool getBreakEngagement(void) const { return this->m_bBreak; }
	bool getMotorEngagement(void) const { return this->m_bLocalization; }
	bool getLocalizationEngagement(void) const { return this->m_bLocalization; }
	bool getBMSEngagement(void) const { return this->m_bBMS; }
	bool getCommunicationsEngagement(void) const { return this->m_bCommunications; }
	State getCurrState(void) const { return this->m_currState; }

	//condition checks
	bool fault(void) const;
	bool causeForConcern(void) const;
	bool readyToLaunch(void) const;
	bool launching(void) const;
	bool breaking(void) const;

	//methods that handle changes to state, in terms of engagement
	void setState_safeToApproach(void);
	void setState_launching(void);
	void setState_breaking(void);
	void setState_crawling(void);

	//other methods

	void updateState(State newState) { this->m_currState = newState; }
	void goThroughControlSystem(void);

	//step method
	void step(void);
};
#endif