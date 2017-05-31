#include "SpriteStorage.h"

namespace Game
{
	namespace Drawables
	{
		void SpriteStorage::add( std::string id, Sprite *sprite )
		{
			sprites.insert( std::make_pair( id, spritePtr( sprite ) ) );
		}

		bool SpriteStorage::find( std::string id )
		{
			auto it = sprites.find( id );

			if( it != sprites.end() )
				return true;

			return false;
		}

		void SpriteStorage::destroy( std::string id )
		{
			if( find( id ) )
				sprites.erase( id );
			else
				if( Debug::active )
					std::cout << "Can't delete sprite" << std::endl;
		}

		Sprite *SpriteStorage::getSprite( std::string id )
		{
			return sprites[id].get();
		}

		spriteMap& SpriteStorage::getSprites()
		{
			return sprites;
		}
	}
}