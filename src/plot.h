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

#define GRAPH_LINES  0
#define GRAPH_POINTS 1

class Plot {
  private:
	struct MinMax {
		struct MM {
			int min;
			int max;
		};

		MM x;
		MM y;
	};

	struct Graph {
		int width;
		int height;
	};

  public:
	Graph graph;

	Plot(int width, int height);

	void trace(SDL_Renderer *renderer, unsigned int type, std::vector<int> x, std::vector<int> y);

	struct Point {
		int x;
		int y;
	};
};

#endif
