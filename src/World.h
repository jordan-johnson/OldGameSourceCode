#ifndef WORLD_H
#define WORLD_H

#include <memory>

#include "SDL.h"

#include "JsonScript.h"
#include "DefaultCharacter.h"
#include "Standard.h"
#include "Controller.h"
#include "Sprite.h"

namespace Game
{
	namespace Level
	{
		class World
		{
		private:
			SDL_Renderer *renderer;

			Input::Standard_Input *kbm = nullptr;
			Input::Controller *ctrl = nullptr;

			// World data
			JsonScript w_data;

			// Map directory
			const std::string m_dir = DefaultCharacter::map_directory;

			// Starting map
			const std::string m_start = DefaultCharacter::map;

			void loadTerrain();
		public:
			// Initialize world w/o save file
			void init( SDL_Renderer *renderer );

			// Initialize world with save file
			void init( SDL_Renderer *renderer, JsonScript& savefile );

			void assignInput( Input::Standard_Input *s_input, Input::Controller *c_input );

			void draw( float delta = 0.0f );

			void update( float delta = 0.0f );

			void loadLevel( std::string location );
		};
	}
}

#endif