#include <iostream>

#include "AddChildScreen.h"

#include <QSqlDatabase>
#include <QSqlQuery>

#include <fstream>

#include "./../../libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

AddChildScreen::AddChildScreen() {
	//settings for the date edit
	dobDateEdit.setCalendarPopup(true);

	//setting the text for the labels
	forenameLabel.setText("Forename:");
	surnameLabel.setText("Surname:");
	dobLabel.setText("Date of birth:");
	emailLabel.setText("Email:");
	homeNoLabel.setText("Home number:");
	p1MobLabel.setText("1st Parent's mobile number:");
	p2MobLabel.setText("2nd Parent's mobile number:");

	//adding labels to the layout
	forenameLayout.addWidget(&forenameLabel);
	surnameLayout.addWidget(&surnameLabel);
	dobLayout.addWidget(&dobLabel);
	emailLayout.addWidget(&emailLabel);
	homeNoLayout.addWidget(&homeNoLabel);
	p1MobLayout.addWidget(&p1MobLabel);
	p2MobLayout.addWidget(&p2MobLabel);

	//adding line edits to the layout
	forenameLayout.addWidget(&forenameLineEdit);
	surnameLayout.addWidget(&surnameLineEdit);
	dobLayout.addWidget(&dobDateEdit);
	emailLayout.addWidget(&emailLineEdit);
	homeNoLayout.addWidget(&homeNoLineEdit);
	p1MobLayout.addWidget(&p1MobLineEdit);
	p2MobLayout.addWidget(&p2MobLineEdit);

	//adding the layouts to the widgets layout
	layout.addLayout(&forenameLayout);
	layout.addLayout(&surnameLayout);
	layout.addLayout(&dobLayout);
	layout.addLayout(&emailLayout);
	layout.addLayout(&homeNoLayout);
	layout.addLayout(&p1MobLayout);
	layout.addLayout(&p2MobLayout);

	layout.addWidget(&submit);

	layout.setAlignment(Qt::AlignTop);

	setLayout(&layout);

	submit.setText("Submit");

	//connections
	connect(&submit, SIGNAL(clicked()), this, SLOT(addChild()));
}

void AddChildScreen::addChild () {
	//get the contents of the fields
	QString forename = forenameLineEdit.text();
	QString surname = surnameLineEdit.text();
	QString dob = dobDateEdit.date().toString();
	QString email = emailLineEdit.text();
	QString home_no = homeNoLineEdit.text();
	QString mobile_no1 = p1MobLineEdit.text();
	QString mobile_no2 = p2MobLineEdit.text();

	//open the json file and append the new child to the end of it
	json new_child;
	
	new_child["forename"] = forename.toStdString();
	new_child["surname"] = surname.toStdString();
	new_child["dob"] = dob.toStdString();
	new_child["email"] = email.toStdString();
	new_child["home_no"] = home_no.toStdString();
	new_child["mobile_no1"] = mobile_no1.toStdString();
	new_child["mobile_no2"] = mobile_no2.toStdString();	

	//get the existing json
	ifstream file("./data/children.json");
	json current = json(file);
	
	//set the id of the new child
	new_child["id"] = current.size();

	current.push_back(new_child);

	//rewrite the file with the new json object	
	ofstream output("./data/children.json");
	output << current.dump();
}
