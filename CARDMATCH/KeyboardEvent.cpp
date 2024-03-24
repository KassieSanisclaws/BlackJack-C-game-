#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
	{
		type = e.type;
		timestamp = e.key.timestamp;
		state = e.key.state;
		key = Key(e.key.keysym.scancode);
		key.sym = e.key.keysym.sym;
	}
}