#include <iostream>

#include "NavigationBar.h"

#include <QMainWindow>

using namespace std;

NavigationBar::NavigationBar(MainWindow* mw) {
	layout.addWidget(addChildButton);
	layout.addWidget(viewChildButton);
	layout.addWidget(newAssessButton);
	layout.addWidget(createReportButton);
	layout.addWidget(loadReportButton);
	layout.addWidget(createUserButton);

	setLayout(&layout);

	mw_ = mw;

	//connections
	connect(addChildButton, SIGNAL(clicked()), this, SLOT(setAddChild()));
	connect(viewChildButton, SIGNAL(clicked()), this, SLOT(setViewChild()));
	connect(createUserButton, SIGNAL(clicked()), this, SLOT(setCreateUser()));
}
