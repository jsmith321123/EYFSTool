#ifndef CREATEREPORTCONTAINERSCREEN_H
#define CREATEREPORTCONTAINERSCREEN_H

#include "./Screen.h"
#include "CreateReportScreen.h"
#include <QTabWidget>
#include <QVBoxLayout>

class CreateReportContainerScreen : public Screen{
public:
	CreateReportContainerScreen(int al);

public slots:

private:
	CreateReportScreen* screens[3];

	QTabWidget tabs;

	QVBoxLayout layout;
};

#endif
