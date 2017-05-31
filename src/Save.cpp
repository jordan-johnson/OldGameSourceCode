#include "Save.h"

namespace Game
{
	namespace External
	{
		JsonScript& Save::get()
		{
			return data;
		}

		void Save::loadSave()
		{
			// If save file exists..
			if( data.fileExists( location ) )
			{
				// Load it
				data.loadFile( location );

				exists = true;
			}
			else
			{
				// Otherwise create a new save file
				createSave();
			}
		}

		void Save::createSave()
		{
			// If save file doesnt exist and we can create the file
			if( !data.fileExists( location ) && data.createFile( location ) )
			{
				// Default character info
				std::string c_class = DefaultCharacter::name;
				unsigned int c_currency = DefaultCharacter::currency;
				unsigned int c_experience = DefaultCharacter::experience;
				std::string c_map = DefaultCharacter::map;
					
				// Default skill point parameters
				JValue c_skills( Json::arrayValue );

				// Loop through array of skill points
				for( auto i : DefaultCharacter::skills )
				{
					c_skills.append( i );
				}

				// Data map
				std::map<std::string, JValue> data_m {
					{ "C_CLASS", c_class },
					{ "C_CURRENCY", c_currency },
					{ "C_EXPERIENCE", c_experience },
					{ "C_SKILLS", c_skills },
					{ "C_MAP", c_map }
				};

				// Add the default values to the save data
				data.addValues( data_m );
			}
		}
	}
}