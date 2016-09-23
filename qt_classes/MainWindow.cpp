#include "MainWindow.h"

MainWindow::MainWindow() {
	currentScreen = screens[0];

	layout.addWidget(currentScreen);
	layout.addWidget(&navBar);

	centralWidget.setLayout(&layout);

	setCentralWidget(&centralWidget);
}