#include "Sprite.h"

namespace Game
{
	namespace Drawables
	{
		Sprite::Sprite( SDL_Renderer *renderer )
		{
			this->renderer = renderer;
		}

		Sprite::Sprite( SDL_Renderer *renderer, std::string location )
		{
			this->renderer = renderer;
			setPath( location );
		}

		void Sprite::setSize( unsigned int w, unsigned int h )
		{
			properties->w = w;
			properties->h = h;
		}

		void Sprite::setSize( SDL_Rect *rect )
		{
			properties->w = rect->w;
			properties->h = rect->h;
		}

		void Sprite::setPosition( unsigned int x, unsigned int y )
		{
			properties->x = x;
			properties->y = y;
		}

		void Sprite::setPosition( SDL_Rect *rect )
		{
			properties->x = rect->x;
			properties->y = rect->y;
		}

		void Sprite::setPath( std::string location )
		{
			path = location;
		}

		void Sprite::assignDefault( SDL_Rect *rect )
		{
			if( texture != nullptr && properties == nullptr )
			{
				SDL_Rect props;
				props.w = props.h = props.x = props.y = 0;

				SDL_QueryTexture( getTexture(), NULL, NULL, &props.w, &props.h );

				properties = rectPtr( new SDL_Rect( props ) );
			}
		}

		void Sprite::setTexture( SDL_Texture *texture )
		{
			this->texture = texturePtr( texture );
		}

		void Sprite::crop( SDL_Rect *rect )
		{
			croprect = rectPtr( rect );
		}

		void Sprite::render()
		{
			if( renderer != nullptr && texture != nullptr && properties != nullptr )
				if( croprect != nullptr )
					SDL_RenderCopy( renderer, getTexture(), getCroppedRect(), getProperties() );
				else
					SDL_RenderCopy( renderer, getTexture(), NULL, getProperties() );
		}

		SDL_Texture *Sprite::getTexture()
		{
			return texture.get();
		}

		SDL_Rect *Sprite::getProperties()
		{
			return properties.get();
		}

		SDL_Rect *Sprite::getCroppedRect()
		{
			return croprect.get();
		}
	}
}