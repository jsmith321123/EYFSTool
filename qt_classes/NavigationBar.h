#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <iostream>

//qt
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMainWindow>

class MainWindow;

class NavigationBar : public QWidget {
	Q_OBJECT

public:
	NavigationBar(MainWindow* mw);

public slots:
	void setAddChild();
	void setViewChild();
	void setCreateReport();
	void setCreateUser();
	void setNewAssessment();
	void setLoadReport();
	void setEditUser();
	void logOut();

private:
	void setScreen(int index);

	QPushButton *addChildButton			= 	new QPushButton("Add child");
	QPushButton *viewChildButton		= 	new QPushButton("View child");
	QPushButton *newAssessButton		= 	new QPushButton("New assessment");
	QPushButton *createReportButton		= 	new QPushButton("Create report");
	QPushButton *loadReportButton		= 	new QPushButton("Load report");
	QPushButton *createUserButton		= 	new QPushButton("Create user");
	QPushButton *editUserButton			=	new QPushButton("Edit user");
	QPushButton *logOutButton			=	new QPushButton("Log out");

	QVBoxLayout layout;

	MainWindow* mw_;
};

#endif //NAVIGATIONBAR_H
