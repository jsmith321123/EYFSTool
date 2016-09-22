#ifndef EYFSTOOL_LOGINSCREEN_H
#define EYFSTOOL_LOGINSCREEN_H

#include <iostream>

using namespace std;

class LoginScreen : public QMainWindow {


public:
	LoginScreen();

private:
	bool login();
	void showMainWindow();

};

#endif //EYFSTOOL_LOGINSCREEN_H