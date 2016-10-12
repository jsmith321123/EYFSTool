#include <iostream>

#include "AddChildScreen.h"

#include <QSqlDatabase>
#include <QSqlQuery>

AddChildScreen::AddChildScreen(QSqlDatabase db) {
	//settings for the date edit
	dobDateEdit.setCalendarPopup(true);

	//setting the text for the labels
	forenameLabel.setText("Forename:");
	surnameLabel.setText("Surname:");
	dobLabel.setText("Date of birth:");
	emailLabel.setText("Email:");
	homeNoLabel.setText("Home number:");
	p1MobLabel.setText("1st Parent's mobile number:");
	p2MobLabel.setText("2nd Parent's mobile number:");

	//adding labels to the layout
	forenameLayout.addWidget(&forenameLabel);
	surnameLayout.addWidget(&surnameLabel);
	dobLayout.addWidget(&dobLabel);
	emailLayout.addWidget(&emailLabel);
	homeNoLayout.addWidget(&homeNoLabel);
	p1MobLayout.addWidget(&p1MobLabel);
	p2MobLayout.addWidget(&p2MobLabel);

	//adding line edits to the layout
	forenameLayout.addWidget(&forenameLineEdit);
	surnameLayout.addWidget(&surnameLineEdit);
	dobLayout.addWidget(&dobDateEdit);
	emailLayout.addWidget(&emailLineEdit);
	homeNoLayout.addWidget(&homeNoLineEdit);
	p1MobLayout.addWidget(&p1MobLineEdit);
	p2MobLayout.addWidget(&p2MobLineEdit);

	//adding the layouts to the widgets layout
	layout.addLayout(&forenameLayout);
	layout.addLayout(&surnameLayout);
	layout.addLayout(&dobLayout);
	layout.addLayout(&emailLayout);
	layout.addLayout(&homeNoLayout);
	layout.addLayout(&p1MobLayout);
	layout.addLayout(&p2MobLayout);

	layout.addWidget(&submit);

	setLayout(&layout);

	submit.setText("Submit");

	//import database
	db_ = db;

	//connections
	connect(&submit, SIGNAL(clicked()), this, SLOT(addChild()));
}

void AddChildScreen::addChild () {
	//open database
	db_.open();

	//get the contents of the fields
	QString forename = forenameLineEdit.text();
	QString surname = surnameLineEdit.text();
	QString dob = dobDateEdit.date().toString();
	QString email = emailLineEdit.text();
	QString home_no = homeNoLineEdit.text();
	QString mobile_no1 = p1MobLineEdit.text();
	QString mobile_no2 = p2MobLineEdit.text();

	//crate the query, add the attributes and then execute
	QSqlQuery query(db_);
	query.prepare("INSERT INTO child_info (forename, surname, d_o_b, email, home_no, mobile_no1, mobile_no2) "
	              "VALUES (:forename, :surname, :d_o_b, :email, :home_no, :mobile_no1, :mobile_no2)");
	query.bindValue(":forename", forename);
	query.bindValue(":surname", surname);
	query.bindValue(":d_o_b", dob);
	query.bindValue(":email", email);
	query.bindValue(":home_no", home_no);
	query.bindValue(":mobile_no1", mobile_no1);
	query.bindValue(":mobile_no2", mobile_no2);
	query.exec();
}
