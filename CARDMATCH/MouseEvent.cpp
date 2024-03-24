#include "MouseEvent.h"

MouseEvent::MouseEvent(SDL_Event& e) : position({ static_cast<float>(e.button.x), static_cast<float>(e.button.y) })
{
	if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		type = e.type;
		timestamp = e.button.timestamp;
		button = e.button.button;
		buttonState = e.button.state;
		numClicks = e.button.clicks;
	}
	else if (e.type == SDL_MOUSEMOTION)
	{
		type = e.type;
		timestamp = e.motion.timestamp;
		button = 0;
		buttonState = e.motion.state;
		numClicks = 0;
	}
}