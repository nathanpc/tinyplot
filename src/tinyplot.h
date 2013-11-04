/**
 *  tinyplot.h
 *  Plotting tiny graphs?
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef TINYPLOT_H_
#define TINYPLOT_H_

#include <string>
#include <SDL.h>

#include "plot.h"
#include "graphics.h"

class TinyPlot {
  private:
	Graphics *graphics;

  public:
	static const SDL_Color Blue;
	static const SDL_Color Red;

	TinyPlot();

	bool showGraph(std::string title = "tinyplot", int width = 810, int height = 560, int flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	void addGraph(std::vector<float> x, std::vector<float> y, SDL_Color color);

	std::string getErrorMessage();
};

#endif
