#include "NewAssessmentScreen.h"
#include <QStringList>

#include <QSqlQuery>
#include <QSqlDatabase>

NewAssessmentScreen::NewAssessmentScreen (QSqlDatabase db) {
	db_ = db;

	QStringList children;

	//create and execute query
	QSqlQuery query(db_);
    query.exec(QString("SELECT * FROM child_info"));

    //loop through query and evaluate whether the user has entered
    //the correct credentials
    while (query.next()) {
        children << query.value(1).toString() + " " + query.value(2).toString();
    }

    for (QString s : children) {
    	cout << s.toStdString() << endl;
    }

    
}