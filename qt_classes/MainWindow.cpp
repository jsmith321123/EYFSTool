#include "MainWindow.h"
#include "Screen.h"

#include <Qt>

#include "./LoginScreen.h"


MainWindow::MainWindow(int al) {
	screens[0] = new AddChildScreen(al);
	screens[1] = new ViewChildScreen();
	screens[2] = new CreateUserScreen(al);
	screens[3] = new CreateReportContainerScreen(al);
	screens[4] = new NewAssessmentScreen(al);
	screens[5] = new LoadReportScreen();
	screens[6] = new EditUserScreen(al);

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

void NavigationBar::logOut() {
	LoginScreen *ls = new LoginScreen();
	ls->show();
	mw_->hide();
}
