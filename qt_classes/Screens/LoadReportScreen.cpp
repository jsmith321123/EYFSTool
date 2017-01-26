#include "LoadReportScreen.h"

#include <fstream>
#include <QFileDialog>
#include <QScrollArea>
#include <QTextEdit>

LoadReportScreen::LoadReportScreen() {
	//setup the selection screen
	selectFile.setText("Select report");
	selectLayout.addWidget(&selectFile);

	selectWidget.setLayout(&selectLayout);
	layout.addWidget(&selectWidget);

	setLayout(&layout);

	//connections
	connect(&selectFile, SIGNAL(clicked()), this, SLOT(chooseFile()));
}

void LoadReportScreen::chooseFile() {
	QString filename = QFileDialog::getOpenFileName();
	cout << filename.toStdString() << endl;

	ifstream file(filename.toStdString(), ifstream::binary);
	json report = json::parse(file);
	file.close();

	type = report["type"];

	cout << report << endl;

	if (type == "individual") {
		int i = 0;

		for (json area : report["areas"]) {
			GraphGraphicsScene *new_graph = new GraphGraphicsScene();

			//get x values
			vector<int> ranges = area["ranges"];

			//get y values
			vector<int> months;
			for (int i = 0; i < ranges.size(); i++) {
				months.push_back(i);
			}

			new_graph->drawLines(months, ranges);
			QTextEdit *new_text_edit = new QTextEdit();

			graphs.push_back(new_graph);
			textEdits.push_back(new_text_edit);

			//add text to the text boxes
			int iROP = new_graph->gradient;
			string sROP = to_string(iROP);

			string comparison = (iROP == 1) ? ("the same as") :
								(iROP > 1) ? ("higher than") : ("lower than");

			string title = area["title"];

			QString text = QString::fromStdString(
				title + "\n" + 
				"Rate of progression: " + sROP + ".\n" +
				"This is " + comparison + " the national average." 
				);

			new_text_edit->setText(text);
		}

		for (int i = 0; i < graphs.size(); i++) {
			QHBoxLayout *newHLayout = new QHBoxLayout();
			QHBoxLayout *newButtonLayout = new QHBoxLayout();
			QVBoxLayout *newVLayout = new QVBoxLayout();

			QPushButton *newNButton = new QPushButton("Next");
			QPushButton *returnButton = new QPushButton("Return");
			QPushButton *newLButton = new QPushButton("Last");

			newHLayout->addWidget(&graphs[i]->view);
			newHLayout->addWidget(textEdits[i]);

			newButtonLayout->addWidget(newLButton);
			newButtonLayout->addWidget(returnButton);
			newButtonLayout->addWidget(newNButton);

			newVLayout->addLayout(newHLayout);
			newVLayout->addLayout(newButtonLayout);

			QWidget *newWidget = new QWidget();
			newWidget->setLayout(newVLayout);

			layout.addWidget(newWidget);

			//connections
			connect(newNButton, SIGNAL(clicked()), this, SLOT(nextArea()));
			connect(returnButton, SIGNAL(clicked()), this, SLOT(returnToSelect()));
			connect(newLButton, SIGNAL(clicked()), this, SLOT(lastArea()));
		}

		layout.setCurrentIndex(1);
	} else if (type == "group") {
		int i = 0;

		for (json area : report["areas"]) {
			GraphGraphicsScene *new_graph = new GraphGraphicsScene();

			//get x values
			vector<int> ranges = area["ranges"];

			//get y values
			vector<int> months;
			for (int i = 0; i < ranges.size(); i++) {
				months.push_back(i);
			}

			new_graph->drawLines(months, ranges);
			QTextEdit *new_text_edit = new QTextEdit();

			graphs.push_back(new_graph);
			textEdits.push_back(new_text_edit);

			//add text to the text boxes
			int iROP = new_graph->gradient;
			string sROP = to_string(iROP);

			string comparison = (iROP == 1) ? ("the same as") :
								(iROP > 1) ? ("higher than") : ("lower than");

			string title = area["title"];

			QString text = QString::fromStdString(
				title + "\n" + 
				"Rate of progression: " + sROP + ".\n" +
				"This is " + comparison + " the national average." 
				);

			new_text_edit->setText(text);
		}

		for (int i = 0; i < graphs.size(); i++) {
			QHBoxLayout *newHLayout = new QHBoxLayout();
			QHBoxLayout *newButtonLayout = new QHBoxLayout();
			QVBoxLayout *newVLayout = new QVBoxLayout();

			QPushButton *newNButton = new QPushButton("Next");
			QPushButton *returnButton = new QPushButton("Return");
			QPushButton *newLButton = new QPushButton("Last");

			newHLayout->addWidget(&graphs[i]->view);
			newHLayout->addWidget(textEdits[i]);

			newButtonLayout->addWidget(newLButton);
			newButtonLayout->addWidget(returnButton);
			newButtonLayout->addWidget(newNButton);

			newVLayout->addLayout(newHLayout);
			newVLayout->addLayout(newButtonLayout);

			QWidget *newWidget = new QWidget();
			newWidget->setLayout(newVLayout);

			layout.addWidget(newWidget);

			//connections
			connect(newNButton, SIGNAL(clicked()), this, SLOT(nextArea()));
			connect(returnButton, SIGNAL(clicked()), this, SLOT(returnToSelect()));
			connect(newLButton, SIGNAL(clicked()), this, SLOT(lastArea()));
		}

		layout.setCurrentIndex(1);
	}
}

void LoadReportScreen::nextArea() {
	int noOfAreas = graphs.size();
	int nextIndex = ((layout.currentIndex()) + 1) % (noOfAreas + 1);

	nextIndex = (nextIndex == 0) ? (1) : (nextIndex);

	layout.setCurrentIndex(nextIndex);
}

void LoadReportScreen::lastArea() {
	int noOfAreas = graphs.size();
	int nextIndex = (layout.currentIndex() - 1);
	nextIndex = (nextIndex < 1) ? (noOfAreas) : (nextIndex);


	layout.setCurrentIndex(nextIndex);
}

void LoadReportScreen::returnToSelect() {
	layout.setCurrentIndex(0);
	graphs.clear();
	textEdits.clear();

	for (int i = 1; i < layout.count(); i++) {
		layout.removeWidget(layout.widget(1));
	}
}