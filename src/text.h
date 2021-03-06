/**
 *  text.h
 *  Renders text.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Text {
	private:
		SDL_Renderer *renderer;

	public:
		TTF_Font *font;

		Text(std::string font_name, unsigned int font_size, SDL_Renderer *renderer);
		~Text();

		void print(std::string text, SDL_Color color, int x, int y);
};

#endif
