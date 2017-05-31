#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <map>
#include <iostream>
#include "SDL.h"

namespace Game
{
	namespace Input
	{
		class cBtns
		{
		public:
			static const std::string a;
			static const std::string b;
			static const std::string x;
			static const std::string y;
			static const std::string back;
			static const std::string guide;
			static const std::string start;
			static const std::string lstick;
			static const std::string rstick;
			static const std::string lshoulder;
			static const std::string rshoulder;
			static const std::string dup;
			static const std::string ddown;
			static const std::string dleft;
			static const std::string dright;
		};

		struct TriggerLeft
		{
			bool half = false, full = false;
		};

		struct TriggerRight
		{
			bool half = false, full = false;
		};

		struct TriggerType
		{
			TriggerLeft Left;
			TriggerRight Right;
		};

		struct LeftStick
		{
			bool up = false, down = false, left = false, right = false;
		};

		struct RightStick
		{
			bool up = false, down = false, left = false, right = false;
		};

		class Controller
		{
		private:
			// Joystick hook
			SDL_Joystick *Joystick;

			// Trigger detection
			TriggerType Trigger;

			// Left joystick
			LeftStick LeftJoystick;

			// Right joystick
			RightStick RightJoystick;

			// Controller slot
			Uint8 CtrlSlot;

			// Button map
			typedef std::map<std::string, bool> bMap;

			// Check trigger pressure with specified axis
			void checkTriggerPressure( SDL_GameControllerAxis axis );

			// Check axis direction
			int checkAxisDirection( Sint16 value );

		public:
			// Game controller
			// Supports only one controller
			SDL_GameController *Ctrl;

			// Buttons
			static bMap Buttons;

			// Initialize controller
			void init();

			// Check if button is pushed via SDL button
			bool isButtonPushed( SDL_GameControllerButton btn );

			// Check if button is pushed via string
			bool isButtonPushed( std::string btn );

			// Returns members of triggers
			TriggerType getTriggerPressure();

			// Returns members of left joystick
			LeftStick getLeftJoystick();

			// Returns members of right joystick
			RightStick getRightJoystick();

			// Event handler for controller input
			void eventHandler( SDL_Event *eventref );
		};
	}
}

#endif