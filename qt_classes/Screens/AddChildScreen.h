#ifndef ADDCHILDSCREEN_H
#define ADDCHILDSCREEN_H

#include <iostream>

#include "../Screen.h"

//qt
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class AddChildScreen : public Screen {
	
	Q_OBJECT

public:
	AddChildScreen();

private:
	QLineEdit forenameLineEdit;
	QLabel forenameLabel;
	QHBoxLayout fornameLayout;

	QLineEdit surnameLineEdit;
	QLabel surnameLabel;
	QHBoxLayout surnameLayout;

	QLineEdit dobLineEdit;
	QLabel dobLabel;
	QHBoxLayout dobLayout;

	QLineEdit emailLineEdit;
	QLabel emailLabel;
	QHBoxLayout emailLayout;

	QLineEdit homeNoLineEdit;
	QLabel homeNoLabel;
	QHBoxLayout homeNoLayout;

	QLineEdit p1MobLineEdit;
	QLabel p1MobLabel;
	QHBoxLayout p1MobLayout;

	QLineEdit p2MobTextEdit;
	QLabel p2MobLabel;
	QHBoxLayout p2MobLayout;

	QVBoxLayout layout;
};

#endif //ADDCHILDSCREEN_H