#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <iostream>
#include <QMainWindow>

using namespace std;

class LoginScreen : public QMainWindow {

public:
	LoginScreen();

private:
	bool login();
	void showMainWindow();

};

#endif //LOGINSCREEN_H