#include "Engine.h"

namespace Game
{
	Engine::~Engine()
	{
		SDL_GameControllerClose( gamepad.Ctrl );
		SDL_HapticClose( haptic );
	}

	void Engine::draw( float delta )
	{
		world.draw( delta );
	}

	void Engine::update( float delta )
	{
		world.update( delta );

		if( gamepad.isButtonPushed( "a" ) && !vib )
			vib = true;
		else if( gamepad.isButtonPushed( "a" ) && vib )
			vib = false;

		while( vib )
		{
			std::cout << "k";
		}
	}

	void Engine::init( SDL_Renderer *renderer )
	{
		// Initialize controller
		gamepad.init();

		SDL_HapticOpen( 0 );

		SDL_HapticRumbleInit( haptic );

		// Try to load save file
		save.loadSave();

		world.assignInput( &kbm, &gamepad );

		// If save file exists..
		if( save.exists )
		{
			// Load world with save data
			world.init( renderer, save.get() );
		}
		else
		{
			// If save file doesn't exist, initialize first level
			world.init( renderer );
		}
	}

	void Engine::events( SDL_Event *ref )
	{
		kbm.EventHandler( ref );
		gamepad.eventHandler( ref );
	}
}