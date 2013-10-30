/**
 *  tinyplot
 *  A lightweight, embeddable, graph plotting tool.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <cstdlib>

#include "clog.h"
#include "graphics.h"

#define VERSION "0.1a"
using namespace std;

Graphics *graphics;

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

	// Initialize the graph window.
	graphics = new Graphics();
	graphics->running = graphics->init("tinyplot",
									   SDL_WINDOWPOS_CENTERED,
									   SDL_WINDOWPOS_CENTERED,
									   1024,
									   768,
									   24,
									   SDL_WINDOW_RESIZABLE |
									   SDL_WINDOW_SHOWN);

	if (!graphics->running) {
		Log::Error(graphics->error_message);
		return EXIT_FAILURE;
	}

	graphics->glLoop();

	return EXIT_SUCCESS;
}

/**
 *  About message.
 */
void about() {
	cout << "tinyplot " << VERSION << endl;
	cout << "Copyright (c) 2013 Nathan Campos" << endl;
}
