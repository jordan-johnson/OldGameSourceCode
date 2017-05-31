#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include <memory>

#include "Sprite.h"
#include "Standard.h"

namespace Game
{
	namespace Drawables
	{
		class Button
		{
		private:
			SDL_Renderer *renderer;

			Image *open, *hover;

			Sprite button_sprite;
	
			std::string button_name;
		public:
			enum state
			{
				state_open, state_hovered
			};

			state current_state;

			void setProperties( SDL_Rect *properties );

			void setState( state _state );

			bool isHovering( int x, int y );

			bool isClicked( Input::Standard_Input *k_source );

			void render( float delta = 0.0f ) override;

			Button(){}

			Button( std::string name, SDL_Renderer *r_source, Image *open, Image *hover );

			~Button(){}
		};
	}
}

#endif