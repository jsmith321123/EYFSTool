#include "MainWindow.h"

#include <Qt>

MainWindow::MainWindow() {
	currentScreen = screens[1];

	layout.addWidget(currentScreen);
	layout.addWidget(&navBar);

	centralWidget.setLayout(&layout);

	setCentralWidget(&centralWidget);
}