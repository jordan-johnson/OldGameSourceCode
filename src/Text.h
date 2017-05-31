#ifndef TEXT_H
#define TEXT_H

#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"

namespace Game
{
	namespace Drawables
	{
		class Text
		{
		private:
			SDL_Renderer *renderer;

			SDL_Surface *message;

			SDL_Texture *texture;

			int width, height;

			int wrapping = 0;

			SDL_Rect dimensions;

			TTF_Font *font;

			SDL_Color color;

			std::string display;
		public:
			void setMaximumWidth( int _width );

			void setFont( TTF_Font *_font );

			void setColor( SDL_Color _color );

			void setColor( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 0 );

			void setPlace( int x, int y );

			void init();

			void render( float delta = 0.0f ) override;

			Text(){}
			Text( SDL_Renderer *source, std::string text ); 
			~Text();
		};
	}
}

#endif