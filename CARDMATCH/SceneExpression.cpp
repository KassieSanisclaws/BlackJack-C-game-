#include "SceneExpression.h"
#include "SceneSettings.h"
#include "GameObjectSettings.h"

SceneExpression::~SceneExpression()
{
    SceneSettings::removeInstance();
}

void SceneExpression::interpret(const rapidjson::Value& value)
{
    if (value.HasMember("id"))
        SceneSettings::getInstance()->sceneID = value["id"].GetString();

    if (value.HasMember("gameobjects"))
    {
        for (auto& m : value["gameobjects"].GetObject())
        {
            std::string name = m.name.GetString();
            GameObjectSettings goSettings;

            if (name == "image")
            {
                goSettings.type = "image";

                if (value["gameobjects"]["image"].HasMember("id"))
                    goSettings.gameObjectID = value["gameobjects"]["image"]["id"].GetString();

                if (value["gameobjects"]["image"].HasMember("file"))
                    goSettings.filename = value["gameobjects"]["image"]["file"].GetString();

                if (value["gameobjects"]["image"].HasMember("x"))
                    goSettings.position.x = value["gameobjects"]["image"]["x"].GetFloat();

                if (value["gameobjects"]["image"].HasMember("y"))
                    goSettings.position.y = value["gameobjects"]["image"]["y"].GetFloat();

                if (value["gameobjects"]["image"].HasMember("w"))
                    goSettings.w = value["gameobjects"]["image"]["w"].GetInt();

                if (value["gameobjects"]["image"].HasMember("h"))
                    goSettings.h = value["gameobjects"]["image"]["h"].GetInt();

                if (value["gameobjects"]["image"].HasMember("rows"))
                    goSettings.rows = value["gameobjects"]["image"]["rows"].GetInt();

                if (value["gameobjects"]["image"].HasMember("cols"))
                    goSettings.cols = value["gameobjects"]["image"]["cols"].GetInt();

                SceneSettings::getInstance()->objects.push_back(goSettings);
            }
            else if (name == "character")
            {
                goSettings.type = "character";

                if (value["gameobjects"]["character"].HasMember("id"))
                    goSettings.gameObjectID = value["gameobjects"]["character"]["id"].GetString();

                if (value["gameobjects"]["character"].HasMember("file"))
                    goSettings.filename = value["gameobjects"]["character"]["file"].GetString();

                if (value["gameobjects"]["character"].HasMember("x"))
                    goSettings.position.x = value["gameobjects"]["character"]["x"].GetFloat();

                if (value["gameobjects"]["character"].HasMember("y"))
                    goSettings.position.y = value["gameobjects"]["character"]["y"].GetFloat();

                if (value["gameobjects"]["character"].HasMember("w"))
                    goSettings.w = value["gameobjects"]["character"]["w"].GetInt();

                if (value["gameobjects"]["character"].HasMember("h"))
                    goSettings.h = value["gameobjects"]["character"]["h"].GetInt();

                if (value["gameobjects"]["character"].HasMember("rows"))
                    goSettings.rows = value["gameobjects"]["character"]["rows"].GetInt();

                if (value["gameobjects"]["character"].HasMember("cols"))
                    goSettings.cols = value["gameobjects"]["character"]["cols"].GetInt();

                SceneSettings::getInstance()->objects.push_back(goSettings);
            }
            else if (name == "wall") 
            {
                goSettings.type = "wall";

                const rapidjson::Value& walls = value["gameobjects"]["wall"].GetArray();
                
                if (walls.IsArray()) 
                {
                    for (rapidjson::SizeType i = 0; i < walls.Size(); i++)
                    {
                        const auto& wall = walls[i];

                        if (wall.HasMember("id"))
                            goSettings.gameObjectID = wall["id"].GetString();

                        if (wall.HasMember("x"))
                            goSettings.position.x = wall["x"].GetFloat();

                        if (wall.HasMember("y"))
                            goSettings.position.y = wall["y"].GetFloat();

                        if (wall.HasMember("w"))
                            goSettings.w = wall["w"].GetInt();

                        if (wall.HasMember("h"))
                            goSettings.h = wall["h"].GetInt();

                        SceneSettings::getInstance()->objects.push_back(goSettings);
                    }
                }
            }
        }
    }
}