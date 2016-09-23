#include "NavigationBar.h"

NavigationBar::NavigationBar() {
	layout.addWidget(addChildButton);
	layout.addWidget(viewChildButton);
	layout.addWidget(newAssessButton);
	layout.addWidget(createReportButton);
	layout.addWidget(loadReportButton);

	setLayout(&layout);
}