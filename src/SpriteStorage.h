#ifndef SPRITE_STORAGE_H
#define SPRITE_STORAGE_H

#include <unordered_map>

#include "Sprite.h"

namespace Game
{
	namespace Drawables
	{
		typedef std::unique_ptr<Sprite> spritePtr;
		typedef std::unordered_map<std::string, spritePtr> spriteMap;
		class SpriteStorage
		{
		private:
			spriteMap sprites;
		public:
			void add( std::string id, Sprite *sprite );

			bool find( std::string id );

			void destroy( std::string id );

			Sprite *getSprite( std::string id );

			spriteMap& getSprites();
		};
	}
}

#endif