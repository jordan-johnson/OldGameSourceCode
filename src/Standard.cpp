#include "Standard.h"

/**
 * Standard values for keys:
 *
 * A, B, C, D, E, F, G, H, I, J, L, M, N, O, P, Q, R, S, T,
 * U, V, W, X, Y, Z
 *
 * Backspace, CapsLock, Down, Escape, F(X), Left Alt, 
 * Left Ctrl, Left, Left Shift, Right Alt, Right Ctrl, Right,
 * Return, Right Shift, Space, Tab, Up
 *
 * Notes: 
 *
 * Up/Down/Left/Right refers to arrow keys
 * F(X) refers to function keys
 *
 * Other keys can be found @ https://wiki.libsdl.org/SDL_Keycode
 */

namespace Game
{
	namespace Input
	{
		/**
		 * Mouse button information
		 *
		 * SDL's (event) mouse button values are type Uint8
		 * Only values 1 (Left MB) and 3 (Right MB) are supported
		 */

		bool Standard_Input::isPressed( SDL_Keycode key )
		{
			// Create vector iterator with SDL_Keycode type
			std::vector<SDL_Keycode>::iterator it;

			// Find parameter (SDL_Keycode) in vector PressedKeys
			it = find( PressedKeys.begin(), PressedKeys.end(), key );

			// If found return true
			if( it != PressedKeys.end() )
			{
				return true;
			}
			return false;
		}

		bool Standard_Input::isPressed( std::string key )
		{
			// Temporary key that will store the SDL_Keycode
			SDL_Keycode tempKey;

			// Convert const char* to SDL_Keycode
			tempKey = SDL_GetKeyFromName( key.c_str() );

			// Create vector iterator with SDL_Keycode type
			std::vector<SDL_Keycode>::iterator it;

			// Find SDL_Keycode match in vector PressedKeys
			it = find( PressedKeys.begin(), PressedKeys.end(), tempKey );

			// If found return true
			if( it != PressedKeys.end() )
			{
				return true;
			}
			return false;
		}

		MousePosition Standard_Input::getMousePosition()
		{
			return MousePos;
		}

		void Standard_Input::setMousePosition( int xpos, int ypos )
		{
			MousePos.x = xpos;
			MousePos.y = ypos;
		}

		Mouse Standard_Input::getMouseButton()
		{
			return MouseButtons;
		}

		void Standard_Input::setMouseButton( Uint8 button, bool pressed )
		{
			// Left mouse button = 1
			// Right mouse button = 3
			if( button == 1 )
			{
				MouseButtons.left = pressed;
			}
			else if( button == 3 )
			{
				MouseButtons.right = pressed;
			}
		}

		void Standard_Input::EventHandler( SDL_Event *eventref )
		{
			// Switch based on the event type
			switch( eventref->type )
			{
				// If key pressed..
				case SDL_KEYDOWN:
				{
					// Temporary key to store SDL_Keycode
					SDL_Keycode tempKey;

					// Assign SDL_Keycode to tempKey via event
					tempKey = eventref->key.keysym.sym;

					// Create vector iterator with SDL_Keycode type
					std::vector<SDL_Keycode>::iterator it;

					// Find SDL_Keycode match in vector PressedKeys
					it = find( PressedKeys.begin(), PressedKeys.end(), tempKey );

					// If match wasnt found add key to vector
					if( it == PressedKeys.end() )
					{
						PressedKeys.push_back( tempKey );
					}
					break;
				}
				// If key is released..
				case SDL_KEYUP:
				{
					// Temporary key to store SDL_Keycode
					SDL_Keycode tempKey;

					// Assign SDL_Keycode to tempKey via event
					tempKey = eventref->key.keysym.sym;

					// Create vector iterator with SDL_Keycode type
					std::vector<SDL_Keycode>::iterator it;

					// Find SDL_Keycode match in vector PressedKeys
					it = find( PressedKeys.begin(), PressedKeys.end(), tempKey );

					// If match was found remove key from vector
					if( it != PressedKeys.end() )
					{
						PressedKeys.erase( it );
					}
					break;
				}
				case SDL_MOUSEMOTION:
					// Set the mouse position
					setMousePosition( eventref->button.x, eventref->button.y );
					break;
				case SDL_MOUSEBUTTONDOWN:
					setMouseButton( eventref->button.button );
					break;
				case SDL_MOUSEBUTTONUP:
					setMouseButton( eventref->button.button, false );
					break;
			}
		}
	}
}