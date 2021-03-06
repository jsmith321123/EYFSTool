#define __USE_MINGW_ANSI_STDIO 0
#ifndef LOADREPORTSCREEN_H
#define LOADREPORTSCREEN_H

#include "./../Screen.h"
#include "GraphGraphicsScene.h"
#include "./../../libraries/json.hpp"

//qt
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QLabel>

using namespace std;
using json = nlohmann::json;

class LoadReportScreen : public Screen {
Q_OBJECT

public:
	LoadReportScreen();

public slots:
	void chooseFile();
	void nextArea();
	void lastArea();
	void returnToSelect();

private:
	//report selection
	QPushButton selectFile;
	QVBoxLayout selectLayout;
	QWidget selectWidget;


	//report display
	//vector of graphs
	vector<GraphGraphicsScene *> graphs;
	vector<QTextEdit *> textEdits;

	QVBoxLayout displayLayout;
	QWidget displayWidget;

	QPushButton nextButton;
	QPushButton lastButton;

	QWidget laWidget;
	QVBoxLayout laLayout;

	QTextEdit laEdit;
	QPushButton* laBack = new QPushButton("Back");

	QStackedLayout *layout = new QStackedLayout();

	QLabel feedbackLabel;

	string type;
};

#endif