#include "GraphGraphicsScene.h"


GraphGraphicsScene::GraphGraphicsScene() {
	view.setScene(this);
	view.setSceneRect(0, 0, 220, 220);
	view.scale(1, -1);

	x_axis = addLine(10, 10, 210, 10);
	y_axis = addLine(10, 10, 10, 210);
}