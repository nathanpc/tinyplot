/**
 *  graphics.h
 *  Handles all the graphics stuff.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL.h>
#include <string>
#include <vector>
#include <cstdint>

#include "plot.h"

class Graphics {
  private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	Plot *plot;
	std::vector<Plot::Points> graphs;

	const uint8_t *keystates;

  public:
	bool running;
	std::string error_message;

	Graphics();
	virtual ~Graphics();

	bool init(const char *title, int x, int y, int width, int height, int flags);
	void update();
	void clean();

	void draw(SDL_Texture *texture, int sx, int sy, int x, int y, unsigned int width, unsigned int height);
	void draw(SDL_Texture *texture, int x, int y, unsigned int width, unsigned int height);

	void glLoop();
	bool isKeyDown(SDL_Scancode key);
};

#endif
