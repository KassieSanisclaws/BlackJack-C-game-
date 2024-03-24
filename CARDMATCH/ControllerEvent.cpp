#include "ControllerEvent.h"

ControllerEvent::ControllerEvent(SDL_Event& e)
{
	if (e.type == SDL_CONTROLLERBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONUP)
	{
		type = e.type;
		id = e.cdevice.which;
		timestamp = e.cbutton.timestamp;
		button = e.cbutton.button;
		state = e.cbutton.state;
		axis = 0;
		axisValue = 0;
	}
	if (e.type == SDL_CONTROLLERAXISMOTION)
	{
		type = e.type;
		id = e.cdevice.which;
		timestamp = e.caxis.timestamp;
		button = 0;
		state = 0;
		axis = e.caxis.axis;
		axisValue = e.caxis.value;
	}
}