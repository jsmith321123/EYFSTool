#include "CreateReportContainerScreen.h"
#include "CreateReportScreen.h"


CreateReportContainerScreen::CreateReportContainerScreen() {
	for (CreateReportScreen* s : screens) {
		tabs.addTab(s, QString::fromStdString(s->type_));
	}

	layout.addWidget(&tabs);

	setLayout(&layout);
}