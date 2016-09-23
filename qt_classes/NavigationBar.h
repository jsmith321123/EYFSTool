#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <iostream>

//qt
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class NavigationBar : public QWidget {
	Q_OBJECT

public:
	NavigationBar();
private:
	QPushButton *addChildButton		= new QPushButton("Add child");
	QPushButton *viewChildButton	= new QPushButton("View child");
	QPushButton *newAssessButton	= new QPushButton("New assessment");
	QPushButton *createReportButton	= new QPushButton("Create report");
	QPushButton *loadReportButton	= new QPushButton("Load report");

	QVBoxLayout layout;
};

#endif //NAVIGATIONBAR_H