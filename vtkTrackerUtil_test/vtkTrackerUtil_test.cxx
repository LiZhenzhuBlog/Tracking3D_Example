/**
Author: QIN Shuo
Date: 2017/05/10
Description:
	Example for tracking class

Main test file

**/

#include "ICPRegistrationFilter.h"
#include "LandmarkRegistrationFilter.h"

#include "vtkTrackerUtil_test_Win.h"
#include <QApplication>
#include <QMainWindow>

QCoreApplication* createApplication(int &argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
		if (!qstrcmp(argv[i], "-no-gui"))
			return new QCoreApplication(argc, argv);
	return new QApplication(argc, argv);
}

int main(int argc, char** argv)
{
	QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

	if (qobject_cast<QApplication *>(app.data())) {
		// start GUI version...
		MainWindow* main_window;
		main_window = new MainWindow;
		main_window->show();
	}
	else {
		// start non-GUI version...
	}

	return app->exec();

}




