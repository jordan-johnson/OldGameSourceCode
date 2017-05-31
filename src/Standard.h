#ifndef STANDARD_H
#define STANDARD_H

#include "SDL.h"
#include <iostream>
#include <vector>
#include <map>

namespace Game
{
	namespace Input
	{
		// Mouse position
		struct MousePosition
		{
			int x, y;
		};

		// Mouse buttons (left/right)
		struct Mouse
		{
			bool left = false, right = false;
		};

		// Keyboard and mouse input
		class Standard_Input
		{
		private:
			// Mouse buttons
			Mouse MouseButtons;

			// Mouse position
			MousePosition MousePos;

			// Set the mouse position via event handler
			void setMousePosition( int xpos, int ypos );

			// Set the mouse buttons via event handler
			void setMouseButton( Uint8 button, bool pressed = true );
		public:
			// Currently pressed keys
			std::vector<SDL_Keycode> PressedKeys;

			// Check if key is pressed via SDL_Keycode
			bool isPressed( SDL_Keycode key );

			// Check if key is pressed via string
			bool isPressed( std::string key );

			// Returns the members of mouse position struct
			MousePosition getMousePosition();

			// Returns the members of mouse button struct
			Mouse getMouseButton();
	
			// Handle events
			void EventHandler( SDL_Event *eventref );
		};
	}
}

#endif