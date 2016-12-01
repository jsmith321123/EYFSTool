#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

//qt
#include <QMainWindow>
#include <QHBoxLayout>
#include <QWidget>
#include <QStackedLayout>

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
#include "Screens/CreateUserScreen.h"


class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(int al);

	void changeScreen(int index);

	int accessLevel = 2;

	int currentIndex = 1;

	Screen* screens [4];
private:
	Screen *currentScreen;

	NavigationBar* navBar = new NavigationBar(this);

	QHBoxLayout layout;

	QWidget centralWidget;

	QStackedLayout mainScreen;
};


#endif //MAINWINDOW_H
