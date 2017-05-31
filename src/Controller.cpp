#include "Controller.h"

namespace Game
{
	namespace Input
	{
		const std::string cBtns::a			= "a";
		const std::string cBtns::b			= "b";
		const std::string cBtns::x			= "x";
		const std::string cBtns::y			= "y";
		const std::string cBtns::back		= "back";
		const std::string cBtns::guide		= "guide";
		const std::string cBtns::start		= "start";
		const std::string cBtns::lstick		= "leftstick";
		const std::string cBtns::rstick		= "rightstick";
		const std::string cBtns::lshoulder	= "leftshoulder";
		const std::string cBtns::rshoulder	= "rightshoulder";
		const std::string cBtns::dup			= "dpup";
		const std::string cBtns::ddown		= "dpdown";
		const std::string cBtns::dleft		= "dpleft";
		const std::string cBtns::dright		= "dpright";

		Controller::bMap Controller::Buttons
		{
			{ cBtns::a, false },
			{ cBtns::b, false },
			{ cBtns::x, false },
			{ cBtns::y, false },
			{ cBtns::guide, false },
			{ cBtns::back, false },
			{ cBtns::start, false },
			{ cBtns::dup, false },
			{ cBtns::ddown, false },
			{ cBtns::dleft, false },
			{ cBtns::dright, false },
			{ cBtns::lstick, false },
			{ cBtns::rstick, false },
			{ cBtns::lshoulder, false },
			{ cBtns::rshoulder, false }
		};

		void Controller::init()
		{
			// Check if controller is available
			if( SDL_IsGameController(0) )
			{
				// Open controller slot
				Ctrl = SDL_GameControllerOpen(0);

				// Set controller slot
				CtrlSlot = 0;

				// Get joystick and assign
				Joystick = SDL_GameControllerGetJoystick( Ctrl );

				// If controller is active, tell us it's working
				if( Ctrl && Joystick )
				{
					std::cout << "CONTROLLER FOUND & ACTIVE: " << SDL_GameControllerName(Ctrl) << std::endl;
				}
			}
		}

		// Check if button is pushed via SDL button
		bool Controller::isButtonPushed( SDL_GameControllerButton btn )
		{
			if( SDL_GameControllerGetButton( Ctrl, btn ) == 1 )
			{
				return true;
			}
			return false;
		}

		// Check if button is pushed via string
		bool Controller::isButtonPushed( std::string btn )
		{
			const char *button = btn.c_str();

			SDL_GameControllerButton checkButton = SDL_GameControllerGetButtonFromString( button );

			return isButtonPushed( checkButton );
		}

		TriggerType Controller::getTriggerPressure()
		{
			return Trigger;
		}

		void Controller::checkTriggerPressure( SDL_GameControllerAxis axis )
		{
			Sint16 axisValue = SDL_GameControllerGetAxis( Ctrl, axis );

			bool left = false, right = false;

			if( axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT ) left = true;
			if( axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT ) right = true;

			if( axisValue > 15000 )
			{
				if( left )
				{
					Trigger.Left.full = true;
					Trigger.Left.half = false;
				}
				else if( right )
				{
					Trigger.Right.full = true;
					Trigger.Right.half = false;
				}
			}
			else if( axisValue < 15000 && axisValue > 0 )
			{
				if( left )
				{
					Trigger.Left.full = false;
					Trigger.Left.half = true;
				}
				else if( right )
				{
					Trigger.Right.full = false;
					Trigger.Right.half = true;
				}
			}
			else if( axisValue == 0 )
			{
				if( left )
				{
					Trigger.Left.full = false;
					Trigger.Left.half = false;
				}
				else if( right )
				{
					Trigger.Right.full = false;
					Trigger.Right.half = false;
				}
			}
		}

		LeftStick Controller::getLeftJoystick()
		{
			return LeftJoystick;
		}

		RightStick Controller::getRightJoystick()
		{
			return RightJoystick;
		}

		// PRIVATE FUNCTION
		// Determines where a joystick is leaning and returns
		// a integer based on the type
		// 0 = no direction
		// 1 = up/left
		// 2 = down/right
		int Controller::checkAxisDirection( Sint16 value )
		{
			// Set deadzone
			int deadzone = 8000;

			// If our value is less than -8000 or greater than 8000..
			if( value < -deadzone || value > deadzone )
			{
				// If value is negative return 1
				if( value < 0 ) return 1;

				// If value is positive return 2
				if( value > 0 ) return 2;
			}

			// Return 0 otherwise
			return 0;
		}

		void Controller::eventHandler( SDL_Event *eventref )
		{
			if( Ctrl )
			{
				if( eventref->cdevice.which == CtrlSlot )
				{
					switch( eventref->type )
					{
						case SDL_CONTROLLERBUTTONDOWN:
							for( auto it = Controller::Buttons.begin(); it != Controller::Buttons.end(); ++it ) {
								if ( isButtonPushed( it->first ) ) {
									Controller::Buttons[it->first] = true;
								}
							}
							break;
						case SDL_CONTROLLERBUTTONUP:
							for( auto it = Controller::Buttons.begin(); it != Controller::Buttons.end(); ++it ) {
								Controller::Buttons[it->first] = false;
							}
							break;
						case SDL_JOYAXISMOTION:
						{
							// If left trigger is active..
							if( eventref->caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT )
							{
								// ..check trigger pressure and assign either half, full, or none
								checkTriggerPressure( SDL_CONTROLLER_AXIS_TRIGGERLEFT );
							}

							// If right trigger is active..
							if( eventref->caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT )
							{
								// ..check trigger pressure and assign either half, full, or none
								checkTriggerPressure( SDL_CONTROLLER_AXIS_TRIGGERRIGHT );
							}

							// If we're moving left or right on the left joystick..
							if( eventref->caxis.axis == SDL_CONTROLLER_AXIS_LEFTX )
							{
								// Find the direction on the axis
								int direction = checkAxisDirection( eventref->caxis.value );

								// If no direction set variables to false
								if( direction == 0 )
								{
									LeftJoystick.left = false;
									LeftJoystick.right = false;
								}
								// If direction is left set true
								else if( direction == 1 )
								{
									LeftJoystick.left = true;
								}
								// If direction is right set true
								else if( direction == 2 )
								{
									LeftJoystick.right = true;
								}
							}

							// If we're moving up or down on the left joystick
							if( eventref->caxis.axis == SDL_CONTROLLER_AXIS_LEFTY )
							{
								// Find the direction on the axis
								int direction = checkAxisDirection( eventref->caxis.value );

								// If no direction set variables to false
								if( direction == 0 )
								{
									LeftJoystick.up = false;
									LeftJoystick.down = false;
								}
								// If direction is up set true
								else if( direction == 1 )
								{
									LeftJoystick.up = true;
								}
								// If direction is down set true
								else if( direction == 2 )
								{
									LeftJoystick.down = true;
								}
							}

							// If we're moving left or right on the right joystick..
							if( eventref->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX )
							{
								// Find the direction on the axis
								int direction = checkAxisDirection( eventref->caxis.value );

								// If no direction set variables to false
								if( direction == 0 )
								{
									RightJoystick.left = false;
									RightJoystick.right = false;
								}
								// If direction is left set true
								else if( direction == 1 )
								{
									RightJoystick.left = true;
								}
								// If direction is right set true
								else if( direction == 2 )
								{
									RightJoystick.right = true;
								}
							}

							// If we're moving up or down on the right joystick
							if( eventref->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY )
							{
								// Find the direction on the axis
								int direction = checkAxisDirection( eventref->caxis.value );

								// If no direction set variables to false
								if( direction == 0 )
								{
									RightJoystick.up = false;
									RightJoystick.down = false;
								}
								// If direction is up set true
								else if( direction == 1 )
								{
									RightJoystick.up = true;
								}
								// If direction is down set true
								else if( direction == 2 )
								{
									RightJoystick.down = true;
								}
							}
							break;
						}
					}
				}
			}
		}
	}
}