/**
 *  plot.cpp
 *  Plotting.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <SDL.h>

#include "plot.h"

using namespace std;

Plot::Plot(int width, int height) {
	graph.width  = width;
	graph.height = height;
}

/**
 *  Plot the graph on the screen.
 *
 *  @param type Graph type.
 *  @param points The list of points to trace.
 */
void Plot::trace(SDL_Renderer *renderer, unsigned int type, vector<int> x, vector<int> y) {
	MinMax minmax;

	minmax.x.min = *min_element(x.begin(), x.end());
	minmax.x.max = *max_element(x.begin(), x.end());
	minmax.y.min = *min_element(y.begin(), y.end());
	minmax.y.max = *max_element(y.begin(), y.end());

	float px = graph.width / (minmax.x.max - minmax.x.min);
	float py = graph.height / (minmax.y.max - minmax.y.min);

	cout << "X: " << minmax.x.min << " - " << minmax.x.max << endl;
	cout << "Y: " << minmax.y.min << " - " << minmax.y.max << endl;
	cout << "PX: " << px << " - PY: " << py << endl;

	// Set the graph color.
	SDL_SetRenderDrawColor(renderer, 0,0,0, 255);

	for (size_t i = 1; i < x.size(); ++i) {
		Point p1;
		Point p2;

		p1.x = x[i - 1] * px;
		p1.y = y[i - 1] * py;
		p2.x = x[i] * px;
		p2.y = y[i] * py;

		switch (type) {
		case GRAPH_LINES:
			SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
			// Get the horizontal spacing using (window width / points.size())
			// Get the vertical spacing using (window height / ((biggest point + lowest point) / 2)?????????
			// Maybe just make the vertical points proportional to the window heit.
			break;
		}
	}
}
