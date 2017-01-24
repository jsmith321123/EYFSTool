#ifndef LOADREPORTSCREEN_H
#define LOADREPORTSCREEN_H

#include "../Screen.h"
#include "GraphGraphicsScene.h"
#include "./../../libraries/json.hpp"

//qt
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedLayout>

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

	QStackedLayout layout;

	string type;
};

#endif