#include "Game.h"

namespace Game
{
	void Game::draw( float delta )
	{
		SDL_RenderClear( renderer );

		engine.draw( delta );

		SDL_RenderPresent( renderer );
	}

	void Game::events()
	{
		while( SDL_PollEvent( &event ) )
		{
			engine.events( &event );
			if( event.type == SDL_QUIT )
			{
				running = false;
			}
		}
	}

	void Game::update( float delta )
	{
		engine.update( delta );

		// Write fps to console
		//cout << "FPS: " << frameRate << "\r";
	}
}