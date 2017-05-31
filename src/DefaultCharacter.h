#ifndef DEFAULTCHARACTER_H
#define DEFAULTCHARACTER_H

#include <string>

namespace Game
{
	struct DefaultCharacter
	{
		// Default class name
		static const std::string name;

		// Default currency
		static const unsigned int currency;

		// Default experience
		static const unsigned int experience;

		// Default skill points
		static const unsigned int skills[4];

		// Default map directory
		static const std::string map_directory;

		// Default map
		static const std::string map;

		// Default tileset directory
		static const std::string tileset_directory;
		
		// Default tileset
		static const std::string tileset;
	};
}

#endif