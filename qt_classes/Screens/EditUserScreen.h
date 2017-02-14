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
#include <QStackedLayout>
#include <QHBoxLayout>

using json = nlohmann::json;

class EditUserScreen : public Screen {

	Q_OBJECT

public:
	EditUserScreen(int al);
	
	void updateList();

public slots:
	void selectUser();
	void back();

	void saveUser();
	void deleteUser();

private:
	//user selection
	QComboBox usersCB;
	QPushButton *selectButton = new QPushButton("Select");
	QVBoxLayout selectLayout;

	QWidget selectWidget;


	json selectedUser;
	json usersJson;

	//editing the user
	QLineEdit passwordLE;
	QLabel *passwordLabel = new QLabel("New password");
	QHBoxLayout passwordLayout;

	QLineEdit passwordConfirmLE;
	QLabel *passwordConfirmLabel = new QLabel("Confirm password");
	QHBoxLayout passwordConfirmLayout;

	QComboBox accessLevelCB;
	QLabel *accessLevelLabel = new QLabel("New access level");
	QHBoxLayout accessLevelLayout;
	QPushButton *deleteButton = new QPushButton("Delete");


	QPushButton* saveButton = new QPushButton("Save");

	QVBoxLayout editLayout;

	QWidget editWidget;

	//main layout to allow switching between selection
	//and editing
	QStackedLayout layout;

	//store the user's id
	int id;
};

#endif //EDITUSERSCREEN_H
