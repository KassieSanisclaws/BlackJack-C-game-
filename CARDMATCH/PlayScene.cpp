#include "PlayScene.h"

PlayScene::PlayScene(std::string sID) : Scene(sID)
{
	bg = new Image("bg", "images/bg.png", 0.f, 0.0f, 2048, 1536, 1, 1);
	logo = new Image("logo", "images/logo.png", 0.f, 0.0f, 1024, 768, 1, 1);
	button = new Image("buttons", "images/buttons.png", 0.f, 0.0f, 512, 512, 1, 1);
}

void PlayScene::update()
{
	Scene::update();

	
}

void PlayScene::render()
{
	Scene::render();
}

bool PlayScene::onEnter()
{
	Scene::onEnter();

	addGameObject(bg, 0);
	addGameObject(logo, 1);

	// Set example screen dimensions
	int screenWidth = 1920; // Example width
	int screenHeight = 1080; // Example height

	// Calculate the position of the button
	 float buttonX = (screenWidth - button->getWidth()) / 2.0f;
	 float buttonY = screenHeight - button->getHeight();

	// Set the position of the button
	button->setPosition(buttonX, buttonY);

	// Add the button to the scene
	addGameObject(button, 2);

	
	return true;
}

bool PlayScene::onExit()
{
	Scene::onExit();

	return true;
}

void PlayScene::onUserEvent(GameEvent* e)
{

}

void PlayScene::onKeyDown(GameEvent* e)
{
	
}

void PlayScene::onKeyUp(GameEvent* e)
{
	
}

void PlayScene::onMouseButtonDown(GameEvent* e)
{

}

void PlayScene::onMouseButtonUp(GameEvent* e)
{

}

void PlayScene::onMouseMove(GameEvent* e)
{

}

void PlayScene::onControllerButtonDown(GameEvent* e)
{

}

void PlayScene::onControllerButtonUp(GameEvent* e)
{

}

void PlayScene::onControllerAxisMotion(GameEvent* e)
{

}

//Uint32 PlayScene::animationDelay(Uint32 delay, void* params)
//{
//	
//}

Game* PlayScene::game = Game::getInstance();