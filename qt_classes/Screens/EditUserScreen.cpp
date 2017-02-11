#include "EditUserScreen.h"

#include <iostream>
#include <fstream>

#include <QStringList>
#include <QMessageBox>

#include "../../Hash.h"

#include "./../../libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

EditUserScreen::EditUserScreen() {
	//add all of the user selection components
	getUsers();

	selectLayout.addWidget(&usersCB);
	selectLayout.addWidget(selectButton);

	selectWidget.setLayout(&selectLayout);
	layout.addWidget(&selectWidget);
	setLayout(&layout);

	//add all of the user editing components
	passwordLayout.addWidget(passwordLabel);
	passwordLayout.addWidget(&passwordLE);

	passwordConfirmLayout.addWidget(passwordConfirmLabel);
	passwordConfirmLayout.addWidget(&passwordConfirmLE);

	//add the access levels to the combo box
	QStringList als;
	als << "" << "2" << "1" << "0";

	accessLevelCB.insertItems(0, als);

	accessLevelLayout.addWidget(accessLevelLabel);
	accessLevelLayout.addWidget(&accessLevelCB);

	editLayout.addLayout(&passwordLayout);
	editLayout.addLayout(&passwordConfirmLayout);
	editLayout.addLayout(&accessLevelLayout);
	editLayout.addWidget(saveButton);
	editLayout.addWidget(deleteButton);

	editWidget.setLayout(&editLayout);

	layout.addWidget(&editWidget);

	editLayout.setAlignment(Qt::AlignTop);
	selectLayout.setAlignment(Qt::AlignTop);

	//connections
	connect(selectButton, SIGNAL(clicked()), this, SLOT(selectUser()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveUser()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteUser()));
}

void EditUserScreen::getUsers() {
	ifstream usersFile("./data/users.json");
	usersJson = json::parse(usersFile);

	QStringList users;

	for (json user : usersJson) {
		string name = user["user"];
		users << QString::fromStdString(name);
	}

	usersCB.clear();
	usersCB.insertItems(0, users);
}

void EditUserScreen::selectUser() {
	layout.setCurrentIndex(1);
	id = usersCB.currentIndex();
}

void EditUserScreen::back() {

}

void EditUserScreen::saveUser() {
	json currentUser = usersJson[id];

	//check if the passwords match
	if (passwordLE.text() != "" &&
		passwordLE.text() == passwordConfirmLE.text()) {
		currentUser["hashed_password"] = Hash(passwordLE.text());
	}

	//check if a new access level has been selected
	if (accessLevelCB.currentIndex() != 0) {
		string access = accessLevelCB.currentText().toStdString();
		currentUser["access_level"] = stoi(access);
	}

	usersJson[id] = currentUser;

	ofstream output("./data/users.json");
	output << usersJson.dump();

	layout.setCurrentIndex(0);
}

void EditUserScreen::deleteUser() {
	//remove the user from the json
	json newUsersJson;

	for (int i; i < usersJson.size(); i++) {
		if (i != id) {
			usersJson[i]["id"] = i - 1;
			newUsersJson.push_back(usersJson[i]);
		}
	}

	QMessageBox::StandardButton reply;
  	reply = QMessageBox::question(this, "EYFSTool", "Delete User?",
                                QMessageBox::Yes|QMessageBox::No);
  	if (reply == QMessageBox::Yes) {
  		usersJson = newUsersJson;

    	ofstream output("./data/users.json");
		output << usersJson.dump();

		layout.setCurrentIndex(0);
  	}

  	getUsers();
}
