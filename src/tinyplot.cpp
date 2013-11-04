/**
 *  tinyplot.cpp
 *  Plotting tiny graphs?
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <SDL.h>

#include "tinyplot.h"
#include "graphics.h"
#include "plot.h"
using namespace std;

const SDL_Color TinyPlot::Blue = { 0, 80, 130, 255 };
const SDL_Color TinyPlot::Red  = { 130, 0, 0, 255 };

/**
 *  Constructor.
 */
TinyPlot::TinyPlot() {
	// Initialize the graph window.
	graphics = new Graphics();
}

bool TinyPlot::showGraph(string title, int width, int height, int flags) {
	// Initialize the graph window.
	graphics->running = graphics->init(title.c_str(),
									   SDL_WINDOWPOS_CENTERED,
									   SDL_WINDOWPOS_CENTERED,
									   width,
									   height,
									   flags);

	if (!graphics->running) {
		return false;
	}

	graphics->glLoop();

	return true;
}

void TinyPlot::addGraph(vector<float> x, vector<float> y, SDL_Color color) {
	Plot::Points points = { x, y };

	graphics->graphs.push_back(points);
	graphics->colors.push_back(color);
}

string TinyPlot::getErrorMessage() {
	return graphics->error_message;
}
