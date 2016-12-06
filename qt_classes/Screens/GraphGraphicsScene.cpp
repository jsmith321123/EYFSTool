#include "GraphGraphicsScene.h"
#include <math.h>

using namespace std;

GraphGraphicsScene::GraphGraphicsScene() {
	//set up the view to have the
	//correct scale and view window and
	//assign this scene to the view
	view.setScene(this);
	view.setSceneRect(-1, -1, 12, 12);
	view.scale(25, -25);
	
	//add the axis lines
	QGraphicsLineItem *x_axis = addLine(0, 0, 10, 0);
	QGraphicsLineItem *y_axis = addLine(0, 0, 0, 10);
	
	//set the colours of the data lines
	//and the axis lines
	line_pen.setColor(Qt::lightGray);
	axis_pen.setColor(Qt::red);
	
	x_axis->setPen(axis_pen);
	y_axis->setPen(axis_pen);
}

pair<pair<int, int>, pair<int, int>> GraphGraphicsScene::rLine(vector<int> x_vals, 
								vector<int> y_vals){
	/*
	 * Function that generates two points at the
	 * start and end of the "trendline" using the formula
	 * y = a + bx
	 * and a = mean y - b * mean x
	 * and b = Sxy/Sxx
	 */	

	//get the values for Sxx and Sxy
	float Sxx = getSxx(x_vals);
	float Sxy = getSxy(x_vals, y_vals);

	//get the values of a and b	
	float b = Sxy/Sxx;
	float a = mean (y_vals) - b * mean(x_vals);
	
	//get the x coords for the start and end of the line
	long int x1 = x_vals[0];
	long int x2 = x_vals[x_vals.size() - 1];

	//create the two pairs that contain the coordinates
	pair<int, int> p1 = make_pair(x1, round(a + b * x1));
	pair<int, int> p2 = make_pair(x2, round(a + b * x2));

	return make_pair(p1, p2);
}

float GraphGraphicsScene::getSxx(vector<int> x_vals) {
	/*
	 * Function that returns the "Sxx" value
	 * using the following formula
	 * sum(x^2) - sum(x)^2/n
	 */

	//calculate the sum of x and x^2
	long int sum_sqd = 0;
	long int sum = 0;

	for (int x : x_vals) {
		sum_sqd += x * x;
		sum += x;
	}

	return static_cast<int>(sum_sqd - (sum * sum) / x_vals.size());
}

float GraphGraphicsScene::getSxy(vector<int> x_vals, vector<int> y_vals) {
	/*
 	 * Function that returns the "Sxy" value
	 * using the following formula
	 * sum(x*y) - (sum(x)*sum(y))/n
	 */

	//calculate the value of sum x
	long int sum_x = 0;
	for (int x : x_vals) {
		sum_x += x;
	}
	
	//calculate the value of sum y
	long int sum_y = 0;
	for (int y : y_vals) {
		sum_y += y;
	}
	
	//calculate the value of sum xy
	long int sum_xy = 0;
	for (int i; i < x_vals.size(); i++) {
		sum_xy += y_vals[i] * x_vals[i];
	}

	return static_cast<int>(sum_xy - (sum_x * sum_y)/x_vals.size());	
}

float GraphGraphicsScene::mean(vector<int> vals) {
	/*
	 * Function that returns the 
	 * mean of the inputted values
	 */

	//calculate the sum
	long int sum = 0;
	for (int val : vals) {
		sum += val;
	}

	return sum/vals.size();
}


void GraphGraphicsScene::drawLines(vector<int> x, vector<int> y) {
	//set the colour of the trendline
    trendline_pen.setColor(Qt::blue);

    //generate the trendline with the test data
    pair<pair<int, int>, pair<int, int>>line = rLine(x, y);

    //adding the test trendline to the graph
    QGraphicsLineItem *trendline = addLine(line.first.first, line.first.second,
        							line.second.first, line.second.second);

    trendline->setPen(trendline_pen);

    //plot the data lines for the test graph
    for (int i = 1; i < x.size(); i++)
        QGraphicsLineItem *newLine = addLine(x[i-1], y[i-1], x[i], y[i]);
        newLine->setPen(line_pen);
    }	
}
