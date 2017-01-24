#include "MainWindow.h"
#include "Screen.h"

#include <Qt>


MainWindow::MainWindow(int al) {
	screens[0] = new AddChildScreen();
	screens[1] = new ViewChildScreen();
	screens[2] = new CreateUserScreen(al);
	screens[3] = new CreateReportContainerScreen();
	screens[4] = new NewAssessmentScreen();
	screens[5] = new LoadReportScreen();

	for (Screen* s : screens) {
		mainScreen.addWidget(s);
	}

	mainScreen.setCurrentIndex(currentIndex);

	layout.addLayout(&mainScreen);
	layout.addWidget(navBar);

	centralWidget.setLayout(&layout);

	//centralWidget.setFixedSize(500, 300);

	setCentralWidget(&centralWidget);
}

void MainWindow::changeScreen(int index) {
	currentIndex = index;

	mainScreen.setCurrentIndex(currentIndex);
}

void NavigationBar::setAddChild() {
	mw_->changeScreen(0);
}

void NavigationBar::setViewChild() {
	mw_->changeScreen(1);
	mw_->screens[1]->updateList();
}

void NavigationBar::setCreateUser() {
	mw_->changeScreen(2);
}

void NavigationBar::setCreateReport() {
	mw_->changeScreen(3);
}

void NavigationBar::setNewAssessment() {
	mw_->changeScreen(4);
}

void NavigationBar::setLoadReport() {
	mw_->changeScreen(5);
}
