#ifndef SPRITE_H
#define SPRITE_H

#include <memory>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "Debug.h"

namespace Game
{
	namespace Drawables
	{
		struct texture_deleter
		{
			void operator()( SDL_Texture * stexture ) const
			{
				if( stexture != nullptr )
				{
					if( Debug::active )
						std::cout << "deleted texture" << std::endl;

					SDL_DestroyTexture( stexture );
				}
			}
		};

		typedef std::unique_ptr<SDL_Texture, texture_deleter> texturePtr;
		typedef std::unique_ptr<SDL_Rect> rectPtr;

		class Sprite
		{
		private:
			std::string path = std::string();

			SDL_Renderer *renderer = nullptr;

			texturePtr texture = nullptr;

			rectPtr properties = nullptr;

			rectPtr croprect = nullptr;
		public:
			virtual void setSize( unsigned int w, unsigned int h );

			virtual void setSize( SDL_Rect *rect );

			virtual void setPosition( unsigned int x, unsigned int y );

			virtual void setPosition( SDL_Rect *rect );

			virtual void setPath( std::string location );

			virtual void assignDefault( SDL_Rect *rect = nullptr );

			virtual void setTexture( SDL_Texture *texture );

			virtual void crop( SDL_Rect *rect );

			virtual void render();

			virtual SDL_Texture *getTexture();

			virtual SDL_Rect *getProperties();

			virtual SDL_Rect *getCroppedRect();

			Sprite( SDL_Renderer *renderer );
			Sprite( SDL_Renderer *renderer, std::string location );
		};
	}
}

#endif