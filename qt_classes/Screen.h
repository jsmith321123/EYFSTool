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

	string name;
	int id;
	int al_;
};

#endif //SCREEN_H