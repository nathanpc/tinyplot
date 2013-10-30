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
using namespace std;

/**
 *  Constructor.
 */
Graphics::Graphics() {
	window = NULL;   // was 0
	renderer = NULL; // was 0

	frame_start = 0;
	frame_time = 0;
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
bool Graphics::init(const char *title, int x, int y, int width, int height, int fps, int flags) {
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

	this->fps = fps;

	return true;
}

/**
 *  Update stuff.
 */
void Graphics::update() {
	// Set to black.
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
}

/**
 *  Render stuff.
 */
void Graphics::render() {
	// Clear window.
	SDL_RenderClear(renderer);

	// Show the window.
	SDL_RenderPresent(renderer);
}

/**
 *  Render loop.
 */
void Graphics::glLoop() {
	while (running) {
		frame_start = SDL_GetTicks();

		// Main loop.
		//handle_events();
		update();
		render();

		frame_time = SDL_GetTicks() - frame_start;
		if (frame_time < fps) {
			SDL_Delay((int)(fps - frame_time));
		}
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
