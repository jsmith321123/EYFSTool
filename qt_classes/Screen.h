#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>

//qt
#include <QWidget>

using namespace std;

class Screen : public QWidget {

Q_OBJECT

public:
	Screen();
	virtual void updateList();

	string name;
	int id;
	int al_;
};

#endif //SCREEN_H
