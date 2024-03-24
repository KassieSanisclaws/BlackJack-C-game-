#include "Mouse.h"

Mouse::Mouse() 
{
	
}

void Mouse::updateButtonState(Uint8 button, bool isPressed) 
{
	buttonStates[button] = isPressed;
}

void Mouse::onMouseMove(GameEvent* event)
{
	MouseEvent* e = dynamic_cast<MouseEvent*>(event);

	if (e != nullptr)
	{
		position = e->position;

		std::cout << "Mouse position = x: " << position.x << ", y:" << position.y << std::endl;

		SceneManager::getInstance()->onMouseMove(e);
	}
}

void Mouse::onMouseButtonDown(GameEvent* event)
{
	MouseEvent* e = dynamic_cast<MouseEvent*>(event);
	
	if (e != nullptr)
	{
		position = e->position;

		if (e->button == MOUSELEFTBUTTON)
			std::cout << "Left Mouse Button Pressed at " << position.x << ", " << position.y << std::endl;
		else if (e->button == MOUSEMIDDLEBUTTON)
			std::cout << "Middle Mouse Button Pressed at " << position.x << ", " << position.y << std::endl;
		else if (e->button == MOUSERIGHTBUTTON)
			std::cout << "Right Mouse Button Pressed at " << position.x << ", " << position.y << std::endl;

		updateButtonState(e->button, true);

		SceneManager::getInstance()->onMouseButtonDown(e);
	}
}

void Mouse::onMouseButtonUp(GameEvent* event)
{
	MouseEvent* e = dynamic_cast<MouseEvent*>(event);

	if (e != nullptr)
	{
		position = e->position;

		if (e->button == MOUSELEFTBUTTON)
			std::cout << "Left Mouse Button Released at " << position.x << ", " << position.y << std::endl;
		else if (e->button == MOUSEMIDDLEBUTTON)
			std::cout << "Middle Mouse Button Released at " << position.x << ", " << position.y << std::endl;
		else if (e->button == MOUSERIGHTBUTTON)
			std::cout << "Right Mouse Button Released at " << position.x << ", " << position.y << std::endl;

		updateButtonState(e->button, false);

		SceneManager::getInstance()->onMouseButtonUp(e);
	}
}

bool Mouse::getMouseButtonState(Uint8 button)
{
	auto it = buttonStates.find(button);

	if(it != buttonStates.end())
		return it->second;

	return false;
}

const Vector2D& Mouse::getMousePosition()
{
	return position;
}

bool Mouse::isMouseButtonPressed(Uint8 button)
{
	auto it = buttonStates.find(button);

	return it != buttonStates.end() && it->second;
}

bool Mouse::isMouseButtonDown(GameEvent* event, Uint8 button)
{
	MouseEvent* e = dynamic_cast<MouseEvent*>(event);

	if (e != nullptr)
		return e->type == SDL_MOUSEBUTTONDOWN && e->buttonState == SDL_PRESSED && e->button == button;
	else
		return false;
}

bool Mouse::isMouseButtonUp(GameEvent* event, Uint8 button)
{
	MouseEvent* e = dynamic_cast<MouseEvent*>(event);

	if (e != nullptr)
		return e->type == SDL_MOUSEBUTTONUP && e->buttonState == SDL_RELEASED && e->button == button;
	else
		return false;
}

void Mouse::setOnMouseButtonDown(Uint8 button, std::function<void()> action) 
{
	onMouseButtonDownActions[button] = action;
}

void Mouse::setOnMouseButtonUp(Uint8 button, std::function<void()> action) 
{
	onMouseButtonUpActions[button] = action;
}

bool Mouse::enabled = true;
Vector2D Mouse::position = { 0.0f, 0.0f };