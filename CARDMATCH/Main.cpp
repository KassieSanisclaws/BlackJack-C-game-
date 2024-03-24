#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Game.h"
#include "SceneManager.h"
#include "PlayScene.h"

// ********************************************
// GAME ENINGE V2
// ********************************************

int main(int argv, char** argc)
{
	Game* game = Game::getInstance();

	SceneManager* sceneManager = SceneManager::getInstance();

	// ********************************************
	// Game Initialization - add your settings here
	// ********************************************
	game->init(50, 50);

	// *********************************
	// Game Scene - add your scenes here
	// *********************************
	SceneManager::getInstance()->addScene(new PlayScene("playscene"));

	game->start();
	
	game->shutdown();

	return 0;
}