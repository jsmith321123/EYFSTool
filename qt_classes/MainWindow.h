#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

//qt
#include <QMainWindow>

//headers
#include "Screen.h"

//screens
#include "Screens/AddChildScreen.h"
#include "Screens/CreateReportScreen.h"
#include "Screens/CreateReportContainerScreen.h"
#include "Screens/LoadReportScreen.h"
#include "Screens/NewAssessmentScreen.h"
#include "Screens/ViewChildScreen.h"


class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow();

private:
	Screen screens [1] = {
		AddChildScreen()//,
		//new CreateReportScreen(),
		//new CreateReportContainerScreen(),
		//new LoadReportScreen(),
		//new NewAssessmentScreen(),
		//new ViewChildScreen()
	};

	Screen currentScreen;
};


#endif //MAINWINDOW_H