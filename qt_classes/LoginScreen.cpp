#include <iostream>

#include "LoginScreen.h"
#include "MainWindow.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>



using namespace std;

LoginScreen::LoginScreen(QSqlDatabase db) {
	userLineEdit.setPlaceholderText("Username");
	passLineEdit.setPlaceholderText("Password");

	passLineEdit.setEchoMode(QLineEdit::Password);

	loginButton.setText("Login");

	layout.addWidget(&userLineEdit);
	layout.addWidget(&passLineEdit);
	layout.addWidget(&loginButton);
	layout.addWidget(&wrongPassLabel);

	centralWidget.setLayout(&layout);
	setCentralWidget(&centralWidget);

	db_ = db;

    connect(&loginButton, SIGNAL(clicked()), this, SLOT (login()));
    connect(&passLineEdit, SIGNAL(returnPressed()), this, SLOT (login()));
}

bool LoginScreen::login() {
	QString user = userLineEdit.text();
	QString password = passLineEdit.text();

	//create and execute query
	QSqlQuery query(db_);
    query.exec(QString("SELECT * FROM users WHERE user_name='" + user + "'"));

    //loop through query and evaluate whether the user has entered
    //the correct credentials
    while (query.next()) {
        QString user_name = query.value(1).toString();
        int hashed_password = query.value(2).toInt();
        al = query.value(3).toInt();

        cout << al << endl;

        if (user_name == user && hash(password) == hashed_password) {
        	db_.close();

        	//close the login screen and open the main window
        	showMainWindow();
        } else {
        	//display incorrect credential message
        	wrongPassLabel.setText("Wrong username or password.");
        	wrongPassLabel.setStyleSheet("QLabel {color : red}");
        }
    }

	return true;
}

int LoginScreen::hash(QString string) {
	long int finalInt = 0;

	int count = 1;
	for (char c : string.toStdString()) {
		finalInt += int(c) * count + 1;

		count += 128;
	}

	finalInt = finalInt;

	return finalInt;
}

void LoginScreen::showMainWindow() {
	MainWindow *main = new MainWindow(db_, al);

	main->show();

	hide();
}
