#include "Core.h"

namespace Game
{
	Core::~Core()
	{
		clean();
	}

	void Core::createWindow( string name, int width, int height )
	{
		window_title	= name;
		window_width	= width;
		window_height	= height;

		if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
		{
			cout << "Couldn't initialize::SDL::" << SDL_GetError() << endl;
			return;
		}

		window = SDL_CreateWindow( window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0 );

		if( window == NULL )
		{
			cout << "Couldn't initialize::Window::" << SDL_GetError() << endl;
			return;
		}

		renderer = SDL_CreateRenderer( window, -1, 0 );

		if( renderer == NULL )
		{
			cout << "Couldn't initialize::Renderer::" << SDL_GetError() << endl;
			return;
		}

		TTF_Init();

		setup();

		loop();

	}

	void Core::setup()
	{
		// Setup engine
		engine.init( renderer );
	}

	void Core::loop()
	{
		// Start tick
		start_tick = SDL_GetTicks();

		// While window is running, run events, update, and draw
		while( running )
		{
			// Set delta time
			setDelta();

			// Get frame count
			getFrameCount();

			// Run events
			events();

			// Update data
			update( delta_time );

			// Draw
			draw( delta_time );

			// Increase frame
			++n_frame;
		}
	}

	void Core::setDelta()
	{
		// Get the current frame time
		curr_time = SDL_GetTicks();
	
		// If current frame is greater than previous frame
		// 1000(ms) represents 1 second
		if( curr_time > prev_time + 1000 )
		{
			// Set previous time to current time to catch up
			prev_time = curr_time;
		}

		// Set delta time
		delta_time = (float) ( curr_time - prev_time ) / 1000;
	}

	void Core::getFrameCount()
	{
		frameRate = ( n_frame / (float) ( SDL_GetTicks() - start_tick ) ) * 1000;
	}

	void Core::events()
	{
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
				running = false;
			}
		}
	}

	void Core::update( float delta )
	{
		//engine.update( delta );
	}

	void Core::draw( float delta )
	{
		SDL_RenderClear( renderer );

		SDL_RenderPresent( renderer );
	}

	void Core::clean()
	{
		SDL_DestroyRenderer( renderer );
		SDL_DestroyWindow( window );
		SDL_Quit();
	}
}