#include "EditUserScreen.h"

#include <iostream>
#include <fstream>

#include <QStringList>
#include <QMessageBox>

#include <regex>

#include "../../Hash.h"

#include "./../../libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

EditUserScreen::EditUserScreen(int al) {
	al_ = al;

	//add all of the user selection components
	updateList();

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
	editLayout.addWidget(&editFeedback);

	editWidget.setLayout(&editLayout);

	layout.addWidget(&editWidget);

	editLayout.setAlignment(Qt::AlignTop);
	selectLayout.setAlignment(Qt::AlignTop);

	//connections
	connect(selectButton, SIGNAL(clicked()), this, SLOT(selectUser()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveUser()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteUser()));
}

void EditUserScreen::updateList() {
	ifstream usersFile("./../data/users.json");
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
	//if the user doesnt have the required permissions show
	//an error message and stay on select screen
	if (al_ >= 1) {
		QLabel* notification = new QLabel("You do not have permissions to do that");
		selectLayout.addWidget(notification);
		return;
	}

	layout.setCurrentIndex(1);
	id = usersCB.currentIndex();
}

void EditUserScreen::back() {

}

void EditUserScreen::saveUser() {
	json currentUser = usersJson[id];

	//check if the password fits the requirements and matches
	regex newRegex = regex("^(?=.*[a-z])(?=.*\\d).+$");

	string reason;

	bool validPW = false;
	bool pwMatch = passwordLE.text() == passwordConfirmLE.text();

	if (!pwMatch) {
		reason = "passwords do not match.";
	}

	if ((regex_match(passwordLE.text().toStdString(), newRegex) && passwordLE.text().length() > 7)) {
		validPW = true;
	} else {
		reason = "password does not fit the requirements, must have 8 characters and at least 1 digit.";
	}

	//see if password has been entered
	if (passwordLE.text() != "") {
		if (validPW && pwMatch) {
			currentUser["hashed_password"] = Hash(passwordLE.text());
		} else {
			//display message telling user why edit failed and exit func
			editFeedback.setText(QString::fromStdString("User not added. Reason: " + reason));
			return;
		}
	}

	//check if a new access level has been selected
	if (accessLevelCB.currentIndex() != 0) {
		string access = accessLevelCB.currentText().toStdString();
		currentUser["access_level"] = stoi(access);
	}

	usersJson[id] = currentUser;

	ofstream output("./../data/users.json");
	output << usersJson.dump();

	layout.setCurrentIndex(0);
}

void EditUserScreen::deleteUser() {
	//remove the user from the json
	json newUsersJson = json::parse("[]");

	//delete user from json
	for (int i = 0; i < usersJson.size(); i++) {
		//if user is not the delted user add it to the new json
		if (i != id) {
			//if the user is after the deleted user, decrement the id
			if (i > id) {
				usersJson[i]["id"] = i - 1;
			}
			
			newUsersJson.push_back(usersJson[i]);
		}
	}

	//create popup asking if the user wants to delete the selected user
	QMessageBox::StandardButton reply;
  	reply = QMessageBox::question(this, "EYFSTool", "Delete User?",
                                QMessageBox::Yes|QMessageBox::No);

  	//if yes was selected save the new json
  	if (reply == QMessageBox::Yes) {
  		usersJson = newUsersJson;

    	ofstream output("./../data/users.json");
		output << usersJson.dump();

		layout.setCurrentIndex(0);
  	}

  	updateList();
}
