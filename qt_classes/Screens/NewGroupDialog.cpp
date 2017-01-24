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

	/*
	 * create a new object for the
	 * group and add it to the 
	 * assessments json
	 */

	json newGroupAssessment;

	//for each child go through each
	//assessment and add it to the group
	for (int childId : ids) {
		json child_;

		for (json child : assessments) {
			if (child["id"] == json(childId)
				&& child["type"] == json("individual")) {
				child_ = child;
			}
		}

		for (json assess : child_["assessments"]) {
			//find if a group assessment
			//exists for this term and year
			bool assessFound = false;
			int assessIndex;
			int i = 0;
			cout << 02 << endl;

			for (json groupAssess : newGroupAssessment["assessments"]) {
				if (groupAssess["term"] == assess["term"]
					&& groupAssess["year"] == assess["year"]) {
					assessFound = true;
					assessIndex = i;
				}

				i++;
			}

			assessIndex = (assessFound) ? (assessIndex) : (i);

			for (json area : assess["areas"]) {
				cout << 04 << endl;
				//find if the area is already
				//in the group object
				bool areaFound = false;
				int areaIndex;
				int i = 0;

				for (json groupArea : newGroupAssessment["assessments"][assessIndex]["areas"]) {
					if (groupArea["title"] == area["title"]) {
						areaFound = true;
						areaIndex = i;
					}

					i++;
				}

				areaIndex = (areaFound) ? (areaIndex) : (i);

				//set the value for this area to
				//correct average
				int currRange = 0;
				int currNumber = 0;

				if (areaFound) {
					int currRange = newGroupAssessment["assessments"][assessIndex]["areas"][areaIndex]["age_range"];
					int currNumber = newGroupAssessment["assessments"][assessIndex]["areas"][areaIndex]["number"];
				} else {
					newGroupAssessment["assessments"][assessIndex]["areas"][areaIndex]["title"] = area["title"];
				}
				
				cout << child_ << endl;

				int newRange = area["age_range"];
				int newAveRange = (currRange + newRange) / (currNumber + 1);

				newGroupAssessment["assessments"][assessIndex]["areas"][areaIndex]["age_range"] = newAveRange;
				newGroupAssessment["assessments"][assessIndex]["areas"][areaIndex]["number"] = currNumber + 1;

				cout << newGroupAssessment << endl;
			}
		}
	}

	groupsJson.push_back(newGroup);

	cout << "groups: " << groupsJson << endl;
	cout << "assessments: " << assessments << endl;

	ofstream outputGroups("./data/groups.json");
	outputGroups << groupsJson.dump();

	ofstream outputAssess("./data/group_assessments.json");
	outputAssess << assessments.dump();
}