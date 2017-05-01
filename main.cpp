#define __USE_MINGW_ANSI_STDIO 0

//defualt libraries
#include <iostream>
#include <fstream>

//headers
#include "qt_classes/LoginScreen.h"
#include "qt_classes/MainWindow.h"
#include "libraries/json.hpp"

//qt
#include <QtCore>
#include <QApplication>

//testing new assessment REMOVE!
#include "qt_classes/Screens/NewAssessmentScreen.h"

using namespace std;
using json = nlohmann::json;

//TODO
//seems to be issues with the new assessments saving to groups
//graph set title

int main(int argc, char **argv) {
	QApplication app (argc, argv);

	LoginScreen login;

	login.show();
	app.exec();
}
