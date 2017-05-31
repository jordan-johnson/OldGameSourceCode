#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <vector>

#include "SDL.h"

#include "Save.h"
#include "World.h"
#include "Standard.h"
#include "Controller.h"

namespace Game
{
	class Engine
	{
	private:
		External::Save save;

		Level::World world;
		
		Input::Standard_Input kbm;

		Input::Controller gamepad;

		SDL_Haptic *haptic;

		bool vib = false;
	public:
		void init( SDL_Renderer *renderer );

		void draw( float delta );

		void update( float delta );

		void events( SDL_Event *ref );

		~Engine();
	};
}

#endif