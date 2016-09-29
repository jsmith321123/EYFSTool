#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <iostream>

//qt
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QSqlDatabase>

//headers
#include "MainWindow.h"

using namespace std;

class LoginScreen : public QMainWindow {

Q_OBJECT

public:
	LoginScreen(MainWindow *mw);

public slots:
	bool login();

private:

	void showMainWindow();

	QString hash(QString string);

	QWidget centralWidget;
	QVBoxLayout layout;

	QLineEdit userLineEdit;
	QLineEdit passLineEdit;

	QPushButton loginButton;

	QLabel wrongPassLabel;

	MainWindow *mw_;

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL3", "localhost");
};

#endif //LOGINSCREEN_H