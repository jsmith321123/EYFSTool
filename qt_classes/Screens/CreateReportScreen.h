#ifndef CREATEREPORTSCREEN_H
#define CREATEREPORTSCREEN_H

#include "Screen.h"

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
public:
	CreateReportScreen(string type);

	void setIndividual();
	void setGroup();
	void setLearningArea();
	
	void createReport();

	string type_;

private:
	QComboBox select;
	QLabel selectLabel;
	QHBoxLayout selectLayout;

	QTextEdit detailTextEdit;

	QDateEdit startDateEdit;
	QLabel startLabel;
	QHBoxLayout startLayout;

	QDateEdit endDateEdit;
	QLabel endLabel;
	QHBoxLayout endLayout;

	QPushButton submitButton;

	QVBoxLayout layout;

	QPushButton addGroupButton;



};

#endif