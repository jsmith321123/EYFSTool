#include <iostream>

#include "LoginScreen.h"
#include "MainWindow.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>


using namespace std;

LoginScreen::LoginScreen(MainWindow *mw) {
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

	mw_ = mw;

	//setup database connection for checking credentials
	db.setHostName("localhost");
	db.setDatabaseName("EYFSTool");
	db.setUserName("root");
	db.setPassword("1011josh");

	bool ok = db.open();

	cout << ok << endl;
	
    connect(&loginButton, SIGNAL(clicked()), this, SLOT (login()));
}

bool LoginScreen::login() {
	QString user = userLineEdit.text();
	QString password = passLineEdit.text();

	//create and execute query
	QSqlQuery query(db);
    query.exec(QString("SELECT * FROM users"));

    //loop through query and evaluate whether the user has entered
    //the correct credentials
    while (query.next()) {
        QString user_name = query.value(1).toString();
        QString hashed_password = query.value(2).toString();

        if (user_name == user && hash(password) == hashed_password) {
        	//close the login screen and open the main window
        	showMainWindow();
        } else {
        	//display incorrect credential message
        	wrongPassLabel.setText("Wrong username or password.");
        }
    }

	return true;
}

QString LoginScreen::hash(QString string) {
	return string;
}

void LoginScreen::showMainWindow() {
	mw_->show();
	hide();
}