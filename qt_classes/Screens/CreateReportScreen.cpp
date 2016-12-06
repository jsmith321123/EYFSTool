#include "CreateReportScreen.h"

CreateReportScreen::CreateReportScreen() {
	submitButton.setText("submit");

	selectLayout.addWidget(&selectLabel);
	selectLayout.addWidget(&select);

	startLayout.addWidget(&startLabel);
	startLayout.addWidget(&startDateEdit);

	endLayout.addWidget(&endLabel);
	endLayout.addWidget(&endDateEdit);

	layout.addLayout(&selectLayout);
	layout.addWidget(&detailTextEdit);
	layout.addLayout(&startLayout);
	layout.addLayout(&endLayout);
	layout.addWidget(&submitButton);

	setLayout(&layout);
}
