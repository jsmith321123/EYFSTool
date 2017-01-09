#include "LoadReportScreen.h"

#include <fstream>
#include <QFileDialog>
#include <QScrollArea>

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

			new_graph->drawLines(ranges, months);

			graphs.push_back(new_graph);			
		}

		for (GraphGraphicsScene *graph : graphs) {
			displayLayout.addWidget(&graph->view);
		}

		QScrollArea scroll;

		scroll.setWidget(&displayWidget);

		displayLayout.addSpacing(50);
		displayWidget.setLayout(&displayLayout);
		layout.addWidget(&displayWidget);

		layout.setCurrentIndex(1);
	}
}