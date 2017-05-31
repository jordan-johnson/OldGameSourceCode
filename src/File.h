#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

#include "json.h"

namespace Game
{
	class File
	{
	public:
		/**
		 * Create file
		 *\returns true if created
		 */
		bool create( const std::string location, bool overwrite = false );

		/**
		 * Delete file
		 *\returns true if deleted
		 */
		bool destroy( const std::string location );

		/**
		 * File existenece
		 *\returns true if found
		 */
		bool exists( const std::string location );

		/**
		 * Write to json file
		 *\returns true if written
		 */
		bool writeJson( std::string filename, Json::Value data );
	};
}

#endif