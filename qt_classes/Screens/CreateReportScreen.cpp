#define __USE_MINGW_ANSI_STDIO 0
#include "CreateReportScreen.h"

#include <fstream>

#include "./../../libraries/json.hpp"

#include "NewGroupDialog.h"

using namespace std;
using json = nlohmann::json;

CreateReportScreen::CreateReportScreen(string type, int al) {
	al_ = al;

	type_ = type;

	if (type_ == "individual") {
		setIndividual();
	} else if (type_ == "group") {
		setGroup();
	} else if (type_ == "learning area") {
		setLearningArea();
	}

	layout.setAlignment(Qt::AlignTop);

	getTermYear();

	getChildInfo();

	//connections
	connect(&submitButton, SIGNAL(clicked()), this, SLOT(createReport()));
	connect(&addGroupButton, SIGNAL(clicked()), this, SLOT(newGroup()));
	connect(&select, SIGNAL(currentIndexChanged(int)), this, SLOT(getChildInfo()));
}

void CreateReportScreen::setIndividual() {
	submitButton.setText("submit");

	selectLabel.setText("Pick child");
	startLabel.setText("Start date");
	endLabel.setText("End date");

	selectLayout.addWidget(&selectLabel);
	selectLayout.addWidget(&select);

	startLayout.addWidget(&startLabel);
	startLayout.addWidget(&startTerm);
	startLayout.addWidget(&startYear);

	endLayout.addWidget(&endLabel);
	endLayout.addWidget(&endTerm);
	endLayout.addWidget(&endYear);

	layout.addLayout(&selectLayout);
	layout.addWidget(&detailTextEdit);
	layout.addLayout(&startLayout);
	layout.addLayout(&endLayout);
	layout.addWidget(&submitButton);

	setLayout(&layout);

	getChildren();
}

void CreateReportScreen::setGroup() {
	submitButton.setText("submit");

	addGroupButton.setText("Add group");

	selectLabel.setText("Pick group");
	startLabel.setText("Start term");
	endLabel.setText("End term");

	selectLayout.addWidget(&selectLabel);
	selectLayout.addWidget(&select);
	selectLayout.addWidget(&addGroupButton);

	startLayout.addWidget(&startLabel);
	startLayout.addWidget(&startTerm);
	startLayout.addWidget(&startYear);

	endLayout.addWidget(&endLabel);
	endLayout.addWidget(&endTerm);
	endLayout.addWidget(&endYear);

	layout.addLayout(&selectLayout);
	layout.addWidget(&detailTextEdit);
	layout.addLayout(&startLayout);
	layout.addLayout(&endLayout);
	layout.addWidget(&submitButton);

	setLayout(&layout);

	//get the list of groups
	ifstream groupsFile("./../data/groups.json", ifstream::binary);
	json groupsJson = json::parse(groupsFile);
	groupsFile.close();

	QStringList groups;

	for (json group : groupsJson) {
		string groupName = group["name"];

		groups << QString::fromStdString(groupName);
	}

	select.insertItems(0, groups);
}

void CreateReportScreen::setLearningArea() {
	submitButton.setText("submit");

	startLabel.setText("Start term");
	endLabel.setText("End term");

	startLayout.addWidget(&startLabel);
	startLayout.addWidget(&startTerm);
	startLayout.addWidget(&startYear);

	endLayout.addWidget(&endLabel);
	endLayout.addWidget(&endTerm);
	endLayout.addWidget(&endYear);

	layout.addLayout(&startLayout);
	layout.addLayout(&endLayout);
	layout.addWidget(&submitButton);

	setLayout(&layout);
}

void CreateReportScreen::getTermYear() {
	time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);

   	int year = aTime->tm_year + 1900;

   	QStringList years;

   	for (int i = 0; i < 10; i++) {
   		years << QString(QString::number(year));
   		year--;
   	}

   	QStringList terms;

   	terms << "Spring" << "Summer" << "Autumn";

   	startYear.insertItems(0, years);
   	endYear.insertItems(0, years);

   	startTerm.insertItems(0, terms);
   	endTerm.insertItems(0, terms); 
}

void CreateReportScreen::createReport() {
	if (al_ > 1) {
		QLabel* notification = new QLabel("You do not have permissions to do that");
		layout.addWidget(notification);
		return;
	}

	//get the start/end terms from the comboboxes
	string begYear = startYear.currentText().toStdString();
	string finYear = endYear.currentText().toStdString();

	string begTerm = startTerm.currentText().toStdString();
	string finTerm = endTerm.currentText().toStdString();

	int begTIndex = startTerm.currentIndex();
	int finTIndex = endTerm.currentIndex();

	//make sure that the start term
	//is before the end term
	if (stoi(begYear) > stoi(finYear)) {
		return;
	} else if (stoi(begYear) == stoi(finYear)
			&& begTIndex > finTIndex) {
		return;
	}

	//create the learning area report if needed
	if (type_ == "learning area") {
		createLAReport();
		return;
	}

	string assFileName = (type_ == "group") ? ("group_assessments.json") : ("assessments.json");

	ifstream assessmentsFile("./../data/" + assFileName, ifstream::binary);
	json assessments = json::parse(assessmentsFile);
	assessmentsFile.close();

	//get the id from the combobox
	id = select.currentIndex();

	/*
	 * Get the required data
	 * and insert it into the
	 * report json
	 */

	json data;
	json report;

	//find the json object with the data
	for (json j : assessments) {
		cout << j << endl;
		if (j["id"].dump() == to_string(id) && j["type"] == json(type_)) {
			data = j;
		}
	}

	report["chid_id"] = id;
	report["type"] = type_;

	for (json assess : data["assessments"]) {
		string term = assess["term"];
		string year = assess["year"];

		int tIndex = (term == "Spring") ? (0) :
					 (term == "Summer") ? (1) : (2);

		bool inRange = false;

		if (stoi(begYear) < stoi(year) && stoi(year) < stoi(finYear)) {
				inRange = true;
			} else if(stoi(begYear) == stoi(year)
					  && tIndex >= begTIndex) {
				inRange = true;
			} else if(stoi(finYear) == stoi(year) 
					  && tIndex <= finTIndex) {
				inRange = true;
			} else if(stoi(begYear) == stoi(year) == stoi(finYear)
					  && tIndex >= begTIndex && tIndex <= finTIndex) {
				inRange = true;
			}

		if (inRange) {
			for (json area : assess["areas"]) {
				//get the area title
				string title = area["title"].dump();
				title = title.substr(1, title.length() - 2);

				//get the age range
				int ageRange = area["age_range"];

				//find where in the report this area is
				bool found = false;
				int index = 0;
				int i = 0;

				//loop through existing areas
				//in the report
				for (json exArea : report["areas"]) {
					//get the existing title for
					//the current area in the report
					string exTitle = exArea["title"];

					if (exTitle == title) {
						found = true;
						index = i;
					}

					i++;
				}

				if (!found) {
					//if the area was not found
					//add a new object to the list
					//with the areas title
					json newArea;
					newArea["title"] = title;
					newArea["ranges"].push_back(ageRange + 1);

					report["areas"].push_back(newArea);
				} else {
					//if it was found modify
					//the existing object
					report["areas"][index]["ranges"].push_back(ageRange + 1);
				}
			}
		}
	}

	/*
	 * Save the report to a new
	 * file, with a name including
	 * the child's name and the current date
	 */

	//get current date
	time_t t = time(0);
    struct tm * now = localtime(&t);

    string day = to_string(now->tm_mday);
    string month = to_string(now->tm_mon + 1);
    string year = to_string(now->tm_year + 1900);
    string date = day + "-" + month + "-" + year;

    //create the file name
	string file_name = select.currentText().toStdString() + " " + date + " " + 
	begTerm + "_" + begYear + "_to_" + finTerm + "_" + finYear +".json";

	ofstream output("./reports/" + file_name);
	output << report.dump();
}

void CreateReportScreen::createLAReport() {
	//get the start/end terms from the comboboxes
	string begYear = startYear.currentText().toStdString();
	string finYear = endYear.currentText().toStdString();

	string begTerm = startTerm.currentText().toStdString();
	string finTerm = endTerm.currentText().toStdString();

	int begTIndex = startTerm.currentIndex();
	int finTIndex = endTerm.currentIndex();

	//read the assessments file
	ifstream assessmentsFile("./../data/assessments.json", ifstream::binary);
	json assessments = json::parse(assessmentsFile);
	assessmentsFile.close();

	/*
	 * Get the required data
	 * and insert it into the
	 * report json
	 */

	json report;

	report["type"] = type_;

	for (json child : assessments) {
		for (json assess : child["assessments"]) {
			//find if this assessment
			//is in the age range
			string term = assess["term"];
			string year = assess["year"];

			int tIndex = (term == "Spring") ? (0) :
						 (term == "Summer") ? (1) : (2);

			bool inRange = false;

			//check if the assessment is in range
			if (stoi(begYear) < stoi(year) && stoi(year) < stoi(finYear)) {
				inRange = true;
			} else if(stoi(begYear) == stoi(year)
					  && tIndex >= begTIndex) {
				inRange = true;
			} else if(stoi(finYear) == stoi(year) 
					  && tIndex <= finTIndex) {
				inRange = true;
			} else if(stoi(begYear) == stoi(year) == stoi(finYear)
					  && tIndex >= begTIndex && tIndex <= finTIndex) {
				inRange = true;
			}

			if (inRange) {
				for (json area : assess["areas"]) {
					//get the age range and title for this area
					int ageRange = area["age_range"];

					string aRTitle = ranges[ageRange].toStdString();
					string title = area["title"];

					//find where in the report this area is
					bool found = false;
					int index = -1;
					int i = 0;

					//loop through existing areas
					//in the report
					for (json exArea : report["areas"]) {
						//get the existing title for
						//the current area in the report
						string exTitle = exArea["title"];

						if (exTitle == title) {
							found = true;
							index = i;
						}

						i++;
					}

					if (i == -1) {
						index = i;
					}

					if (!found) {
						json newArea;
						newArea["title"] = title;
						newArea[aRTitle] = 1;
						report["areas"].push_back(newArea);
					} else {
						//if the age range doesn't
						//currently have a value set
						//it to 1
						if (report["areas"][index][aRTitle] == json()) {
							report["areas"][index][aRTitle] = 1;
						} else {
							int currTotal = report["areas"][index][aRTitle];
							report["areas"][index][aRTitle] = currTotal + 1;
						}
					}
				}
			}
		}
	}

	//get current date
	time_t t = time(0);
    struct tm * now = localtime(&t);

    string day = to_string(now->tm_mday);
    string month = to_string(now->tm_mon + 1);
    string year = to_string(now->tm_year + 1900);
    string date = day + "-" + month + "-" + year;

	//create the file name
	string file_name = "Learning_Areas_" + date + "_" + begTerm + 
	"_" + begYear + "_to_" + finTerm + "_" + finYear + ".json";

	ofstream output("./reports/" + file_name);
	output << report.dump();
}

void CreateReportScreen::getChildren() {
	QStringList items;

	ifstream child_file("./../data/children.json", ifstream::binary);
    json child_json(child_file);

	for (json child : child_json) {
        string surname = child["surname"].dump();
        surname = surname.substr(1, surname.length() -2);

        string forename = child["forename"].dump();
        forename = forename.substr(1, forename.length() -2);

        items << QString::fromStdString(surname + ", " + forename);
 	}

    select.insertItems(0, items);
}

void CreateReportScreen::newGroup() {
    NewGroupDialog *dialog = new NewGroupDialog(this);
    dialog->show();
}

void CreateReportScreen::getChildInfo() {
	id = select.currentIndex();

	if (id < 0) {
		return;
	}

	ifstream child_file("./../data/children.json", ifstream::binary);
    json child_json = json::parse(child_file);

    json curr_child = child_json[id];
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

	detailTextEdit.setText(text);
}
