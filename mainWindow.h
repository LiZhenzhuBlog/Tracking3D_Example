/*
Author: QIN Shuo
Organization: RC-MIC (CUHK)
Date: 2016/1/10
*/


#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include "ui_mainWindow.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <functional>
#include <algorithm>

#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <QWheelEvent>



//qt + vtk include
#include "QVTKWidget.h"
//qt + vtk connect signal and slot
#include "vtkCommand.h"
#include "vtkEventQtSlotConnect.h"

#include "vtkTracking3D.h"

namespace Ui {
	class MainWindow;
}



class MainWindow: public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void sys_Init();

public slots:
	void on_Load_Image();
	void on_Load_Atlas();
	void on_Sel_Tracker();
	void on_Config_Tracker();

	void on_StartTracking();
	void on_StopTracking();
	void on_OpacityMove(int);

private:
	Ui::MainWindow *ui;
};






#endif
