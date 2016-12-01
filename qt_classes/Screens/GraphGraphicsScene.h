#ifndef GRAPHGRAPHICSSCENE_H
#define GRAPHGRAPHICSSCENE_H

#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPen>

using namespace std;

class GraphGraphicsScene : public QGraphicsScene {
public:
	GraphGraphicsScene();
	QGraphicsView view;

private:
	pair<pair<int, int>, pair<int, int>> rLine(vector<int> x_vals, vector<int> y_vals);
	float getSxx(vector<int> x_vals);
	float getSxy(vector<int> x_vals, vector<int> y_vals);
	float mean(vector<int> vals);

	QPen trendline_pen;
	QPen line_pen;	
	QPen axis_pen;

	QGraphicsLineItem* x_axis;
	QGraphicsLineItem* y_axis;

	QGraphicsTextItem labels[10000];
};

#endif
