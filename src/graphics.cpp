/**
 *  graphics.h
 *  Handles all the graphics stuff.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <SDL.h>

#include "graphics.h"
#include "plot.h"
using namespace std;

/**
 *  Constructor.
 */
Graphics::Graphics() {
	window = NULL;
	renderer = NULL;
	plot = NULL;

	running = false;
}

/**
 *  Destructor.
 */
Graphics::~Graphics() {
	clean();
}

/**
 *  Initialize SDL.
 *
 *  @param title Window title.
 *  @param x Window X position.
 *  @param y Window Y position.
 *  @param width Window width.
 *  @param height Window height.
 *  @param fps Frames per second.
 *  @param flags SDL init flags.
 *  @return True if everything initialized corrrectly.
 */
bool Graphics::init(const char *title, int x, int y, int width, int height, int flags) {
	// Initialize SDL.
	int sdl_init_status = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdl_init_status >= 0) {
		// Create a window.
		window = SDL_CreateWindow(title, x, y, width, height, flags);

		// Create the renderer.
		if (window != 0) {
			renderer = SDL_CreateRenderer(window, -1, 0);
		} else {
			error_message = "Couldn't create the SDL window";
			return false;
		}
	} else {
		error_message = "There was an error while trying to initialize SDL: " + sdl_init_status;
		return false;
	}

	plot = new Plot(renderer, width, height);

	return true;
}

/**
 *  Update stuff.
 */
void Graphics::update() {
	for (size_t i = 0; i < graphs.size(); ++i) {
		if (i == 0) {
			plot->showAxis(graphs[0]);
		}

		plot->trace(GRAPH_LINES, colors[i], graphs[i]);
	}
}

/**
 *  Render loop.
 */
void Graphics::glLoop() {
	keystates = SDL_GetKeyboardState(0);
	SDL_Event event;

	while (running && SDL_WaitEvent(&event)) {
		// Set the background color and clear the window.
		SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
		SDL_RenderClear(renderer);

		switch (event.type) {
		case SDL_KEYDOWN:
			if (isKeyDown(SDL_SCANCODE_ESCAPE)) {
				// Escape
				SDL_Quit();
				exit(EXIT_SUCCESS);
			}
			break;

		case SDL_MOUSEMOTION:
			for (size_t i = 0; i < graphs.size(); ++i) {
				plot->showMouseCursor(event.motion, i, colors[i], graphs[i]);
			}
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				SDL_Log("Window %d resized to %dx%d",
						event.window.windowID, event.window.data1,
						event.window.data2);

				plot = new Plot(renderer, event.window.data1, event.window.data2);
				break;
			}
			break;
		}

		// Update the graphs on the screen.
		update();

		// Show the window.
		SDL_RenderPresent(renderer);
	}
}

/**
 *  Clean all the trash.
 */
void Graphics::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

/**
 *  Draws a texture.
 *
 *  @param texture The texture.
 *  @param sx Source X position.
 *  @param sy Source Y postition.
 *  @param x Texture X position.
 *  @param y Texture Y position.
 *  @param width Texture width.
 *  @param height Texture height.
 */
void Graphics::draw(SDL_Texture *texture, int sx, int sy, int x, int y, unsigned int width, unsigned int height) {
	SDL_Rect source;
	SDL_Rect destination;

	// Get the texture size for the source rectangle.
	SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);

	// Set the positions and sizes for everything.
	source.x = sx * 37;
	source.y = sy * 38;
	source.w = 36;
	source.h = 38;
	destination.x = x;
	destination.y = y;
	destination.w = width;
	destination.h = height;

	// Copy the texture to the render buffer.
	SDL_RenderCopy(renderer, texture, &source, &destination);
}

/**
 *  Draws a texture.
 *
 *  @param texture The texture.
 *  @param x Texture X position.
 *  @param y Texture Y position.
 *  @param width Texture width.
 *  @param height Texture height.
 */
void Graphics::draw(SDL_Texture *texture, int x, int y, unsigned int width, unsigned int height) {
	draw(texture, 0, 0, x, y, width, height);
}

/**
 *  Check if a key is down.
 *
 *  @param key SDL_Scancode for the key you want to be tested.
 *  @return True if the key is down.
 */
bool Graphics::isKeyDown(SDL_Scancode key) {
	if (keystates != 0) {
		if (keystates[key] == 1) {
			return true;
		} else {
			return false;
		}
	}

	return false;
}
