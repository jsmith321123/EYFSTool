#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <iostream>

//qt
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>

using namespace std;

class LoginScreen : public QMainWindow {

Q_OBJECT

public:
	LoginScreen();

private:

	bool login(string u, string p);
	void showMainWindow();

	string hash();

	QTextEdit userTextEdit;
	QTextEdit passTextEdit;

	QPushButton loginButton;

};

#endif //LOGINSCREEN_H