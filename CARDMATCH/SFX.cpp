#include "SFX.h"
#include "ResourceManager.h"
#include "GameObjectVisitor.h"

SFX::SFX() : GameObject()
{
	resourceManager = ResourceManager::getInstance();

	library.reserve(8);
}

SFX::SFX(std::string goID, std::string filename)
{
	GraphicsComponent* gc = nullptr;
	AnimationComponent* ac = nullptr;
	PhysicsComponent* pc = nullptr;
	TextComponent* tc = nullptr;
	MusicComponent* mc = nullptr;
	SFXComponent* sfxc = new SFXComponent();

	properties = new GameObjectProperties(gc, ac, pc, tc, mc, sfxc);

	gameObjectID = goID;
	sfxc->filename = filename;

	sfxc->loadAsset(goID, filename);

	library[goID] = sfxc;

	resourceManager = ResourceManager::getInstance();
}

SFX::SFX(GameObjectProperties* properties)
	: GameObject(properties)
{
	SFXComponent* sfxc = new SFXComponent();

	resourceManager = ResourceManager::getInstance();
}

SFX::SFX(const SFX& other)
{
	GraphicsComponent* gc = nullptr;
	AnimationComponent* ac = nullptr;
	PhysicsComponent* pc = nullptr;
	TextComponent* tc = nullptr;
	MusicComponent* mc = nullptr;
	SFXComponent* sfxc = new SFXComponent();

	properties = new GameObjectProperties(gc, ac, pc, tc, mc, sfxc);

	resourceManager = ResourceManager::getInstance();

	properties = new GameObjectProperties(gc, ac, pc, tc, mc, sfxc);

	gameObjectID = other.gameObjectID;
	
	library = other.library;

	resourceManager = ResourceManager::getInstance();
}

SFX::~SFX()
{ 
	std::unordered_map<std::string, SFXComponent*>::iterator it = library.begin();
	
	while (it != library.end())
	{
		delete (*it).second;

		++it;
	}
}

SFX* SFX::clone()
{
	return new SFX(*this);
}

void SFX::accept(GameObjectVisitor& visitor)
{

}

void SFX::update()
{ }

void SFX::render()
{ }

void SFX::addSFX(std::string goID, std::string filename)
{
	std::cout << "Loading SFX " << goID << "..." << std::endl;
	SFXComponent* sfxc = new SFXComponent();
	
	sfxc->filename = filename;

	sfxc->loadAsset(goID, filename);

	if (library.size() < 8)
		library[goID] = sfxc;
}

void SFX::play(std::string goID)
{
	std::cout << "Playing SFX " << goID << "..." << std::endl;
	library[goID]->playSFX();
}

std::unordered_map<std::string, SFXComponent*> SFX::library;