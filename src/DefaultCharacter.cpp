#include "DefaultCharacter.h"

namespace Game
{
	const std::string DefaultCharacter::name				= "brute";

	const unsigned int DefaultCharacter::currency			= 0;

	const unsigned int DefaultCharacter::experience			= 0;

	const unsigned int DefaultCharacter::skills[]			= { 0, 0, 0, 0 };

	const std::string DefaultCharacter::map_directory		= "maps/";

	const std::string DefaultCharacter::map					= "jungle";

	const std::string DefaultCharacter::tileset_directory	= "assets/tilesets/";

	const std::string DefaultCharacter::tileset				= "jungle.gif";
}