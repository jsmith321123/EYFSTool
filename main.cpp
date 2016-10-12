//defualt libraries
#include <iostream>

//headers
#include "qt_classes/LoginScreen.h"
#include "qt_classes/MainWindow.h"

//qt
#include <QtCore>
#include <QApplication>
#include <QSqlDatabase>

//testing new assessment REMOVE!
#include "qt_classes/Screens/NewAssessmentScreen.h"

using namespace std;

int main(int argc, char **argv) {
	QApplication app (argc, argv);

	//setup database connection
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL3", "localhost");

	db.setHostName("localhost");
	db.setDatabaseName("EYFSTool");
	db.setUserName("root");
	db.setPassword("1011josh");

	bool ok = db.open();

	cout << ok << endl;

	LoginScreen login(db);

	NewAssessmentScreen* nas = new NewAssessmentScreen(db);
	login.show();
	app.exec();
}
