/**
 *  plot.h
 *  Plotting.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef _PLOT_H_
#define _PLOT_H_

#include <string>
#include <vector>
#include <SDL.h>

#include "text.h"

#define GRAPH_LINES  0
#define GRAPH_POINTS 1

class Plot {
  private:
	SDL_Renderer *renderer;
	Text *text;
	std::string font;

	struct MinMax {
		struct MM {
			float min;
			float max;
		};

		MM x;
		MM y;
	};

	struct Graph {
		int width;
		int height;

		int padding;
		int tarea_width;
		int tarea_height;

		int bottom;
		int right_side;

		unsigned int font_size;
	};

  public:
	Graph graph;

	Plot(SDL_Renderer *renderer, int width, int height);

	void showAxis(std::vector<float> x, std::vector<float> y);
	void trace(unsigned int type, std::vector<float> x, std::vector<float> y);

	struct Point {
		float x;
		float y;
	};
};

#endif
