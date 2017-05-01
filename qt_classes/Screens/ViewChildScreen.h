#ifndef VIEWCHILDSCREEN_H
#define VIEWCHILDSCREEN_H

#include "./../Screen.h"

//qt
#include <QTextEdit>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QComboBox>
#include <QPushButton>

#include "./../../libraries/json.hpp"

using json=nlohmann::json;

class ViewChildScreen : public Screen {
	Q_OBJECT

public:
	ViewChildScreen();

	void displayChild(int id);
	void updateList();
	
public slots:
	void displayChoice();
	void back();

private:
	//selection of individual child
	QComboBox selectionBox;
	QPushButton submitButton;
	QVBoxLayout layout1;

	QWidget selectionWidget;

	//showing the information about the child
	QTextEdit dataTextEdit;
	QVBoxLayout layout2;

	QPushButton backButton;

	QWidget displayWidget;

	//allowing the switch between selecting and displaying info
	QStackedLayout stackedLayout;


	json JSON;
};

#endif //VIEWCHILDSCREEN_H
