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
		new CreateReportScreen("individual"),
		new CreateReportScreen("group"),
		new CreateReportScreen("learning area")
	};

	QTabWidget tabs;

	QVBoxLayout layout;
};

#endif