/*
Author: QIN Shuo
Organization: RC-MIC (CUHK)
Date: 2016/2/22
Module:
	Tool Calibration module
*/

#ifndef _CALIBRATION_WINDOW_H_
#define _CALIBRATION_WINDOW_H_

#include "ui_CalibrationWindow.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <functional>
#include <algorithm>

#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <QWheelEvent>
#include <QMessageBox>
#include <QTimer>

#include "vtkNIFTIImageReader.h"

//qt + vtk include
#include "QVTKWidget.h"
//qt + vtk connect signal and slot
#include "vtkCommand.h"
#include "vtkEventQtSlotConnect.h"
#include "vtkMarchingCubes.h"
#include "vtkSphereSource.h"
#include "vtkSTLReader.h"
#include "vtkXMLPolyDataReader.h"
#include "vtkSmartPointer.h"

#include "PolarisVicraConfiguration.h"
#include "ATC3DGConfiguration.h"
#include "vtkTrackingResliceView.h"
#include "vtkTracking3D.h"
#include "vtkTrackingMarkCapture.h"
#include "vtkTrackingRegistration.h"

#include "PivotCalibration.h"
#include "PivotCalibration2.h"



namespace Ui {
	class CalibrationWindow;
}



class CalibrationWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit CalibrationWindow(QWidget *parent = 0);
	~CalibrationWindow();


	void sys_Init();
	void GetCalibrationMatrix(vtkMatrix4x4*);


	public slots:

	void On_Config_Polaris();
	void On_Config_ATC();
	void On_Capture();
	void On_Calculate1();
	void On_Calculate2();
	void Act_LoadSTL();
	void Act_CreateDefault();
	void On_Move();
	void On_Close();
	void On_Timer();

protected:
	void CreateCoordinate();
	
private:
	Ui::CalibrationWindow *ui;
	QTimer*					m_Timer;

	vtkSmartPointer<vtkRenderWindow>			m_View;
	vtkSmartPointer<vtkRenderWindowInteractor>  m_Interactor;
	vtkSmartPointer<vtkRenderer>				m_Renderer;

	vtkSmartPointer<vtkProp3D>					m_Actor;
	vtkSmartPointer<vtkProp3D>					m_Actor2;
	vtkSmartPointer<vtkActor>					m_Tra_Actor;


	PloarisVicraConfiguration*  m_Polaris;
	ATC3DGConfiguration*        m_ATC;


	QIN_Transform_Type*         m_Tool_Transform; // tool position and orientation
	vtkSmartPointer<vtkMatrix4x4>	m_Tool_Matrix;
	vtkSmartPointer<vtkTransform>   m_Tool2TipTransform;  // tool to tooltip transformation
	vtkSmartPointer<vtkMatrix4x4>	m_Tool2TipMatrix;

	vtkSmartPointer<PivotCalibration>           m_CalibrationHandle1;
	vtkSmartPointer<PivotCalibration2>			m_CalibrationHandle2;

	

};






#endif
