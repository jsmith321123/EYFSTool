#include "CreateReportScreen.h"

CreateReportScreen::CreateReportScreen(string type) {
	type_ = type;

	if (type_ == "Individual") {
		setIndividual();
	} else if (type_ == "Group") {
		setGroup();
	} else if (type_ == "Learning Area") {
		setLearningArea();
	}

	layout.setAlignment(Qt::AlignTop);
}


void CreateReportScreen::setIndividual() {
	submitButton.setText("submit");

	selectLabel.setText("Pick child");
	startLabel.setText("Start date");
	endLabel.setText("End date");

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

void CreateReportScreen::setGroup() {
	submitButton.setText("submit");

	addGroupButton.setText("Add group");

	selectLabel.setText("Pick child");
	startLabel.setText("Start date");
	endLabel.setText("End date");

	selectLayout.addWidget(&selectLabel);
	selectLayout.addWidget(&select);
	selectLayout.addWidget(&addGroupButton);

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

void CreateReportScreen::setLearningArea() {
	submitButton.setText("submit");

	startLabel.setText("Start date");
	endLabel.setText("End date");

	startLayout.addWidget(&startLabel);
	startLayout.addWidget(&startDateEdit);

	endLayout.addWidget(&endLabel);
	endLayout.addWidget(&endDateEdit);

	layout.addLayout(&startLayout);
	layout.addLayout(&endLayout);
	layout.addWidget(&submitButton);

	setLayout(&layout);
}

void CreateReportScreen::createReport() {
	
}