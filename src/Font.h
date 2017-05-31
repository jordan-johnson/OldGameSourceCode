#ifndef FONT_H
#define FONT_H

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

namespace Game
{
	namespace Drawables
	{
		class Font
		{
		public:
			TTF_Font *font;
			Font( std::string source, int size );
			~Font(){ TTF_CloseFont( font ); }
		};
	}
}

#endif