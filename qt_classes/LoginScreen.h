#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <iostream>

//qt
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>

using namespace std;

class LoginScreen : public QMainWindow {

Q_OBJECT

public:
	LoginScreen();

private:

	bool login(string u, string p);
	void showMainWindow();

	string hash();

	QWidget centralWidget;
	QVBoxLayout layout;

	QLineEdit userLineEdit;
	QLineEdit passLineEdit;

	QPushButton loginButton;

};

#endif //LOGINSCREEN_H