#include "Font.h"

namespace Game
{
	namespace Drawables
	{
		Font::Font( std::string source, int size )
		{
			font = TTF_OpenFont( source.c_str(), size );
		}
	}
}