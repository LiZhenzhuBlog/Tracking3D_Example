/*
Author: QIN Shuo
Organization: RC-MIC (CUHK)
Date: 2016/01/05

*/

#ifndef _ATC3DGCONFIGURATION_H_
#define _ATC3DGCONFIGURATION_H_


#include "ATC3DG.h"
#include "../TrackingClass/TrackerBase.h"
#include <string>
#include <iostream>
#include <map>


class ATC3DGConfiguration : public TrackerBase
{
	typedef SYSTEM_CONFIGURATION        ATC3DGSysType;
	typedef SENSOR_CONFIGURATION        ATC3DGSensorType;
	typedef TRANSMITTER_CONFIGURATION   ATC3DGTransimitterType;
	typedef BOARD_CONFIGURATION		    ATC3DGBoardType;

	typedef DOUBLE_POSITION_ANGLES_RECORD      DefaultTransformType; //useless
	typedef DOUBLE_POSITION_ANGLES_TIME_Q_RECORD  DefinedTransformType;

public:
	ATC3DGConfiguration();
	~ATC3DGConfiguration();

	virtual int StartTracking() { return 0; };
	virtual int StopTracking() { CloseSystem(); return 0; };
	virtual int GetTrackingStatus();
	virtual int ConfigureTracker();
	virtual int GetToolValidation(int);
	virtual int GetTransformValidation(int);
	virtual QIN_Transform_Type* GetTransform(int index);

	//
	int PreInitialization(); // this function is controversial, not recommanded
	int SystemInitialization();
	int SystemSetup();
	int SensorSetup();
	int TransmitterSetup();
	int GetTransformInformation();
	int CloseSystem();
	int ErrorHandler();

private:
	int m_ErrorCode;
	std::string m_Status; //  "NULL Status" :        Default status
						  //  "Initialized Status"   System initialized
						  //  "System Ready"         System is set up and ready for next step
						  //  "Sensors Ready"         Sensors is set up and ready for next step
						  //  "Transmitters Ready"    Transmitter is ready for next step (ready for tracking)

	SYSTEM_CONFIGURATION			m_SystemConfig;
	SENSOR_CONFIGURATION*			m_SensorConfig;
	TRANSMITTER_CONFIGURATION*		m_TransmitterConfig;
	BOARD_CONFIGURATION*		    m_BoardConfig;

	int m_Num_Sensor;
	int m_Num_Transmitter;
	std::map< int, DefinedTransformType* >  m_TransformInformation;
	//QIN_Transform_Type*                  m_Transform;  // this object has been defined in TrackerBase class
};





#endif