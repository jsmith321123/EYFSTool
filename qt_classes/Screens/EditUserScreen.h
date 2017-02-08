#ifndef EDITUSERSCREEN_H
#define EDITUSERSCREEN_H

#include <iostream>

#include "../Screen.h"

#include "./../../libraries/json.hpp"

//qt
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>

using json = nlohmann::json;

class EditUserScreen : public Screen {

	Q_OBJECT

public:
	EditUserScreen();

public slots:
	void selectUser();
	void back();

private:
	//user selection
	QComboBox users;
	QPushButton *selectButton = new QPushButton("select");
	QVBoxLayout selectLayout;

	void getUsers();

	json users;
	json selectedUser;

	//editing the user
	QLineEdit password;
	QLabel *passwordLabel = new QLabel("New password");

	QLineEdit passwordConfirm;
	QLabel *passwordConfirmLabel = new QLabel("Confirm password");

	QComboBox accessLevel;
	QLabel *accessLevelLabel = new QLabel("New access level");

	//main layout to allow switching between selection
	//and editing

	void saveUser();
};

#endif //EDITUSERSCREEN_H