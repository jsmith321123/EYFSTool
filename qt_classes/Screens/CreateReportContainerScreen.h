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
		new CreateReportScreen("Individual"),
		new CreateReportScreen("Group"),
		new CreateReportScreen("Learning Area")
	};

	QTabWidget tabs;

	QVBoxLayout layout;
};

#endif