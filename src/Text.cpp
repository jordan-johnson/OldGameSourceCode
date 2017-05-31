#include "Text.h"

/**
 * Example use (update later):
 *
 * Text mytext;
 * mytext = Text( Renderer, "example" );
 * mytext.setFont( "verdana.ttf", 14 );
 * mytext.setColor( 255, 255, 255 );
 * mytext.setPlace( 100, 100 );
 * mytext.init();
 *
 * // -- in a draw loop -- /
 * mytext.render();
 *
 * Above example will display the text "example"
 * on screen using verdana font (14pt) with
 * white text at destination 100, 100
 */

namespace Game
{
	namespace Drawables
	{
		Text::~Text()
		{
			SDL_FreeSurface( message );
			SDL_DestroyTexture( texture );
		}

		Text::Text( SDL_Renderer *source, std::string text )
		{
			// Set source to renderer
			renderer = source;

			// Set text
			display = text;

			// Set default text color
			setColor( 0, 0, 0 );

			// Set default text placement
			setPlace( 0, 0 );
		}

		/**
		 * PUBLIC FUNCTIONS
		 *
		 * setMaximumWidth( int )
		 * setFont( TTF_Font )
		 * setColor( SDL_Color ), setColor( Uint8, Uint8, Uint8, Uint8 = 0 )
		 * setPlace( int, int )
		 * init()
		 * render()
		 */

		void Text::setMaximumWidth( int _width )
		{
			wrapping = _width;
		}

		void Text::setFont( TTF_Font *_font )
		{
			font = _font;
		}

		void Text::setColor( SDL_Color _color )
		{
			// Set color through SDL_Color
			color = _color;
		}

		void Text::setColor( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha )
		{
			// Set color through parameters
			color.r = red;
			color.g = green;
			color.b = blue;
			color.a = alpha;
		}

		void Text::setPlace( int x, int y )
		{
			// Set x and y coordinates
			dimensions.x = x;
			dimensions.y = y;
		}

		void Text::init()
		{
			// Check for wrapping (maximum width)
			// If greater than 0, wrap the text
			// Set surface of text with specified font, text, and color
			message = ( wrapping == 0 ) ? TTF_RenderText_Solid( font, display.c_str(), color ) : TTF_RenderText_Blended_Wrapped( font, display.c_str(), color, wrapping );

			// Create texture from Message surface
			texture = SDL_CreateTextureFromSurface( renderer, message );

			// Get the size of the text
			TTF_SizeText( font, display.c_str(), &width, &height );

			// ..then set the variables
			dimensions.w = width;
			dimensions.h = height;
		}

		void Text::render( float delta )
		{
			// Check if font is opened..
			if( font != NULL )
			{
				// ..then render the text
				SDL_RenderCopy( renderer, texture, NULL, &dimensions );
			}
		}
	}
}