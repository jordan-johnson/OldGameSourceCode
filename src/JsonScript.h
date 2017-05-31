#ifndef JSONSCRIPT_H
#define JSONSCRIPT_H

#include <iostream>
#include <map>
#include "json.h"

#include "File.h"
#include "Debug.h"

namespace Game
{

	typedef Json::Value JValue;

	class JsonScript
	{
	private:
		std::string filename = std::string();

		bool errors = false;

		// Error types
		enum E_TYPES
		{
			LOAD, PARSER, DELETION, WRITING
		};

		Json::Reader reader;

		Json::Value data;

		bool stringFind( const std::string original, const std::string piece );

		void pushError( E_TYPES type, std::string extra = std::string() );
	public:
		// Json extension
		std::string ext( std::string value );

		bool loadFile( const std::string location );
		bool createFile( const std::string location, bool overwrite = false );
		bool deleteFile( const std::string location );

		bool addValues( std::map<std::string, JValue> arr );

		bool fileExists( std::string location );

		std::string getString( std::string name, std::string val );

		int getInt( std::string name, int val );

		float getFloat( std::string name, float val );

		Json::Value& getJson();
	};
}

#endif