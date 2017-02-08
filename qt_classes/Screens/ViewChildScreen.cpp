#include <iostream>

#include "ViewChildScreen.h"

#include <fstream>

#include "./../../libraries/json.hpp"

//qt
#include <QStringList>
#include <QtCore>

using namespace std;
using json = nlohmann::json;

ViewChildScreen::ViewChildScreen() {	
	updateList();

	backButton.setText("Back");

	submitButton.setText("Submit");

	layout1.addWidget(&selectionBox);
	layout1.addWidget(&submitButton);
	selectionWidget.setLayout(&layout1);

	layout2.addWidget(&dataTextEdit);
	layout2.addWidget(&backButton);
	displayWidget.setLayout(&layout2);

	stackedLayout.addWidget(&selectionWidget);
	stackedLayout.addWidget(&displayWidget);

	layout1.setAlignment(Qt::AlignTop);
	
	setLayout(&stackedLayout);

	connect(&submitButton, SIGNAL(clicked()), this, SLOT(displayChoice()));
	connect(&backButton, SIGNAL(clicked()), this, SLOT(back()));

}

void ViewChildScreen::displayChoice() {
	int id = selectionBox.currentIndex();
	
	displayChild(id);
}

void ViewChildScreen::displayChild(int id) {
	json curr_child;

	for (json child : JSON) {
		if (json(id) == child["id"]) {
			curr_child = child;
		}
	}
	
	//get all of the child's information
	string name = "Name: " + curr_child["surname"].dump() + ", " 
			+ curr_child["forename"].dump();
	string knownAs = "Known as: " + curr_child["knownAs"].dump();
	string dob = "Date of birth: " + curr_child["dob"].dump();
	string neg = "NEG: " + string(((curr_child["neg"].dump() == "1") ? ("Yes") : ("No")));
	string f2yo = "F2YO: " + string(((curr_child["f2yo"].dump() == "1") ? ("Yes") : ("No")));
	string eypp = "EYPP: " + string(((curr_child["eypp"].dump() == "1") ? ("Yes") : ("No")));

	QString text = QString::fromStdString(
			name + "\n" + knownAs + "\n" +
			dob + "\n" + neg + "\n" + 
			f2yo + "\n" + eypp
		);

	dataTextEdit.setText(text);
	stackedLayout.setCurrentIndex(1);
}

void ViewChildScreen::back() {
	stackedLayout.setCurrentIndex(0);
}

void ViewChildScreen::updateList() {
	QStringList items;

	ifstream child_file("./data/children.json", ifstream::binary);
    json child_json(child_file);

    JSON = child_json;

	for (json child : child_json) {
                string surname = child["surname"].dump();
                surname = surname.substr(1, surname.length() -2);

                string forename = child["forename"].dump();
                forename = forename.substr(1, forename.length() -2);

                items << QString::fromStdString(surname + ", " + forename);
        }

        selectionBox.clear();
        selectionBox.insertItems(0, items);
}
