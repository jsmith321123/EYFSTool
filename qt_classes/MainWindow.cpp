#include "MainWindow.h"
#include "Screen.h"

#include <Qt>


MainWindow::MainWindow(int al) {
	screens[0] = new AddChildScreen(al);
	cout << 0 << endl;
	screens[1] = new ViewChildScreen();
	cout << 1 << endl;
	screens[2] = new CreateUserScreen(al);
	cout << 2 << endl;
	screens[3] = new CreateReportContainerScreen(al);
	cout << 3 << endl;
	screens[4] = new NewAssessmentScreen(al);
	cout << 4 << endl;
	screens[5] = new LoadReportScreen();
	cout << 5 << endl;
	screens[6] = new EditUserScreen(al);
	cout << 6 << endl;

	for (Screen* s : screens) {
		mainScreen.addWidget(s);
	}

	mainScreen.setCurrentIndex(currentIndex);

	layout.addLayout(&mainScreen);
	layout.addWidget(navBar);

	centralWidget.setLayout(&layout);

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
	mw_->screens[4]->updateList();
}

void NavigationBar::setLoadReport() {
	mw_->changeScreen(5);
}

void NavigationBar::setEditUser() {
	mw_->changeScreen(6);
	mw_->screens[6]->updateList();
}
