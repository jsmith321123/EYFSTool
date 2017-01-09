#ifndef NEWASSESSMENTSCREEN_H
#define NEWASSESSMENTSCREEN_H

#include <iostream>

//qt
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

using namespace std;

class NewGroupDialog : public QDialog {

Q_OBJECT

public:
	NewGroupDialog();

public slots:
	void createGroup();

private:
	//labels
	QLabel groupNameLabel;
	QLabel genderLabel;
	QLabel f2yoLabel;
	QLabel negLabel;
	QLabel eyppLabel;

	//selection
	QLineEdit groupNameEdit;
	QComboBox genderCB;
	QComboBox f2yoCB;
	QComboBox negCB;
	QComboBox eyppCB;

	QPushButton submitButton;

	//layouts
	QHBoxLayout groupNameLayout;
	QHBoxLayout genderLayout;
	QHBoxLayout f2yoLayout;
	QHBoxLayout negLayout;
	QHBoxLayout eyppLayout;

	QVBoxLayout layout;

	vector<int> ids;
};

#endif //NEWASSESSMENTSCREEN_H