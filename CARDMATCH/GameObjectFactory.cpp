#include "GameObjectFactory.h"
#include "Image.h"
#include "Sprite.h"

GameObject* GameObjectFactory::createGameObject(const GameObjectSettings& settings)
{
    if (settings.type == "image")
    {
        return new Image(settings.gameObjectID, settings.filename, settings.position.x, settings.position.y, settings.w, settings.h, settings.rows, settings.cols);
    }
    else if (settings.type == "sprite")
    {
        return new Sprite(settings.gameObjectID, settings.filename, settings.position.x, settings.position.y, settings.w, settings.h, settings.rows, settings.cols);
    }

    return nullptr;
}