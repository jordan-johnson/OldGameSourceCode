#include "Game.h"

int main( int argc, char **argv )
{
	Game::Game myGame = Game::Game();
	myGame.createWindow( "My Game", 1280, 720 );

	return 0;
}