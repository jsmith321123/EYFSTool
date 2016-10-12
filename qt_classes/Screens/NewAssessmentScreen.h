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
#include <QSqlDatabase>

using namespace std;

class NewAssessmentScreen : public Screen {

Q_OBJECT

public:
	NewAssessmentScreen(QSqlDatabase db);

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

	QSqlDatabase db_;
};

#endif //NEWASSESSMENTSCREEN_H