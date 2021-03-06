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
#include <cmath>
#include <SDL.h>
#include <SDL_ttf.h>

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

	font = "/usr/share/fonts/truetype/freefont/FreeSans.ttf";
	text = new Text(font.c_str(), graph.font_size, renderer);  // TODO: Make this portable.
}

/**
 *  Draw the graph axis.
 *
 *  @param points Points to trace.
 */
void Plot::showAxis(Points points) {
	// Set the graph color.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// X Axis.
	SDL_RenderDrawLine(renderer,
					   graph.padding, graph.bottom,
					   graph.right_side, graph.bottom);
	SDL_RenderDrawLine(renderer,
					   graph.padding, graph.padding,
					   graph.right_side, graph.padding);

	// Y Axis.
	SDL_RenderDrawLine(renderer,
					   graph.padding, graph.padding,
					   graph.padding, graph.bottom);
	SDL_RenderDrawLine(renderer,
					   graph.width - graph.padding, graph.padding,
					   graph.width - graph.padding, graph.bottom);

	// Drawing the unit markers.
	static const unsigned int dash_size = 10;
	SDL_Color color = {30, 30, 30};
	MinMax minmax = getMinMax(points);

	// Dashes for the Y axis.
	float yspacing = 50;
	int y_dashes = graph.tarea_height / yspacing;
	float y_interval = (minmax.y.max - minmax.y.min) / y_dashes;

	for (size_t i = 0; i < y_dashes + 1; ++i) {
		float ypos = graph.bottom - (i * yspacing);
		SDL_RenderDrawLine(renderer,
						   graph.padding, ypos,
						   graph.padding + dash_size, ypos);
		SDL_RenderDrawLine(renderer,
						   graph.width - graph.padding, ypos,
						   graph.width - graph.padding - dash_size, ypos);

		// Create the unit string.
		ostringstream stream;
		stream << (floorf((i * y_interval) * 100 + 0.5) / 100);

		// Get the text size to center it.
		int width, height;
		TTF_SizeText(text->font, stream.str().c_str(), &width, &height);

		// Just some alignment stuff.
		float right_padding = (dash_size / 2) * stream.str().length();
		if (stream.str().length() == 1) {
			right_padding = dash_size;
		}

		float xpos = graph.padding - (width / 2) - right_padding;
		text->print(stream.str(), color, xpos, ypos - (height / 2));
	}

	// Dashes for the X axis.
	float xspacing = 50;
	int x_dashes = graph.tarea_width / xspacing;
	float x_interval = (minmax.x.max - minmax.x.min) / x_dashes;

	for (size_t i = 0; i < x_dashes + 1; ++i) {
		float xpos = graph.padding + (i * xspacing);
		SDL_RenderDrawLine(renderer,
						   xpos, graph.bottom,
						   xpos, graph.bottom - dash_size);
		SDL_RenderDrawLine(renderer,
						   xpos, graph.padding,
						   xpos, graph.padding + dash_size);

		// Create the unit string.
		ostringstream stream;
		stream.precision(2);
		stream << i * x_interval;

		// Get the text size to center it.
		int width, height;
		TTF_SizeText(text->font, stream.str().c_str(), &width, &height);

		text->print(stream.str(), color, xpos - (width / 2), graph.bottom + (height / 2));
	}
}

/**
 *  Show cursors that follow the mouse and display the point information
 *  to the user.
 *
 *  @param mouse SDL mouse motion event struct.
 *  @param n Collumn number.
 *  @param color Matching trace color.
 *  @param points Graph points.
 */
void Plot::showMouseCursor(SDL_MouseMotionEvent mouse, unsigned int n, SDL_Color color, Points points) {
	MinMax minmax = getMinMax(points);

	float px = graph.tarea_width / (minmax.x.max - minmax.x.min);
	float py = graph.tarea_height / (minmax.y.max - minmax.y.min);

	// Set the cursor color.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	if ((mouse.x > graph.padding) && (mouse.x < (graph.width - graph.padding)) && (mouse.y < graph.bottom) && (mouse.y > graph.padding)) {
		// Render cursors
		SDL_RenderDrawLine(renderer, graph.padding, mouse.y, mouse.x, mouse.y);
		SDL_RenderDrawLine(renderer, mouse.x, mouse.y, mouse.x, graph.bottom);

		// Get graph's X and Y.
		float x = floorf(((mouse.x - graph.padding) / px) * 100 + 0.5) / 100;
		float y = floorf(((graph.bottom - mouse.y) / py) * 100 + 0.5) / 100;

		// Create the position string.
		ostringstream stream;
		stream << "(" << x << ", " << y << ")";

		// Get the text size to position it correctly.
		int width;
		TTF_SizeText(text->font, stream.str().c_str(), &width, NULL);

		// Render text.
		float xpos = (graph.width - graph.padding) - width - (graph.font_size * 9 * n);
		float ypos = (graph.padding / 2) - (graph.font_size / 2);
		text->print(stream.str(), color, xpos, ypos);
	}
}

/**
 *  Plot the graph on the screen.
 *
 *  @param type Graph type.
 *  @param color Trace color.
 *  @param points Points to trace.
 */
void Plot::trace(unsigned int type, SDL_Color color, Points points) {
	MinMax minmax = getMinMax(points);

	float px = graph.tarea_width / (minmax.x.max - minmax.x.min);
	float py = graph.tarea_height / (minmax.y.max - minmax.y.min);

	// Set the graph color.
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	for (size_t i = 1; i < points.x.size(); ++i) {
		Point p1;
		Point p2;

		p1.x = graph.padding + points.x[i - 1] * px;
		p1.y = graph.bottom - points.y[i - 1] * py;
		p2.x = graph.padding + points.x[i] * px;
		p2.y = graph.bottom - points.y[i] * py;

		switch (type) {
		case GRAPH_LINES:
			SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
			break;
		}
	}
}

/**
 *  Gets the MinMax points.
 *
 *  @param points Points.
 *  @return MinMax for points.
 */
Plot::MinMax Plot::getMinMax(Points points) {
	MinMax minmax;

	minmax.x.min = *min_element(points.x.begin(), points.x.end());
	minmax.x.max = *max_element(points.x.begin(), points.x.end());
	minmax.y.min = *min_element(points.y.begin(), points.y.end());
	minmax.y.max = *max_element(points.y.begin(), points.y.end());

	return minmax;
}
