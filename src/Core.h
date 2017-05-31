#ifndef CORE_H
#define CORE_H

#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Engine.h"

using namespace std;

namespace Game
{
	class Core
	{
	protected:
		// Window title
		string window_title = string();

		// Window dimensions
		int window_width = 0, window_height = 0;

		// Is the window running
		bool running = true;
	private:
		// Previous and current times
		// Uses SDL_GetTicks()
		unsigned int prev_time = 0, curr_time;

		// Current frame count
		unsigned int n_frame = 0;

		// Start tick
		Uint32 start_tick;

		// Delta time
		float delta_time = 0.0f;

		// Game loop
		void loop();

		// Setup
		void setup();

		// Set delta time
		void setDelta();
	
		// Get frame count
		void getFrameCount();
	public:
		Core(){}

		// Core deconstructor
		// Calls clean function
		~Core();

		// SDL window
		SDL_Window *window;

		// SDL renderer
		SDL_Renderer *renderer;

		// SDL event
		SDL_Event event;

		// Game instance
		Engine engine;

		// Framerate
		double frameRate = 0;

		// Create window
		virtual void createWindow( string name, int width, int height );

		// Drawing
		virtual void draw( float delta ) = 0;

		// Events
		virtual void events() = 0;

		// Update
		virtual void update( float delta ) = 0;

		// Clean up
		virtual void clean();
	};
}

#endif