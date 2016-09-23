#include <iostream>

#include "AddChildScreen.h"

AddChildScreen::AddChildScreen() {
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

	setLayout(&layout);
}