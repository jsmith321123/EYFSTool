#include <iostream>

#include "AddChildScreen.h"

#include <fstream>

#include "./../../libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

AddChildScreen::AddChildScreen(int al) {
	al_ == al;

	//settings for the date edit
	dobDateEdit.setCalendarPopup(true);

	//setting the text for the labels
	forenameLabel.setText("Forename:");
	surnameLabel.setText("Surname:");
	genderLabel.setText("Gender: ");
	dobLabel.setText("Date of birth:");
	knownAsLabel.setText("Known as:");
	negLabel.setText("NEG:");
	f2yoLabel.setText("F2YO");
	eyppLabel.setText("EYPP:");

	//adding labels to the layout
	forenameLayout.addWidget(&forenameLabel);
	surnameLayout.addWidget(&surnameLabel);
	genderLayout.addWidget(&genderLabel);
	dobLayout.addWidget(&dobLabel);
	knownAsLayout.addWidget(&knownAsLabel);
	negLayout.addWidget(&negLabel);
	f2yoLayout.addWidget(&f2yoLabel);
	eyppLayout.addWidget(&eyppLabel);

	//adding inputs to the layout
	forenameLayout.addWidget(&forenameLineEdit);
	surnameLayout.addWidget(&surnameLineEdit);
	genderLayout.addWidget(&genderCB);
	dobLayout.addWidget(&dobDateEdit);
	knownAsLayout.addWidget(&knownAsLineEdit);
	negLayout.addWidget(&negCheckBox);
	f2yoLayout.addWidget(&f2yoCheckBox);
	eyppLayout.addWidget(&eyppCheckBox);

	//adding the layouts to the widgets layout
	layout.addLayout(&forenameLayout);
	layout.addLayout(&surnameLayout);
	layout.addLayout(&knownAsLayout);
	layout.addLayout(&genderLayout);
	layout.addLayout(&dobLayout);
	layout.addLayout(&negLayout);
	layout.addLayout(&f2yoLayout);
	layout.addLayout(&eyppLayout);

	layout.addWidget(&submit);
	layout.addWidget(&notification);

	layout.setAlignment(Qt::AlignTop);

	setLayout(&layout);

	submit.setText("Submit");

	//set the contents of the gender box
	QStringList genders;
	genders << "Male" << "Female";
	genderCB.insertItems(0, genders);

	//connections
	connect(&submit, SIGNAL(clicked()), this, SLOT(addChild()));
}

void AddChildScreen::addChild () {
	//get the contents of the fields
	QString forename = forenameLineEdit.text();
	QString surname = surnameLineEdit.text();
	QString gender = genderCB.currentText();
	QString dob = dobDateEdit.date().toString();
	QString knownAs = knownAsLineEdit.text();
	int neg = negCheckBox.isChecked();
	int f2yo = f2yoCheckBox.isChecked();
	int eypp = eyppCheckBox.isChecked();

	//open the json file and append the new child to the end of it
	json new_child;
	
	new_child["forename"] = forename.toStdString();
	new_child["surname"] = surname.toStdString();
	new_child["gender"] = gender.toStdString();
	new_child["dob"] = dob.toStdString();
	new_child["knownAs"] = knownAs.toStdString();
	new_child["neg"] = neg;
	new_child["f2yo"] = f2yo;
	new_child["eypp"] = eypp;

	//get the existing json
	ifstream file("./../data/children.json");
	json current = json(file);

	//failure reasons
	string alFail = "You do not have the permissions to do this";
	string foreFail = "You have not entered a forename";
	string surFail = "You have not entered a surname";

	string reason = (al_ > 0) ? (alFail) : (forename == "") ? (foreFail) : (surFail);
	

	//only add the child if the user has
	//the correct permissions
	if (al_ < 1 && forename != "" && surname != "") {
		//set the id of the new child
		new_child["id"] = current.size();
	
		current.push_back(new_child);

		//notify the user that the child
		//has been added
		notification.setStyleSheet("QLabel {color : green}");
		notification.setText("Child added!");
	} else {
		notification.setStyleSheet("QLabel {color : red}");
		notification.setText("Child not added. Reason: " + QString::fromStdString(reason));
	}

	//rewrite the file with the new json object	
	ofstream output("./../data/children.json");
	output << current.dump();
}
