#include <iostream>

#include "LoginScreen.h"


using namespace std;

LoginScreen::LoginScreen() {
	userLineEdit.setPlaceholderText("Username");
	passLineEdit.setPlaceholderText("Password");

	passLineEdit.setEchoMode(QLineEdit::Password);

	loginButton.setText("Login");

	layout.addWidget(&userLineEdit);
	layout.addWidget(&passLineEdit);
	layout.addWidget(&loginButton);

	centralWidget.setLayout(&layout);

	setCentralWidget(&centralWidget);
}