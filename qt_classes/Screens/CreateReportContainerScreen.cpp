#include "CreateReportContainerScreen.h"
#include "CreateReportScreen.h"


CreateReportContainerScreen::CreateReportContainerScreen() {
	for (CreateReportScreen* s : screens) {
		tabs.addTab(s, "1");
	}

	layout.addWidget(&tabs);

	setLayout(&layout);
}