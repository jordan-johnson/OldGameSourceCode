#include "Button.h"

namespace Game
{
	namespace Drawables
	{
		Button::Button( std::string name, SDL_Renderer *r_source, Image *_open, Image *_hover )
		{
			button_name = name.c_str();
			renderer = r_source;
			open = _open;
			hover = _hover;
			button_sprite.setProperties( &_open->dimensions );
		}

		void Button::setState( state _state )
		{
			current_state = _state;
		}

		bool Button::isHovering( int x, int y )
		{
			if( button_sprite.isColliding( x, y ) ) return true;
			return false;
		}

		bool Button::isClicked( Input::Standard_Input *k_source )
		{
			if( k_source->getMouseButton().left ) return true;
			return false;
		}

		void Button::render( float delta )
		{
			if( current_state == state_open )
			{
				button_sprite.setImage( open );
			}
			else if( current_state == state_hovered )
			{
				button_sprite.setImage( hover );
			}
			button_sprite.render();
		}
	}
}