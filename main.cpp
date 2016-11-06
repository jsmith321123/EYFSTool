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

	//ifstream user_file("./data/users.json",  ifstream::binary);
	//json user_json(user_file);

	//cout<<user_json[0]<<endl;

	//setup database connection
	//QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL3", "localhost");

	//db.setHostName("localhost");
	//db.setDatabaseName("EYFSTool");
	//db.setUserName("root");
	//db.setPassword("1011josh");

	//bool ok = db.open();

	//cout << ok << endl;

	LoginScreen login;

	login.show();
	app.exec();

	json test;
}
