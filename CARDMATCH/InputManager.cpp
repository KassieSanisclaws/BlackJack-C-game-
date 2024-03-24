#include "InputManager.h"

InputManager::InputManager()
{ 
	init();
}

InputManager::~InputManager()
{
	if (!eventQueue.empty())
	{
		while (!eventQueue.empty())
		{
			GameEvent* e = eventQueue.front();
			eventQueue.pop();
			delete e;
		}
	}

	if (!observers.empty())
	{
		while (!observers.empty())
		{
			EventListener* e = observers.back();
			observers.pop_back();
			delete e;
		}
	}
}

InputManager* InputManager::getInstance()
{
	if (instance == nullptr)
		instance = new InputManager();

	return instance;
}

void InputManager::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

void InputManager::init()
{
	for (int i = 0; i < 6; ++i)
		controller.controllerAxisStates.push_back(false);

	SDL_GameControllerAddMapping("4c05c405000000000000504944564944, PS4 Controller,a:b1,b:b2,back:b8,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,dpup:h0.1,guide:b12,leftshoulder:b4,leftstick:b10,lefttrigger:a3,leftx:a0,lefty:a1,rightshoulder:b5,rightstick:b11,righttrigger:a4,rightx:a2,righty:a5,start:b9,touchpad:b13,x:b0,y:b3,");
	//SDL_GameControllerAddMappingsFromFile("SDL_GameControllerDB.txt");

	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		controller.controllers[i] = SDL_GameControllerOpen(i);
		controller.numControllers++;

		if (!controller.controllers[i])
			std::cout << "Error: Controller not connected" << std::endl;
		else
		{
			if (SDL_JoystickEventState(SDL_ENABLE) < 0)
				std::cout << "Error: Joystick not initialized" << std::endl;

			if (SDL_GameControllerSetSensorEnabled(controller.controllers[i], SDL_SENSOR_GYRO, SDL_TRUE) < 0)
				std::cout << "Error: Gyro not initialized" << std::endl;

			if (SDL_GameControllerSetSensorEnabled(controller.controllers[i], SDL_SENSOR_ACCEL, SDL_TRUE) < 0)
				std::cout << "Error: Accellerometer not initialized" << std::endl;
		}

		ControllerAxis temp;

		temp.xAxis = 0;
		temp.yAxis = 0;
		temp.xDirection = 0;
		temp.yDirection = 0;

		controller.controllerAxis.push_back(temp);
	}

	mouseHandler.setNextHandler(&controllerHandler);
	keyboardHandler.setNextHandler(&mouseHandler);

	std::cout << "Input Manager Initialized..." << std::endl;
}

void InputManager::handleEvents()
{
	pollEvents();
	processEvents();
}

void InputManager::pollEvents()
{
	SDL_Event e;

	while (SDL_PollEvent(&e)) 
	{
		GameEvent* gameEvent;

		if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION)
		{
			gameEvent = new MouseEvent(e);
			
			eventQueue.push(gameEvent);
		}
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			gameEvent = new KeyboardEvent(e);

			KeyboardEvent* keyEvent = dynamic_cast<KeyboardEvent*>(gameEvent);

			inputHistory.push_back(keyEvent->key.code);

			eventQueue.push(gameEvent);
		}
		else if (e.type == SDL_CONTROLLERDEVICEADDED)
		{
			controller.init(e);
		}
		else if (e.type == SDL_CONTROLLERDEVICEREMOVED)
		{
			controller.removeController(e);
		}
		else if (e.type == SDL_CONTROLLERBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONUP || e.type == SDL_CONTROLLERAXISMOTION)
		{
			gameEvent = new ControllerEvent(e);

			eventQueue.push(gameEvent);
		}
		else if (e.type == SDL_QUIT)
		{
			Game::getInstance()->stop();
		}
	}
}

void InputManager::processEvents()
{
	while (!eventQueue.empty())
	{
		GameEvent* e = eventQueue.front();
		eventQueue.pop();

		if (checkCombo())
			inputHistory.clear();
		else
			keyboardHandler.handleEvent(e);
	}
}

void InputManager::addCombo(const Combo& combo)
{
	combos.push_back(combo);
}

bool InputManager::checkCombo()
{
	for (const auto& combo : combos) 
	{
		if (isCombo(combo)) 
		{
			combo.action();
			return true;
		}
	}

	return false;
}

bool InputManager::isCombo(const Combo& combo) 
{
	if (inputHistory.size() >= combo.sequence.size()) 
	{
		bool match = true;
		auto itHistory = inputHistory.rbegin();
		for (auto itCombo = combo.sequence.rbegin(); itCombo != combo.sequence.rend(); ++itCombo, ++itHistory) 
		{
			if (*itCombo != *itHistory) 
			{
				match = false;
				break;
			}
		}

		if (match) 
		{
			combo.action();
			inputHistory.clear();
			return true;
		}
	}

	return false;
}

void InputManager::addEventListener(EventListener* observer)
{
	observers.push_back(observer);
}

void InputManager::removeEventListener(EventListener* observer)
{
	auto it = observers.begin();

	while (it != observers.end())
	{
		if (*it == observer)
		{
			delete* it;

			it = observers.erase(it);
		}
		else
			++it;
	}
}

void InputManager::notify(GameEvent& e)
{
	for (auto listener : observers)
	{
		if (e.type == SDL_KEYDOWN)
			listener->onKeyDown(e);
		else if (e.type == SDL_KEYUP)
			listener->onKeyUp(e);
		else if (e.type == SDL_MOUSEBUTTONDOWN)
			listener->onMouseButtonDown(e);
		else if (e.type == SDL_MOUSEBUTTONUP)
			listener->onMouseButtonUp(e);
		else if (e.type == SDL_CONTROLLERBUTTONDOWN)
			listener->onControllerButtonDown(e);
		else if (e.type == SDL_CONTROLLERBUTTONUP)
			listener->onControllerButtonUp(e);
	}
}

void InputManager::enableKeyboard()
{
	keyboard.enabled = true;
}

void InputManager::disbaleKeyboard()
{
	keyboard.enabled = false;
}

void InputManager::enableMouse()
{
	mouse.enabled = true;
}

void InputManager::disableMouse()
{
	mouse.enabled = false;
}

void InputManager::onUserEvent(GameEvent* e)
{
	//std::cout << "User Event Dispatched: " << e.user.code << std::endl;

	SceneManager::getInstance()->onUserEvent(e);
}

InputManager* InputManager::instance = nullptr;