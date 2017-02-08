#include "./EditUserScreen.h"

#include <iostream>
#include <fstream>

#include <QStringList>

#include "./../../libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

EditUserScreen::EditUserScreen() {
	//add all of the user selection components
	getUsers();

	selectLayout.addWidget(&users);
	selectLayout.addWidget(selectButton);

	layout.addLayout(&selectLayout);
	setLayout(layout);

	//add all of the user editing components
	editLayout.addWidget(passwordLabel);
	edit
}

void EditUserScreen::getUsers() {
	ifstream usersFile("./data/users.json");
	json usersJson = json::parse(usersFile);

	QStringList users;

	for (json user : usersJson) {
		users << user["user"];
	}

	users.insertItems(0, users);
}
