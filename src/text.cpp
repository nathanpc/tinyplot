/**
 *  text.cpp
 *  Renders text.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <SDL.h>
#include <SDL_ttf.h>

#include "text.h"
using namespace std;

/**
 *  Constructor.
 */
Text::Text(string font_name, unsigned int font_size, SDL_Renderer *renderer) {
	this->renderer = renderer;

	// Initialize SDL_ttf library.
	if (TTF_Init() != 0) {
		cout << "TTF_Init() failed: " << TTF_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

	// Load a font.
	font = TTF_OpenFont(font_name.c_str(), font_size);
	if (font == NULL) {
		cout << "TTF_OpenFont() failed: " << TTF_GetError() << endl;
		TTF_Quit();
		exit(1);
	}

	// Set the font style to bold.
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
}

/**
 *  Destructor.
 */
Text::~Text() {
	TTF_CloseFont(font);
	TTF_Quit();
}

/**
 *  Prints text.
 *
 *  @param text Text to print.
 *  @param color Color of the text.
 *  @param x Texture X position.
 *  @param y Texture Y position.
 */
void Text::print(string text, SDL_Color color, int x, int y) {
	SDL_Rect source;
	SDL_Rect destination;
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;

	// Create surface from text.
	text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (text_surface == NULL) {
		cout << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}

	// Convert from surface to texture.
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_FreeSurface(text_surface);

	// Get the text size for the source rectangle.
	SDL_QueryTexture(text_texture, NULL, NULL, &source.w, &source.h);

	// Set the positions and sizes for everything.
	source.x = 0;
	source.y = 0;
	destination.y = y;
	destination.x = x;
	destination.w = source.w;
	destination.h = source.h;

	// Copy the texture to the render buffer.
	SDL_RenderCopy(renderer, text_texture, &source, &destination);
	SDL_DestroyTexture(text_texture);
}
