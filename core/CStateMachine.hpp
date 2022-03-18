//HyperJackets State Machine v1.0
//Author: Sean Liu
//Language Used: C++

//Push changes to current branch as sean, and see changes online at https://github.com/HyperJackets/buzz-22/tree/sean

#pragma once
#ifndef C_STATE_MACHINE_HPP
#define C_STATE_MACHINE_HPP

enum State { UNLOADED, LOADED, FAULT, SAFE_TO_APPROACH, READY_TO_LAUNCH, LAUNCHING, CRAWLING, BRAKING };

class CStateMachine
{
private:
	//member variables
	//Note that m_ in front of a variable name means that it is a member variable, and f means that it's a float (decimal), and b means that it's a boolean.
	double m_fVelocity, m_fAccel, m_fBatteryTemp, m_fMotorTemp, m_fCurrentDist;
	bool m_bHealth, m_bLocalizationHealth;
	//The following variables denote if the interface is engaged or not. Also make sure that VD and structures know that braking and propulsion can never be simultaneously powered.
	bool m_bBrake, m_bMotor, m_bLocalization, m_bBMS, m_bCommunications;  
	State m_currState;
	//The following variables are changed when a GUI is pressed on the dashboard.
	bool m_bIsUnloaded = true;
	bool m_bIsReadyToLaunch = false; 

	//constants
	static const int THRESHOLD = 100, EXCEEDED_DIST = 170, TRACK_DIST = 150, BREAK_DIST = 70;

public:
	//constructor
	CStateMachine();

	//methods

	//get methods
	double getVelocity(void) const { return this->m_fVelocity; }
	double getAccel(void) const { return this->m_fAccel; }
	double getBatteryTemp(void) const { return this->m_fBatteryTemp; }
	double getMotorTemp(void) const { return this->m_fBatteryTemp; }
	double getCurrentDist(void) const { return this->m_fCurrentDist; }
	bool getHealth(void) const { return this->m_bHealth; }
	bool getLocalizationHealth(void) const { return this->m_bLocalizationHealth; }
	bool getBrakeEngagement(void) const { return this->m_bBrake; }
	bool getMotorEngagement(void) const { return this->m_bMotor; }
	bool getLocalizationEngagement(void) const { return this->m_bLocalization; }
	bool getBMSEngagement(void) const { return this->m_bBMS; }
	bool getCommunicationsEngagement(void) const { return this->m_bCommunications; }
	State getCurrState(void) const { return this->m_currState; }
	bool isUnloaded(void) const {return this->m_bIsUnloaded;}
	bool isReadyToLaunch(void) const {return this->m_bIsReadyToLaunch;}

	//set methods for engagement
	void setLocalizationEngagement(bool bLocalization) {this->m_bLocalization = bLocalization;}
	void setMotorEngagement(bool bMotor) {this->m_bMotor = bMotor;}
	void setBrakeEngagement(bool bBrake) {this->m_bBrake = bBrake;}
	void setBMSEngagement(bool bBMS) {this->m_bBMS = bBMS;}
	void setCommunicationsEngagement(bool bCommunications) {this->m_bCommunications = bCommunications;}

	//set methods for GUI 
	void setIsUnloaded(bool bIsUnloaded) {this->m_bIsUnloaded = bIsUnloaded;}
	void setIsReadyToLaunch(bool bIsReadyToLaunch) {this->m_bIsReadyToLaunch = bIsReadyToLaunch;}

	//condition checks
	bool hasFinishedTrack(void) const;
	bool isHealthy(void) const;
	bool isMoving(void) const;
	bool hasMoved(void) const;
	bool temperatureCheck(void) const;
	bool readyToLaunch(void) const;
	bool launching(void) const;
	bool braking(void) const;

	//These are methods that will be used in the test. However when we integrate with hardware the hardware will monitor and calculate the data.
	void setVelocity(double fVelocity) {this->m_fVelocity = fVelocity;}
	void setAccel(double fAccel) {this->m_fAccel = fAccel;}
	void setBatteryTemp(double fBatteryTemp) {this->m_fBatteryTemp = fBatteryTemp;}
	void setMotorTemp(double fMotorTemp) {this->m_fMotorTemp = fMotorTemp;}
	void setCurrentDist(double fCurrentDist) {this->m_fCurrentDist = fCurrentDist;}
	void setHealth(bool bHealth) {this->m_bHealth = bHealth;}
	void setLocalizationHealth(bool bLocalizationHealth) {this->m_bLocalizationHealth = bLocalizationHealth;}

	//other methods
	void handleFault(void);
	void updateState(State newState) { this->m_currState = newState; }
	void goThroughControlSystem(void);

	//step method
	void step(void);
};
#endif