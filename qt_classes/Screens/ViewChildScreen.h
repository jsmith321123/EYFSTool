#ifndef VIEWCHILDSCREEN_H
#define VIEWCHILDSCREEN_H

#include "../Screen.h"

//qt
#include <QTextEdit>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QComboBox>
#include <QPushButton>

class ViewChildScreen : public Screen {
	Q_OBJECT

public:
	ViewChildScreen();

private:
	//selection of individual child
	QComboBox selectionBox;
	QPushButton submitButton;
	QVBoxLayout layout1;

	QWidget selectionWidget;

	//showing the information about the child
	QTextEdit dataTextEdit;
	QVBoxLayout layout2;

	QWidget displayWidget;

	//allowing the switch between selecting and displaying info
	QStackedLayout stackedLayout;
};

#endif //VIEWCHILDSCREEN_H