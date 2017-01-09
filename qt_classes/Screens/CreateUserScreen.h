#ifndef CREATEUSERSCREEN_H
#define CREATEUSERSCREEN_H

#include <iostream>

//qt
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>

//headers
#include "./Screen.h"

using namespace std;

class CreateUserScreen : public Screen {

Q_OBJECT

public:
	CreateUserScreen(int al);

	//user's permission level
	int al_ = 3;

public slots:
	void addUser();

private:
	bool userExists(QString user_name);

	//user_name selection
	QLabel userLabel;
	QLineEdit userLineEdit;
	QHBoxLayout userLayout;

	//password selection
	QLabel pass1Label;
	QLabel pass2Label;
	QLineEdit pass1LineEdit;
	QLineEdit pass2LineEdit;
	QHBoxLayout pass1Layout;
	QHBoxLayout pass2Layout;
	QVBoxLayout passLayout;

	//submitting
	QPushButton submitButton;

	//access level selection
	QLabel accessLabel;
	QComboBox accessComboBox;
	QHBoxLayout accessLayout;

	//feedback label
	QLabel feedbackLabel;

	//overall layout
	QVBoxLayout layout;
};

#endif
