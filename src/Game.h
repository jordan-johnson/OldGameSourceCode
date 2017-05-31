#ifndef GAME_H
#define GAME_H

#include "SDL.h"

#include "Core.h"

namespace Game
{
	class Game : public Core
	{
	public:
		void draw( float delta );
		void update( float delta );
		void events();

		Game(){}
		~Game(){}
	};
}

#endif