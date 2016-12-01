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
#include <QSqlDatabase>

//testing new assessment REMOVE!
#include "qt_classes/Screens/NewAssessmentScreen.h"

using namespace std;
using json = nlohmann::json;

int main(int argc, char **argv) {
	QApplication app (argc, argv);

	LoginScreen login;

	login.show();
	app.exec();
}
