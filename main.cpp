//defualt libraries
#include <iostream>

//headers
#include "qt_classes/LoginScreen.h"
#include "qt_classes/MainWindow.h"

//qt
#include <QtCore>
#include <QApplication>
#include <QSqlDatabase>

using namespace std;

int main(int argc, char **argv) {
	QApplication app (argc, argv);
	MainWindow mw;
	LoginScreen login(&mw);
	login.show();
	app.exec();
}