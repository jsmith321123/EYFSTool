//defualt libraries
#include <iostream>

//headers
#include "qt_classes/LoginScreen.h"

//qt
#include <QtCore>
#include <QApplication>

using namespace std;

int main(int argc, char **argv) {
	QApplication app (argc, argv);
	LoginScreen login;
	login.show();
	app.exec();
}