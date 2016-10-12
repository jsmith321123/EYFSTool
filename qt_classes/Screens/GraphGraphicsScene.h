#ifndef GRAPHGRAPHICSSCENE_H
#define GRAPHGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>

class GraphGraphicsScene : public QGraphicsScene {
public:
	GraphGraphicsScene();
	QGraphicsView view;

private:

	QGraphicsLineItem* x_axis;
	QGraphicsLineItem* y_axis;

	QGraphicsTextItem labels[10000];
};

#endif