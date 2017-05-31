#include "World.h"

namespace Game
{
	namespace Level
	{
		void World::init( SDL_Renderer *renderer )
		{
			this->renderer = renderer;

			// Load level with default starting map
			loadLevel( m_start );
		}

		void World::init( SDL_Renderer *renderer, JsonScript& savefile )
		{
			this->renderer = renderer;

			// Load the level currently active
			// If there is a problem, load first level
			loadLevel( savefile.getString( "C_MAP", m_start ) );
		}

		void World::assignInput( Input::Standard_Input *s_input, Input::Controller *c_input )
		{
			kbm = s_input;
			ctrl = c_input;
		}

		void World::draw( float delta )
		{
		}

		void World::update( float delta )
		{
			//
		}

		void World::loadLevel( std::string location )
		{
			// Path to file
			std::string path = m_dir + location;

			if( w_data.fileExists( path ) )
			{
				w_data.loadFile( path );

				loadTerrain();

				if( Debug::active )
					std::cout << w_data.getInt( "M_SIZE", 0 ) << std::endl;
			}
			else
			{
				if( Debug::active )
					std::cout << "Couldn't load level::" << path << std::endl;
			}
		}

		void World::loadTerrain()
		{
			// Get terrain filename
			std::string t_filename = w_data.getString( "M_TILE", DefaultCharacter::tileset );

			// Path to file
			std::string path = DefaultCharacter::tileset_directory + t_filename;

			File file;

			if( file.exists( path ) )
			{
				// rip tiles
			}
		}
	}
}