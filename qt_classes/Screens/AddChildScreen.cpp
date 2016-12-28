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
	knownAsLabel.setText("Known as:");
	negLabel.setText("NEG:");
	f2yoLabel.setText("F2YO");
	eyppLabel.setText("EYPP:");

	//adding labels to the layout
	forenameLayout.addWidget(&forenameLabel);
	surnameLayout.addWidget(&surnameLabel);
	dobLayout.addWidget(&dobLabel);
	knownAsLayout.addWidget(&knownAsLabel);
	negLayout.addWidget(&negLabel);
	f2yoLayout.addWidget(&f2yoLabel);
	eyppLayout.addWidget(&eyppLabel);

	//adding line edits to the layout
	forenameLayout.addWidget(&forenameLineEdit);
	surnameLayout.addWidget(&surnameLineEdit);
	dobLayout.addWidget(&dobDateEdit);
	knownAsLayout.addWidget(&knownAsLineEdit);
	negLayout.addWidget(&negCheckBox);
	f2yoLayout.addWidget(&f2yoCheckBox);
	eyppLayout.addWidget(&eyppCheckBox);

	//adding the layouts to the widgets layout
	layout.addLayout(&forenameLayout);
	layout.addLayout(&surnameLayout);
	layout.addLayout(&knownAsLayout);
	layout.addLayout(&dobLayout);
	layout.addLayout(&negLayout);
	layout.addLayout(&f2yoLayout);
	layout.addLayout(&eyppLayout);

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
	QString knownAs = knownAsLineEdit.text();
	int neg = negCheckBox.isChecked();
	int f2yo = f2yoCheckBox.isChecked();
	int eypp = eyppCheckBox.isChecked();

	//open the json file and append the new child to the end of it
	json new_child;
	
	new_child["forename"] = forename.toStdString();
	new_child["surname"] = surname.toStdString();
	new_child["dob"] = dob.toStdString();
	new_child["knownAs"] = knownAs.toStdString();
	new_child["neg"] = neg;
	new_child["f2yo"] = f2yo;
	new_child["eypp"] = eypp;

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
