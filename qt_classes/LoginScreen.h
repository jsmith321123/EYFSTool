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

//headers
#include "MainWindow.h"


using namespace std;

class LoginScreen : public QMainWindow {

Q_OBJECT

public:
	LoginScreen();

public slots:
	bool login();

private:
	int al;

	void showMainWindow();

	int hash(QString string);

	QWidget centralWidget;
	QVBoxLayout layout;

	QLineEdit userLineEdit;
	QLineEdit passLineEdit;

	QPushButton loginButton;

	QLabel wrongPassLabel;

	MainWindow *mw_;
};

#endif //LOGINSCREEN_H
