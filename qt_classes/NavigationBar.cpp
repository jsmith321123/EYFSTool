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
	layout.addWidget(editUserButton);
	layout.addWidget(logOutButton);

	setLayout(&layout);

	mw_ = mw;

	//connections
	connect(addChildButton, SIGNAL(clicked()), this, SLOT(setAddChild()));
	connect(viewChildButton, SIGNAL(clicked()), this, SLOT(setViewChild()));
	connect(createUserButton, SIGNAL(clicked()), this, SLOT(setCreateUser()));
	connect(createReportButton, SIGNAL(clicked()), this, SLOT(setCreateReport()));
	connect(newAssessButton, SIGNAL(clicked()), this, SLOT(setNewAssessment()));
	connect(loadReportButton, SIGNAL(clicked()), this, SLOT(setLoadReport()));
	connect(editUserButton, SIGNAL(clicked()), this, SLOT(setEditUser()));
	connect(logOutButton, SIGNAL(clicked()), this, SLOT(logOut()));
}
