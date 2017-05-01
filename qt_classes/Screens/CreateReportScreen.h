#define __USE_MINGW_ANSI_STDIO 0
#ifndef CREATEREPORTSCREEN_H
#define CREATEREPORTSCREEN_H

#include "./../Screen.h"

//qt
#include <QComboBox>
#include <QTextEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>

class CreateReportScreen : public Screen {
Q_OBJECT;

public:
	CreateReportScreen(string type, int al);

	void setIndividual();
	void setGroup();
	void setLearningArea();

	void updateGroups();
	
	void createLAReport();

	string type_;

public slots:
	void createReport();

	void newGroup();
	void getChildInfo();

private:
	int al_;

	void getChildren();
	void getTermYear();

	QComboBox select;
	QLabel selectLabel;
	QHBoxLayout selectLayout;

	QTextEdit detailTextEdit;

	QLabel startLabel;
	QComboBox startTerm;
	QComboBox startYear;
	QHBoxLayout startLayout;

	QLabel endLabel;
	QComboBox endTerm;
	QComboBox endYear;
	QHBoxLayout endLayout;

	QPushButton submitButton;

	QVBoxLayout layout;

	QPushButton addGroupButton;

	int id = 0;

	vector<QString> ranges = {"0-11 months", "8-20 months", "16-26 months",
							  "22-36 months", "30-50 months", "40-60+ months"};
};

#endif
