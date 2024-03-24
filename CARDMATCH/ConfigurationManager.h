#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "rapidjson/Document.h"

#include "JSONContext.h"
#include "SettingsExpression.h"
#include "SceneExpression.h"

class ConfigurationManager 
{
public:
    ConfigurationManager(const std::string&);
    ~ConfigurationManager();

    void loadConfiguration(const std::string&);

    SettingsExpression gameSettings;
    SceneExpression sceneSettings;

    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

private:
    void parse();

    void parseGameSettings(const rapidjson::Value&);
    void parseSceneSettings(const rapidjson::Value&);
    
    JSONContext* context;
};
