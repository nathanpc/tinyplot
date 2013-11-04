/**
 *  tinyplot
 *  A lightweight, embeddable, graph plotting tool.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <cstdlib>
#include <SDL.h>

#include "clog.h"
#include "tinyplot.h"

#define VERSION "0.1a"
using namespace std;

TinyPlot *tinyplot;

void about();

/**
 *  That old C thing.
 *
 *  @param argc Number of arguments.
 *  @param argv Array of arguments.
 *  @return Exit code.
 */
int main(int argc, char *argv[]) {
	// Print the usual "About" message.
	about();

	// Initialize tinyplot.
	tinyplot = new TinyPlot();

	vector<float> x = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	vector<float> y = { 0, 1, 2, 21, 4, 5, 10, 7, 12, 9, 100 };

	vector<float> x2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	vector<float> y2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	tinyplot->addGraph(x, y, TinyPlot::Blue);
	tinyplot->addGraph(x2, y2, TinyPlot::Red);
	bool res = tinyplot->showGraph();

	if (!res) {
		Log::Error(tinyplot->getErrorMessage());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/**
 *  About message.
 */
void about() {
	cout << "tinyplot " << VERSION << endl;
	cout << "Copyright (c) 2013 Nathan Campos" << endl;
}
