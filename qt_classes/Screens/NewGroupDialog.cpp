#include "./NewGroupDialog.h"

#include "./../../libraries/json.hpp"

#include <fstream>

using namespace std;
using json = nlohmann::json;

NewGroupDialog::NewGroupDialog() {
	groupNameLabel.setText("Group name:");
	groupNameLayout.addWidget(&groupNameLabel);
	groupNameLayout.addWidget(&groupNameEdit);

	genderLabel.setText("Gender:");
	genderLayout.addWidget(&genderLabel);
	genderLayout.addWidget(&genderCB);

	QStringList genders;
	genders << "Either" << "Male" << "Female";

	genderCB.insertItems(0, genders);

	f2yoLabel.setText("F2YO:");
	f2yoLayout.addWidget(&f2yoLabel);
	f2yoLayout.addWidget(&f2yoCB);

	QStringList yesNo;
	yesNo << "Either" << "No" << "Yes";

	f2yoCB.insertItems(0, yesNo);

	negLabel.setText("NEG:");
	negLayout.addWidget(&negLabel);
	negLayout.addWidget(&negCB);

	negCB.insertItems(0, yesNo);

	eyppLabel.setText("EYPP");
	eyppLayout.addWidget(&eyppLabel);
	eyppLayout.addWidget(&eyppCB);

	eyppCB.insertItems(0, yesNo);

	submitButton.setText("Submit");

	layout.addLayout(&groupNameLayout);
	layout.addLayout(&genderLayout);
	layout.addLayout(&f2yoLayout);
	layout.addLayout(&eyppLayout);
	layout.addLayout(&negLayout);
	layout.addWidget(&submitButton);

	setLayout(&layout);

	//connections
	connect(&submitButton, SIGNAL(clicked()), this, SLOT(createGroup()));
}

void NewGroupDialog::createGroup() {
	/*
	 * Create the new group
	 */

	//load the json containing the current groups
	ifstream groupsFile("./data/groups.json", ifstream::binary);
	json groupsJson = json::parse(groupsFile);
	groupsFile.close();

	int id = groupsJson.size();

	string name = groupNameEdit.text().toStdString();
	string gender = genderCB.currentText().toStdString();
	string f2yo = f2yoCB.currentText().toStdString();
	string neg = negCB.currentText().toStdString();
	string eypp = eyppCB.currentText().toStdString();

	int f2yoIndex = f2yoCB.currentIndex() - 1;
	int negIndex = negCB.currentIndex() - 1;
	int eyppIndex = eyppCB.currentIndex() - 1;

	//create a new object for the group
	json newGroup;
	newGroup["name"] = name;
	newGroup["gender"] = gender;
	newGroup["f2yo"] = f2yo;
	newGroup["neg"] = neg;
	newGroup["eypp"] = eypp;
	newGroup["id"] = id;

	/*
	 * Calculate the assessments for the group
	 */

	//load all existing assessments
	ifstream assessmentsFile("./data/assessments.json", ifstream::binary);
	json assessments = json::parse(assessmentsFile);
	assessmentsFile.close();

	//load all of the child info
	ifstream childrenFile("./data/children.json", ifstream::binary);
	json children = json::parse(childrenFile);
	childrenFile.close();

	//find all the ids for children
	//that fit in the group
	for (json child : children) {
		int childId = child["id"];

		bool member;

		string childGender = child["gender"];
		member = (gender == "Either") ? (true) : 
				 (gender == childGender) ? (true) : (false);

		int childF2YO = child["f2yo"];
		member = (f2yoIndex == -1 && member) ? (true) :
				 (f2yoIndex == childF2YO && member) ? (true) : (false);

		int childNEG = child["neg"];
		member = (negIndex == -1 && member) ? (true) :
				 (negIndex == childNEG && member) ? (true) : (false);

		int childEYPP = child["eypp"];
		member = (eyppIndex == -1 && member) ? (true) :
				 (eyppIndex == childEYPP && member) ? (true) : (false);

		ids.push_back(childId);
	}

	//loop through all of the children
	//in the group
	for (int childId : ids) {
		json child = children[childId];

		for (json assess : assessments[childId]["assessments"]) {
			//find if an assessment with this month
			//and year currently exists in the group
			if (true) {
				int i = 0;
				int index;
				bool found = false;

				for (json groupAssess : newGroup["assessments"]) {
					if (groupAssess["term"] == assess["term"] && 
						groupAssess["year"] == assess["year"]) {
						found = true;
						index = i;
					}

					i++;
				}

				index = (found) ? (index) : (i);

				if (!found) {
					cout << "assessment found" << endl;

					newGroup["assessments"][index]["term"] = assess["term"];
					newGroup["assessments"][index]["year"] = assess["year"];
				}

				cout << "areas: " << assess["areas"] << endl;

				for (json area : assess["areas"]) {
					cout << 0 << endl;

					//find the corresponding area index
					bool areaFound = false;
					int x = 0;
					int areaIndex;

					for (json groupArea : newGroup["assessments"][index]["areas"]) {
						if (groupArea["title"] == area["title"]) {
							areaFound = true;
							areaIndex = x;
						}

						x++;
					}

					areaIndex = (areaFound) ? (areaIndex) : (x);

					if (!areaFound) {
						newGroup["assessments"][index]["areas"][areaIndex]["title"] = area["title"];
						newGroup["assessments"][index]["areas"][areaIndex]["age_range"] = 0;
						newGroup["assessments"][index]["areas"][areaIndex]["number"] = 0;
					}

					int number = newGroup["assessments"][index]["areas"][areaIndex]["number"];
					int currentAgeRange = newGroup["assessments"][index]["areas"][areaIndex]["age_range"];

					int newAgeRange = area["age_range"];

					int newTotal = (currentAgeRange + newAgeRange) / (number + 1);

					newGroup["assessments"][index]["areas"][areaIndex]["age_range"] = newTotal;
				}
			}
		}
	}

	groupsJson.push_back(newGroup);

	cout << groupsJson << endl;

	ofstream output("./data/groups.json");
	output << groupsJson.dump();
}