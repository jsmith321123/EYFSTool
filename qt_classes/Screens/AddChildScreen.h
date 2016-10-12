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
#include <QSqlDatabase>
#include <QPushButton>

class AddChildScreen : public Screen {
	
	Q_OBJECT

public:
	AddChildScreen(QSqlDatabase db);

public slots:
	void addChild();

private:
	QLineEdit forenameLineEdit;
	QLabel forenameLabel;
	QHBoxLayout forenameLayout;

	QLineEdit surnameLineEdit;
	QLabel surnameLabel;
	QHBoxLayout surnameLayout;

	QDateEdit dobDateEdit;
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

	QLineEdit p2MobLineEdit;
	QLabel p2MobLabel;
	QHBoxLayout p2MobLayout;

	QPushButton submit;

	QVBoxLayout layout;

	QSqlDatabase db_;
};

#endif //ADDCHILDSCREEN_H