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
#include <sstream>
#include <SDL.h>

#include "plot.h"
#include "text.h"

using namespace std;

/**
 *  Constructor.
 *
 *  @param renderer SDL_Renderer to draw.
 *  @param width Window width.
 *  @param height Window height.
 */
Plot::Plot(SDL_Renderer *renderer, int width, int height) {
	this->renderer = renderer;

	graph.width  = width;
	graph.height = height;
	graph.padding = 30;
	graph.tarea_width = graph.width - graph.padding * 2;
	graph.tarea_height = graph.height - graph.padding * 2;

	graph.bottom = graph.tarea_height + graph.padding;
	graph.right_side = graph.tarea_width + graph.padding;

	graph.font_size = 10;

	text = new Text("/usr/share/fonts/truetype/freefont/FreeSans.ttf", graph.font_size, renderer);  // TODO: Make this portable.
}

/**
 *  Draw the graph axis.
 *
 *  @param x The list of X points to trace.
 *  @param xyThe list of Y points to trace.
 */
void Plot::showAxis(vector<float> x, vector<float> y) {
	// Set the graph color.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// X Axis.
	SDL_RenderDrawLine(renderer,
					   graph.padding, graph.bottom,
					   graph.right_side, graph.bottom);

	// Y Axis.
	SDL_RenderDrawLine(renderer,
					   graph.padding, graph.padding,
					   graph.padding, graph.bottom);

	// Drawing the unit markers.
	static const unsigned int dash_width = 10;
	SDL_Color color = {30, 30, 30};

	MinMax minmax;
	minmax.x.min = *min_element(x.begin(), x.end());
	minmax.x.max = *max_element(x.begin(), x.end());
	minmax.y.min = *min_element(y.begin(), y.end());
	minmax.y.max = *max_element(y.begin(), y.end());

	// Dashes for the Y axis.
	float yspacing = 30;
	float y_dashes = graph.tarea_height / yspacing;
	
	// TODO: Remove this.
	if (y_dashes > y.size()) {
		y_dashes = y.size();
		yspacing = graph.tarea_height / y.size();
	}

	int y_interval = (minmax.y.max - minmax.y.min) / y_dashes;

	for (size_t i = 0; i < y_dashes + 1; ++i) {
		float ypos = graph.bottom - (i * yspacing);
		SDL_RenderDrawLine(renderer,
						   graph.padding, ypos,
						   graph.padding + dash_width, ypos);

		// TODO: This is wrong, it should print the scale, not the array.
		ostringstream stream;
		float font_centering = graph.font_size / 2;
		stream << i * y_interval;

		if (stream.str().length() == 2) {
			font_centering = graph.font_size;
		} else if (stream.str().length() == 3) {
			font_centering = graph.font_size + graph.font_size / 2;
		} else if (stream.str().length() == 4) {
			font_centering = graph.font_size * 2;
		} else {
			// TODO: Handle bigger values with scientific notation.
		}

		text->print(stream.str(), color, graph.padding - font_centering - dash_width, ypos - (graph.font_size / 2));
	}
}

// TODO: Add some cursors that will follow the mouse, those are going to show the user where he is in the line.

/**
 *  Plot the graph on the screen.
 *
 *  @param type Graph type.
 *  @param x The list of X points to trace.
 *  @param y The list of Y points to trace.
 */
void Plot::trace(unsigned int type, vector<float> x, vector<float> y) {
	MinMax minmax;
	minmax.x.min = *min_element(x.begin(), x.end());
	minmax.x.max = *max_element(x.begin(), x.end());
	minmax.y.min = *min_element(y.begin(), y.end());
	minmax.y.max = *max_element(y.begin(), y.end());

	float px = graph.tarea_width / (minmax.x.max - minmax.x.min);
	float py = graph.tarea_height / (minmax.y.max - minmax.y.min);

	// Set the graph color.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	for (size_t i = 1; i < x.size(); ++i) {
		Point p1;
		Point p2;

		p1.x = graph.padding + x[i - 1] * px;
		p1.y = graph.bottom - y[i - 1] * py;
		p2.x = graph.padding + x[i] * px;
		p2.y = graph.bottom - y[i] * py;

		switch (type) {
		case GRAPH_LINES:
			SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
			break;
		}
	}
}
