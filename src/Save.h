#ifndef SAVE_H
#define SAVE_H

#include <map>

#include "JsonScript.h"
#include "DefaultCharacter.h"

namespace Game
{
	namespace External
	{
		class Save
		{
		private:
			// Save data
			JsonScript data;

			// Location
			std::string location = "save/character";
		public:
			// Get direct save data
			JsonScript& get();

			// File existence
			bool exists = false;

			// Load save file
			void loadSave();

			// Create new save file
			void createSave();
		};
	}
}

#endif