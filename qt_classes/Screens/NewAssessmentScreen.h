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
#include <QSqlDatabase>
#include <QStackedLayout>
#include <QWidget>
#include <QHBoxLayout>

using namespace std;
using json = nlohmann::json;

class NewAssessmentScreen : public Screen {

Q_OBJECT

public:
	NewAssessmentScreen();
	void createSelectLayout();
	void updateList();
	void createAssessmentLayout();
	void getAreas();

public slots:
	void selectChild();

	void setAreaSlot();
	void setSubareaSlot();

	void nextAgeRange();
	void lastAgeRange();

	void selectAgeRange();

private:
	void setArea(int index);
	void setSubarea(int index);

	void setAgeRange(int index);

	void nextSubarea();
	void lastSubarea();

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
	int id;

	//assessment
	QComboBox areaCb;
	QPushButton areaSet;
	QHBoxLayout areaLayout;

	QComboBox subareaCb;
	QPushButton subareaSet;
	QHBoxLayout subareaLayout;

	QTextEdit text;
	QPushButton backButton;
	QPushButton selectButton;
	QPushButton nextButton;
	QHBoxLayout buttonLayout;

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

	//json
	json details_json_;
	json assessment_json;
	json results_json_;

	vector<string> completedSa;
};

#endif //NEWASSESSMENTSCREEN_H