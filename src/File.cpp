#include "File.h"

namespace Game
{
	bool File::create( const std::string location, bool overwrite )
	{
		if( !exists( location ) )
		{
			// Create file
			std::ofstream file( location );

			// Close file
			file.close();

			return true;
		}
		else
		{
			if( overwrite )
			{
				// Delete file
				destroy( location );

				// Create file
				create( location );
				
				return true;
			}
		}

		return false;
	}

	bool File::destroy( const std::string location )
	{
		if( std::remove( location.c_str() ) != 0 )
			return false;

		return true;
	}

	bool File::exists( const std::string location )
	{
		bool f_exist;

		// Open our file
		std::ifstream file( location );

		// Check to see if file exists
		if( !file.good() )
			f_exist = false;
		else
			f_exist = true;

		// Close file
		file.close();

		// Return value
		return f_exist;
	}

	bool File::writeJson( std::string filename, Json::Value data )
	{
		if( exists( filename ) )
		{
			std::ofstream file;

			file.open( filename );

			file << data;

			file.close();

			return true;
		}

		return false;
	}
}