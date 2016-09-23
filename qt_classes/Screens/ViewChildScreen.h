#ifndef VIEWCHILDSCREEN_H
#define VIEWCHILDSCREEN_H

#include "../Screen.h"

//qt
#include <QTextEdit>
#include <QVBoxLayout>
#include <QStackedLayout>

class ViewChildScreen : public Screen {
	Q_OBJECT

public:
	ViewChildScreen();

private:
	QVBoxLayout layout1;

	QTextEdit dataTextEdit;
	QVBoxLayout layout2;

	QStackedLayout stackedLayout;
}

#endif //VIEWCHILDSCREEN_H