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
	window = NULL;
	renderer = NULL;

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
	SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
	SDL_RenderDrawLine(renderer, 10, 10, 200, 200);
}

/**
 *  Render stuff.
 */
void Graphics::render() {
	// Set the background color.
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);

	// Clear window.
	SDL_RenderClear(renderer);

	// Update the things on the screen.
	//handle_events();
	update();

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
