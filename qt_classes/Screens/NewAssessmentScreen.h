#ifndef NEWASSESSMENTSCREEN_H
#define NEWASSESSMENTSCREEN_H

#include <iostream>

//headers
#include "../Screen.h"

#include "./../../libraries/json.hpp"

//qt
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedLayout>
#include <QWidget>
#include <QHBoxLayout>

using namespace std;
using json = nlohmann::json;

class NewAssessmentScreen : public Screen {

Q_OBJECT

public:
	NewAssessmentScreen();
	void updateList();
	void getAreas();
	void calculateGroupValues();

public slots:
	void selectChild();

	void setAreaSlot();
	void setSubareaSlot();

	void nextAgeRange();
	void lastAgeRange();

	void nextSubarea();
	void lastSubarea();

	void nextArea();
	void lastArea();

	void selectAgeRange();

	void saveAssessment();

private:
	void setArea(int index);
	void setSubarea(int index);

	void createSelectLayout();
	void createAssessmentLayout();

	void setAgeRange(int index);

	void loadAssessment();

	void setLastAssessedAR();

	int getIndex(int a, int s);

	string getYear(string term);

	//child selection
	QComboBox childSelection;
	QComboBox termSelection;
	QPushButton submitButton;

	QVBoxLayout selectionLayout;
	QWidget selectionWidget;

	//info taken from selection screen
	string name;
	string year;
	string term;
	string gender;
	int id;

	int childIndex;

	//assessment
	QPushButton areaBack;
	QComboBox areaCb;
	QPushButton areaSet;
	QHBoxLayout areaLayout;
	QPushButton areaNext;

	QPushButton subareaBack;
	QComboBox subareaCb;
	QPushButton subareaSet;
	QHBoxLayout subareaLayout;
	QPushButton subareaNext;

	QTextEdit text;
	QPushButton backButton;
	QPushButton selectButton;
	QPushButton nextButton;
	QHBoxLayout buttonLayout;
	QPushButton saveButton;

	QVBoxLayout assessLayout;
	QWidget assessWidget;

	QStackedLayout layout;

	//assessment details
	vector<pair<QString, QStringList>> subareas;

	int areaIndex = 0;
	int subareaIndex = 0;
	int ageRange = 0;

	vector<QString> ranges = {"0-11 months", "8-20 months", "16-26 months",
							  "22-36 months", "30-50 months", "40-60+ months"};


	//find whether assessment exits
	bool assessExists = false;
	int assessIndex = 0;

	//json
	json details_json_;
	json assessment_json;
	json prev_assessment_json;
	json results_json_;
	json oldAssJson;

	json child_;

	vector<string> completedSa;
	map<string, int> prevAgeRanges;
};

#endif //NEWASSESSMENTSCREEN_H