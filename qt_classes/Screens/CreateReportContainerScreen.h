#ifndef CREATEREPORTCONTAINERSCREEN_H
#define CREATEREPORTCONTAINERSCREEN_H

#include "./Screen.h"
#include "CreateReportScreen.h"
#include <QTabWidget>
#include <QVBoxLayout>

class CreateReportContainerScreen : public Screen{
public:
	CreateReportContainerScreen();

public slots:

private:
	CreateReportScreen* screens[3] = {
		new CreateReportScreen(),
		new CreateReportScreen(),
		new CreateReportScreen()
	};

	QTabWidget tabs;

	QVBoxLayout layout;
};

#endif