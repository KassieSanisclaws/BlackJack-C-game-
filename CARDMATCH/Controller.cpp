#include "Controller.h"
#include "SceneManager.h"

Controller::Controller() : position(0.0f, 0.0f)
{

}

Controller::~Controller()
{
	for (int i = 0; i < controllers.size(); ++i)
		SDL_GameControllerClose(controllers[i]);
}

void Controller::init(SDL_Event& e)
{
	std::cout << "Controller " << e.cdevice.which << " added..." << std::endl;

	if (SDL_IsGameController(e.cdevice.which) && !SDL_GameControllerGetAttached(controllers[e.cdevice.which]))
	{
		controllers[numControllers] = SDL_GameControllerOpen(numControllers);

		if (!controllers[numControllers])
			std::cout << "Error: Controller not connected" << std::endl;
		else
		{
			if (SDL_JoystickEventState(SDL_ENABLE) < 0)
				std::cout << "Error: Joystick not initialized" << std::endl;

			if (SDL_GameControllerSetSensorEnabled(controllers[numControllers], SDL_SENSOR_GYRO, SDL_TRUE) < 0)
				std::cout << "Error: Gyro not initialized" << std::endl;

			if (SDL_GameControllerSetSensorEnabled(controllers[numControllers], SDL_SENSOR_ACCEL, SDL_TRUE) < 0)
				std::cout << "Error: Accellerometer not initialized" << std::endl;
		}

		ControllerAxis temp;

		temp.xAxis = 0;
		temp.yAxis = 0;
		temp.xDirection = 0;
		temp.yDirection = 0;

		controllerAxis.push_back(temp);

		numControllers++;
	}
}

void Controller::removeController(SDL_Event& e)
{
	std::cout << "Controller " << e.cdevice.which << " removed..." << std::endl;
	SDL_GameControllerClose(controllers[e.cdevice.which]);
	numControllers--;
}

void Controller::updateButtonState(Uint8 button, bool isPressed)
{
    buttonStates[button] = isPressed;
}

void Controller::onControllerButtonDown(ControllerEvent* e)
{
	std::cout << "Controller Button Pressed: " << SDL_GameControllerGetStringForButton((SDL_GameControllerButton)e->button) << std::endl;

	SceneManager::getInstance()->onControllerButtonDown(e);
}

void Controller::onControllerButtonUp(ControllerEvent* e)
{
	std::cout << "Controller Button Released: " << SDL_GameControllerGetStringForButton((SDL_GameControllerButton)e->button) << std::endl;

	SceneManager::getInstance()->onControllerButtonUp(e);
}

void Controller::onControllerAxisMotion(ControllerEvent* e)
{
	SDL_Joystick* j = SDL_GameControllerGetJoystick(controllers[e->id]);
	
	SDL_JoystickID joyId = SDL_JoystickInstanceID(j);

	if (e->axisValue < -JOYSTICK_DEADZONE || e->axisValue > JOYSTICK_DEADZONE)
	{
		if (e->axis == SDL_CONTROLLER_AXIS_LEFTX)
		{
			controllerAxisStates[LEFTX] = true;
			
			if (e->axisValue < -JOYSTICK_DEADZONE)
				controllerAxis[joyId].xDirection = -1;
			else if (e->axisValue > JOYSTICK_DEADZONE)
				controllerAxis[joyId].xDirection = 1;
			else
				controllerAxis[joyId].xDirection = 0;

			std::cout << "Controller Left X Axis Moved." << std::endl;
		}
		else if (e->axis == SDL_CONTROLLER_AXIS_LEFTY)
		{
			controllerAxisStates[LEFTY] = true;

			if (e->axisValue < -JOYSTICK_DEADZONE)
				controllerAxis[joyId].yDirection = -1;
			else if (e->axisValue > JOYSTICK_DEADZONE)
				controllerAxis[joyId].yDirection = 1;
			else
				controllerAxis[joyId].yDirection = 0;

			std::cout << "Controller Left Y Axis Moved." << std::endl;
		}
		else if (e->axis == SDL_CONTROLLER_AXIS_RIGHTX)
		{
			controllerAxisStates[RIGHTX] = true;

			if (e->axisValue < -JOYSTICK_DEADZONE)
				controllerAxis[joyId].xDirection = -1;
			else if (e->axisValue > JOYSTICK_DEADZONE)
				controllerAxis[joyId].xDirection = 1;
			else
				controllerAxis[joyId].xDirection = 0;

			std::cout << "Controller Right X Axis Moved." << std::endl;
		}
		else if (e->axis == SDL_CONTROLLER_AXIS_RIGHTY)
		{
			controllerAxisStates[RIGHTY] = true;

			if (e->axisValue < -JOYSTICK_DEADZONE)
				controllerAxis[joyId].yDirection = -1;
			else if (e->axisValue > JOYSTICK_DEADZONE)
				controllerAxis[joyId].yDirection = 1;
			else
				controllerAxis[joyId].yDirection = 0;

			std::cout << "Controller Right Y Axis Moved." << std::endl;
		}
		else if (e->axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
		{
			controllerAxisStates[TRIGGERLEFT] = true;

			std::cout << "Controller Trigger Left Moved." << std::endl;
		}
		else if (e->axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
		{
			controllerAxisStates[TRIGGERRIGHT] = true;

			std::cout << "Controller Trigger Right Moved." << std::endl;
		}

		SDL_Joystick* temp = SDL_GameControllerGetJoystick(controllers[joyId]);

		controllerAxis[joyId].xAxis = SDL_JoystickGetAxis(temp, 0);
		controllerAxis[joyId].yAxis = SDL_JoystickGetAxis(temp, 1);

		controllerAxis[joyId].angle = atan2((double)controllerAxis[joyId].yDirection, (double)controllerAxis[joyId].xDirection) * (180.0 / M_PI);

		if (controllerAxis[joyId].xDirection == 0 && controllerAxis[joyId].yDirection == 0)
			controllerAxis[joyId].angle = 0;

		SceneManager::getInstance()->onControllerAxisMotion(e);
	}
}

bool Controller::isButtonPressed(Uint8 button)
{
    auto it = buttonStates.find(button);

    return it != buttonStates.end() && it->second;
}

bool Controller::isButtonDown(SDL_Event& e, Uint8 button)
{
	return SDL_GameControllerGetButton(controllers[e.cdevice.which], static_cast<SDL_GameControllerButton>(button));
}

bool Controller::isButtonUp(SDL_Event& e, Uint8 button)
{
	return e.type == SDL_CONTROLLERBUTTONUP && e.cbutton.state == SDL_RELEASED && e.cbutton.button == button;
}

void Controller::setOnButtonDown(Uint8 button, std::function<void()> action)
{
    onButtonDownActions[button] = action;
}

void Controller::setOnButtonUp(Uint8 button, std::function<void()> action)
{
    onButtonUpActions[button] = action;
}

bool Controller::getControllerAxisStates(Uint8 axisNum)
{
	return controllerAxisStates[axisNum];
}

int Controller::numControllers = 0;
const int Controller::JOYSTICK_DEADZONE = 8000;