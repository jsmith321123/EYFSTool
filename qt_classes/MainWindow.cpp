#include "MainWindow.h"

MainWindow::MainWindow() {
	currentScreen = screens[0];

	setCentralWidget(currentScreen);
}