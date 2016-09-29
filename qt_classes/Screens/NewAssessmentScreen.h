#ifndef NEWASSESSMENTSCREEN_H
#define NEWASSESSMENTSCREEN_H

#include <iostream>

//headers
#include "../Screen.h"

//qt
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

using namespace std;

class NewAssessmentScreen : public Screen {

Q_OBJECT

public:

private:
	//child selection
	QComboBox childSelection;
	QPushButton submitButton;

	QVBoxLayout selectionLayout;

	//assessment
	QLabel areaLabel;
	QLabel subtitleLabel;
	QLabel ageRangeLabel;

	QTextEdit uniqueChildTextEdit;
	QTextEdit posRelTextEdit;
	QTextEdit enabEnvTextEdit;

	QVBoxLayout assessLayout;
};

#endif //NEWASSESSMENTSCREEN_H