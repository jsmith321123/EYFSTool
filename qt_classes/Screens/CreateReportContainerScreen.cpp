#include "CreateReportContainerScreen.h"
#include "CreateReportScreen.h"


CreateReportContainerScreen::CreateReportContainerScreen(int al) {
	screens[0] = new CreateReportScreen("individual", al);
	screens[1] = new CreateReportScreen("group", al);
	screens[2] = new CreateReportScreen("learning area", al);

	for (CreateReportScreen* s : screens) {
		tabs.addTab(s, QString::fromStdString(s->type_));
	}

	layout.addWidget(&tabs);

	setLayout(&layout);
}
