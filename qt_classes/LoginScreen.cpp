#include <iostream>
#include <fstream>

#include "LoginScreen.h"
#include "MainWindow.h"
#include "./../libraries/json.hpp"

#include <QString>
#include <QDebug>

#include <typeinfo>

using namespace std;
using json = nlohmann::json;

LoginScreen::LoginScreen() {
	userLineEdit.setPlaceholderText("Username");
	passLineEdit.setPlaceholderText("Password");

	passLineEdit.setEchoMode(QLineEdit::Password);

	loginButton.setText("Login");

	layout.addWidget(&userLineEdit);
	layout.addWidget(&passLineEdit);
	layout.addWidget(&loginButton);
	layout.addWidget(&wrongPassLabel);

	centralWidget.setLayout(&layout);
	setCentralWidget(&centralWidget);

	centralWidget.setLayout(&layout);
	setCentralWidget(&centralWidget);

	connect(&loginButton, SIGNAL(clicked()), this, SLOT (login()));
    	connect(&passLineEdit, SIGNAL(returnPressed()), this, SLOT (login()));
}

bool LoginScreen::login() {
	QString user = userLineEdit.text();
	QString password = passLineEdit.text();
	
	ifstream user_file("./data/users.json", ifstream::binary);
	json user_json(user_file);
	
	for (json curr_user : user_json) {
	 	if (curr_user["user"] == json(user.toStdString())
		    && curr_user["hashed_password"] == json(hash(password))
		) {
			al = curr_user["access_level"];
			showMainWindow();
		}
	}

	wrongPassLabel.setStyleSheet("QLabel {color : red}");
	wrongPassLabel.setText("Incorrect username or password.");
	
	return true;
}

int LoginScreen::hash(QString string) {
	int finalInt = 0;

	int count = 1;
	for (char c : string.toStdString()) {
		finalInt += int(c) * count + 1;

		count += 128;
	}

	return finalInt;
}

void LoginScreen::showMainWindow() {
	MainWindow *main = new MainWindow(al);

	main->show();

	hide();
}
