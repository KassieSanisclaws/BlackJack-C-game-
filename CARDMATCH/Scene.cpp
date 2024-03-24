#include "Scene.h"

Scene::Scene(std::string sID) : sceneID(sID)
{ 
	mc = new MusicComponent();
	gameObjectSize = 0;
}

Scene::Scene(const Scene& other)
{
	gameObjectID = other.gameObjectID;
	context = other.context;
	gameObjectSize = other.gameObjectSize;
	
	for (auto item : other.depthMap)
		depthMap.insert(item);

	for (auto item : other.gameObjectMap)
		gameObjectMap.insert(item);

	mc = new MusicComponent();
	mc->filename = other.mc->filename;
	mc->playing = other.mc->playing;
}

Scene::~Scene()
{
	if (!gameObjectMap.empty())
	{
		auto it = gameObjectMap.begin();

		while (it != gameObjectMap.end())
		{
			std::string goID = (*it).first;

			std::cout << "Removing GameObject " << goID << "..." << std::endl;
			delete gameObjectMap[goID];

			++it;
		}
	}

	if (!depthMap.empty())
		depthMap.clear();

	if (mc)
		delete mc;
}

void Scene::update()
{
	std::unordered_map<std::string, int>::iterator it = depthMap.begin();

	while (it != depthMap.end())
	{
		std::string goID = (*it).first;

		gameObjectMap[goID]->update();

		++it;
	}
}

void Scene::render()
{
	std::vector<std::pair<int, std::string>> sortedMap;

	for (auto i : depthMap)
		sortedMap.push_back({ i.second, i.first });

	std::sort(sortedMap.begin(), sortedMap.end());

	std::vector<std::pair<int, std::string>>::iterator it = sortedMap.begin();

	while (it != sortedMap.end())
	{
		std::string goID = (*it).second;

		gameObjectMap[goID]->render();

		++it;
	}
}

Scene* Scene::clone()
{
	return new Scene(*this);
}

bool Scene::onEnter()
{
	return true;
}

bool Scene::onExit()
{
	std::unordered_map<std::string, int>::iterator depthIT = depthMap.begin();
	std::unordered_map<std::string, GameObject*>::iterator goIT = gameObjectMap.begin();

	while (depthIT != depthMap.end())
	{
		std::string goID = (*depthIT).first;

		std::cout << "Removing GameObject " << goID << "..." << std::endl;

		depthIT = depthMap.erase(depthIT);
		goIT = gameObjectMap.erase(goIT);
	}
	
	std::cout << "Exiting Scene..." << std::endl;
	
	return true;
}

void Scene::addGameObject(GameObject* object, int depth)
{
	std::string goID = object->getGameObjectID();

	std::cout << "Adding GameObject " << goID << "..." << std::endl;
	gameObjectMap[goID] = object;
	depthMap[goID] = depth;

	gameObjectSize++;
}

void Scene::removeGameObject(GameObject* object)
{
	std::string goID = object->getGameObjectID();

	std::cout << "Removing GameObject " << goID << "..." << std::endl;
	gameObjectMap.erase(goID);
	depthMap.erase(goID);

	gameObjectSize--;
}

GameObject* Scene::getObjectByID(std::string id)
{
	return gameObjectMap[id];
}

void Scene::addMusic(std::string filename)
{
	mc->filename = filename;

	mc->loadAsset(sceneID, filename);
}

void Scene::playMusic()
{
	mc->playMusic();
	mc->playing = true;
}

std::string Scene::getSceneID() const
{
	return sceneID;
}