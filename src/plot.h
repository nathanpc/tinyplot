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
  protected:
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

	struct Point {
		float x;
		float y;
	};

  private:
	SDL_Renderer *renderer;
	Text *text;
	std::string font;

  public:
	Graph graph;

	struct Points {
		std::vector<float> x;
		std::vector<float> y;
	};

	Plot(SDL_Renderer *renderer, int width, int height);

	void showAxis(Points points);
	void showMouseCursor(SDL_MouseMotionEvent mouse, SDL_Color color, Points points);
	void trace(unsigned int type, SDL_Color color, Points points);

	MinMax getMinMax(Points points);
};

#endif
