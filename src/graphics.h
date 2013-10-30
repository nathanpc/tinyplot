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
#include <cstdint>

class Graphics {
  private:
	uint32_t frame_start;
	uint32_t frame_time;
	int fps;

  public:
	SDL_Window *window;
	SDL_Renderer *renderer;

	bool running;
	std::string error_message;

	Graphics();
	virtual ~Graphics();

	bool init(const char *title, int x, int y, int width, int height, int fps, int flags);
	void update();
	void render();
	void clean();

	void draw(SDL_Texture *texture, int sx, int sy, int x, int y, unsigned int width, unsigned int height);
	void draw(SDL_Texture *texture, int x, int y, unsigned int width, unsigned int height);

	void glLoop();
};

#endif
