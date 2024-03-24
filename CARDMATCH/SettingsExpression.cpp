#include "SettingsExpression.h"
#include "GameSettings.h"

SettingsExpression::~SettingsExpression()
{
    GameSettings::removeInstance();
}

void SettingsExpression::interpret(const rapidjson::Value& value)
{
    if (value.HasMember("fullscreen"))
        GameSettings::getInstance()->fullscreen = value["fullscreen"].GetBool();

    if (value.HasMember("resolution"))
    {
        if (value["resolution"].HasMember("width"))
            GameSettings::getInstance()->SCREEN_WIDTH = value["resolution"]["width"].GetInt();

        if (value["resolution"].HasMember("height"))
            GameSettings::getInstance()->SCREEN_HEIGHT = value["resolution"]["height"].GetInt();
    }

    if (value.HasMember("title"))
        GameSettings::getInstance()->title = value["title"].GetString();

    if (value.HasMember("renderer"))
        GameSettings::getInstance()->renderer = value["renderer"].GetString();

    if (value.HasMember("gameloop"))
        GameSettings::getInstance()->gameloop = value["gameloop"].GetString();
}