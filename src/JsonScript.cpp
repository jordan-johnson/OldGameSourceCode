#include "JsonScript.h"

namespace Game
{
	std::string JsonScript::ext( std::string value )
	{
		// Assign file extension
		std::string val = ( stringFind( value, ".json" ) ) ? value : value + ".json";

		return val;
	}

	bool JsonScript::loadFile( const std::string location )
	{
		// Assign file extension
		std::string loc = ext( location );

		// If file does not exist.. push load error
		if( !fileExists( loc ) )
		{
			pushError( LOAD, loc );
			return false;
		}
		
		// Load file
		std::ifstream file( loc );

		// Assign file name
		filename = loc;

		// Check parser success and assign file data
		bool parse_success = reader.parse( file, data );

		// If not successful.. push parse error
		if( !parse_success )
		{
			pushError( PARSER );
			return false;
		}

		file.close();

		return true;
	}

	bool JsonScript::createFile( const std::string location, bool overwrite )
	{
		// Assign file extension
		std::string loc = ext( location );

		// Assign file name
		filename = loc;

		File file;

		if( file.create( loc, overwrite ) )
			return true;

		return false;
	}

	bool JsonScript::deleteFile( const std::string location )
	{
		// Assign file extension
		std::string loc = ext( location );

		File file;

		if( !file.destroy( loc ) )
		{
			pushError( DELETION );
			return false;
		}

		return true;
	}

	bool JsonScript::fileExists( std::string location )
	{
		// Assign file extension
		std::string loc = ext( location );

		File file;
		
		if( file.exists( loc ) )
			return true;

		return false;
	}

	std::string JsonScript::getString( std::string name, std::string val  )
	{
		if( !errors )
			return data.get( name, val ).asString();

		return std::string();
	}

	int JsonScript::getInt( std::string name, int val )
	{
		if( !errors )
			return data.get( name, val ).asInt();

		return 0;
	}

	float JsonScript::getFloat( std::string name, float val )
	{
		if( !errors )
			return data.get( name, val ).asFloat();

		return 0.0f;
	}

	Json::Value& JsonScript::getJson()
	{
		return data;
	}

	bool JsonScript::addValues( std::map<std::string, JValue> arr )
	{
		for( auto &i : arr )
		{
			data[i.first] = i.second;
		}

		File file;

		if( !file.writeJson( filename, data ) )
		{
			pushError( WRITING );
			return false;
		}

		return true;
	}

	void JsonScript::pushError( E_TYPES type, std::string extra )
	{
		// Errors found
		errors = true;

		if( Debug::active )
		{
			// Error message
			std::string e_msg = "JsonScript Error::";

			// Error message switch
			switch( type )
			{
			case LOAD:
				e_msg += "File could not be found";
				break;
			case PARSER:
				e_msg += "Could not parse file\n";
				e_msg += reader.getFormattedErrorMessages();
				break;
			case DELETION:
				e_msg += "Could not delete file";
				break;
			case WRITING:
				e_msg += "Could not write file";
				break;
			}

			if( !extra.empty() )
				e_msg += "::" + extra;
			

			// Write message
			std::cout << e_msg << std::endl;
		}
	}

	bool JsonScript::stringFind( const std::string original, const std::string piece )
	{
		if( original.find( piece ) != std::string::npos )
			return true;

		return false;
	}
}