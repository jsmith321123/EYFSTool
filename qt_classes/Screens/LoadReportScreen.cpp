#define __USE_MINGW_ANSI_STDIO 0
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
	layout->addWidget(&selectWidget);

	setLayout(layout);

	//connections
	connect(&selectFile, SIGNAL(clicked()), this, SLOT(chooseFile()));
	connect(laBack, SIGNAL(clicked()), this, SLOT(returnToSelect()));
}

void LoadReportScreen::chooseFile() {
	QString filename = QFileDialog::getOpenFileName();
	cout << filename.toStdString() << endl;

	ifstream file(filename.toStdString(), ifstream::binary);
	json report = json::parse(file);
	file.close();

	type = report["type"];

	cout << report << endl;

	/*
		Displays the reports, individual and group
		reports will be a sequence of screens with
		a text box and graph, where as the learning
		area reports will just be a text box,
		individual reports will also give a brief 
		description of progression/regression
	 */

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

			/*
			 *	Add text to the boxes
			 */

			//calculate how the child's progression
			//compares to the national average
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

			layout->addWidget(newWidget);

			//connections
			connect(newNButton, SIGNAL(clicked()), this, SLOT(nextArea()));
			connect(returnButton, SIGNAL(clicked()), this, SLOT(returnToSelect()));
			connect(newLButton, SIGNAL(clicked()), this, SLOT(lastArea()));
		}

		layout->setCurrentIndex(1);
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

			layout->addWidget(newWidget);

			//connections
			connect(newNButton, SIGNAL(clicked()), this, SLOT(nextArea()));
			connect(returnButton, SIGNAL(clicked()), this, SLOT(returnToSelect()));
			connect(newLButton, SIGNAL(clicked()), this, SLOT(lastArea()));
		}

		layout->setCurrentIndex(1);
	} else if (type == "learning area") {
		//vector of age ranges
		vector<string> ranges = {"0-11 months", "8-20 months", "16-26 months",
							     "22-36 months", "30-50 months", "40-60+ months"};

		//generate a string for each area
		//and append it to the list
		QString areas = "Learning Area Report \n\n";

		for (json area : report["areas"]) {
			string areaTitle = area["title"];
			string tempArea = areaTitle + "\n";
			for (string range : ranges) {
				string tempRange;
				if (area[range] != NULL) {
					int val = area[range];
					tempRange = range + ": " + to_string(val) + " children. \n";
					tempArea += tempRange;
				}
			}

			areas += QString::fromStdString(tempArea + "\n");
		}

		//setup the text box and add it to the layout
		laEdit.setText(areas);
		laLayout.addWidget(&laEdit);
		laLayout.addWidget(laBack);

		laWidget.setLayout(&laLayout);
		layout->addWidget(&laWidget);

		layout->setCurrentIndex(1);
	}
}

void LoadReportScreen::nextArea() {
	int noOfAreas = graphs.size();
	int nextIndex = ((layout->currentIndex()) + 1) % (noOfAreas + 1);

	nextIndex = (nextIndex == 0) ? (1) : (nextIndex);

	layout->setCurrentIndex(nextIndex);
}

void LoadReportScreen::lastArea() {
	int noOfAreas = graphs.size();
	int nextIndex = (layout->currentIndex() - 1);
	nextIndex = (nextIndex < 1) ? (noOfAreas) : (nextIndex);


	layout->setCurrentIndex(nextIndex);
}

void LoadReportScreen::returnToSelect() {
	//remove the old layout and add a fresh one
	layout->setCurrentIndex(0);

	delete(layout);

	layout = new QStackedLayout();
	layout->addWidget(&selectWidget);

	setLayout(layout);

	graphs.clear();
	textEdits.clear();

	for (int i = 1; i < layout->count(); i++) {
		layout->removeWidget(layout->widget(1));
	}
}