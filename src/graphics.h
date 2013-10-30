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
	SDL_Window *window;
	SDL_Renderer *renderer;

	uint32_t frame_start;
	uint32_t frame_time;
	int fps;

  public:
	bool running;
	std::string error_message;

	Graphics();
	virtual ~Graphics();

	bool init(const char *title, int x, int y, int width, int height, int fps, int flags);
	void update();
	void render();
	void clean();

	void glLoop();
};

#endif
