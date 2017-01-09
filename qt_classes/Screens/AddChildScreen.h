#ifndef ADDCHILDSCREEN_H
#define ADDCHILDSCREEN_H

#include <iostream>

#include "../Screen.h"

//qt
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QStringList>

class AddChildScreen : public Screen {
	
	Q_OBJECT

public:
	AddChildScreen();

public slots:
	void addChild();

private:
	QLineEdit forenameLineEdit;
	QLabel forenameLabel;
	QHBoxLayout forenameLayout;

	QLineEdit surnameLineEdit;
	QLabel surnameLabel;
	QHBoxLayout surnameLayout;

	QLineEdit knownAsLineEdit;
	QLabel knownAsLabel;
	QHBoxLayout knownAsLayout;

	QComboBox genderCB;
	QLabel genderLabel;
	QHBoxLayout genderLayout;

	QDateEdit dobDateEdit;
	QLabel dobLabel;
	QHBoxLayout dobLayout;

	QCheckBox negCheckBox;
	QLabel negLabel;
	QHBoxLayout negLayout;

	QCheckBox f2yoCheckBox;
	QLabel f2yoLabel;
	QHBoxLayout f2yoLayout;

	QCheckBox eyppCheckBox;
	QLabel eyppLabel;
	QHBoxLayout eyppLayout;

	QPushButton submit;

	QVBoxLayout layout;
};

#endif //ADDCHILDSCREEN_H
