#include "CreateUserScreen.h"

#include "../../Hash.h"
#include "./../../libraries/json.hpp"

#include <iostream>
#include <fstream>

#include <QString>
#include <QStringList>

#include "./MainWindow.h"

using namespace std;
using json = nlohmann::json;

CreateUserScreen::CreateUserScreen(int al) {
	//user_name selection
	userLabel.setText("Username");
	userLayout.addWidget(&userLabel);
	userLayout.addWidget(&userLineEdit);

	//password selection
	pass1Label.setText("Password");
	pass2Label.setText("Confirm password");
	pass1Layout.addWidget(&pass1Label);
	pass1Layout.addWidget(&pass1LineEdit);
	pass2Layout.addWidget(&pass2Label);
	pass2Layout.addWidget(&pass2LineEdit);
	passLayout.addLayout(&pass1Layout);
	passLayout.addLayout(&pass2Layout);

	//stops the input being visible for password entry
	pass1LineEdit.setEchoMode(QLineEdit::Password);
	pass2LineEdit.setEchoMode(QLineEdit::Password);

	//access level selection
	accessLabel.setText("Access level");
	accessLayout.addWidget(&accessLabel);
	accessLayout.addWidget(&accessComboBox);

	//submitting
	submitButton.setText("Submit");

	//overall layout
	layout.addLayout(&userLayout);
	layout.addLayout(&passLayout);
	layout.addLayout(&accessLayout);
	layout.addWidget(&submitButton);
	layout.addWidget(&feedbackLabel);

	al_ = al;

 	//adding values to combobox
	QStringList levels;
	levels << "2" << "1" << "0";
	accessComboBox.insertItems(0, levels);


	setLayout(&layout);

	//connections
	connect(&submitButton, SIGNAL(clicked()), this, SLOT(addUser()));
}

void CreateUserScreen::addUser() {
	//bool and string that will help give
	//feedback to the user
	bool succeded = false;
	QString reason = "";

	//initialising the variable for the hashed_password
	int password = 0;

	//calculating the hashed value for the password
	//only if the passwords entered in the boxes match
	if (pass1LineEdit.text() == pass2LineEdit.text()) {
		password = Hash(pass1LineEdit.text());
	} else {
		succeded = false;
		reason = "passwords do not match.";
	}

	//gets inputted username and checks if
	//a user exists with that name
	QString user = userLineEdit.text();
	bool newUser = !userExists(user);

	//selects correct reason for failure
	//to add the new user
	if (user == "") {
		succeded = false;
		reason = "no username given.";
	} else if (!newUser) {
		succeded = false;
		reason = "user exists.";
	}

	//check if the current user has the
	//permissions to add a user
	if (al_ != 0) {
		succeded = false;
		reason = "you do not possess the permissions to add a user";
	}

	//check if no password has been added
	if (password == 0) {
		succeded = false;
		reason = "no password given";
	}

	cout << "al: " << al_ << endl;

	//if the password and user name are valid
	//adds the new user to the table as long
	//as they dont already exist
	if (newUser && password != 0 && user != "" && al_ == 0) {
		ifstream user_file("./data/users.json", ifstream::binary);
		json user_json(user_file);
		
		string access = accessComboBox.currentText().toStdString();

		json new_user;

		new_user["user"] = user.toStdString();
		new_user["hashed_password"] = password;
		new_user["access_level"] = stoi(access);
		
		user_json.push_back(new_user);

		ofstream output("./data/users.json");

		output << user_json.dump();

		succeded = true;
	}

	//displays the correct messages
	if (succeded) {
		feedbackLabel.setText("User added.");
		feedbackLabel.setStyleSheet("QLabel {color : green}");

		//clear all of the input fields
		userLineEdit.setText("");
		pass1LineEdit.setText("");
		pass2LineEdit.setText("");
		accessComboBox.setCurrentIndex(0);
	} else {
		feedbackLabel.setText("User not added. Reason: " + reason);
		feedbackLabel.setStyleSheet("QLabel {color : red}");
	}

   	
}

bool CreateUserScreen::userExists(QString user_name) {
	ifstream user_file("./data/users.json", ifstream::binary);
	json user_json(user_file);
	
	for (json user : user_json) {
		if (user["user"] == json(user_name.toStdString())) {
			return true;
		}
	}

	return false;
}
