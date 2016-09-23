#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

//qt
#include <QMainWindow>
#include <QHBoxLayout>
#include <QWidget>

//headers
#include "Screen.h"
#include "NavigationBar.h"

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
	Screen* screens [1] = {
		new AddChildScreen()//,
		//new CreateReportScreen(),
		//new CreateReportContainerScreen(),
		//new LoadReportScreen(),
		//new NewAssessmentScreen(),
		//new ViewChildScreen()
	};

	Screen *currentScreen;

	NavigationBar navBar;

	QHBoxLayout layout;

	QWidget centralWidget;
};


#endif //MAINWINDOW_H