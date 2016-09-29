#include <iostream>

#include "ViewChildScreen.h"

//qt
#include <QStringList>
#include <QtCore>

ViewChildScreen::ViewChildScreen() {
	QStringList items;
	items << "test1" << "test2" << "test3" << "test4";
	selectionBox.insertItems(0, items);

	submitButton.setText("Submit");

	layout1.addWidget(&selectionBox);
	layout1.addWidget(&submitButton);
	selectionWidget.setLayout(&layout1);

	layout2.addWidget(&dataTextEdit);
	displayWidget.setLayout(&layout2);

	stackedLayout.addWidget(&selectionWidget);
	stackedLayout.addWidget(&displayWidget);

	layout1.setAlignment(Qt::AlignTop);
	
	setLayout(&stackedLayout);
}