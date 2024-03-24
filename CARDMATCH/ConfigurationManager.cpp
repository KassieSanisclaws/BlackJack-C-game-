#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager(const std::string& configFilePath)
{
    loadConfiguration(configFilePath);
}

ConfigurationManager::~ConfigurationManager()
{
    delete context;
}

void ConfigurationManager::loadConfiguration(const std::string& configFilePath)
{
    std::ifstream ifs(configFilePath);

    std::cout << "Reading " << configFilePath << "..." << std::endl;

    if (!ifs.is_open())
    {
        std::cout << "Failed to open config file: " << configFilePath << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();

    context = new JSONContext(buffer.str());

    parse();
}

void ConfigurationManager::parse()
{
    auto& document = context->getDocument();

    if (document.HasMember("game"))
    {
        const auto& settings = document["game"];

        parseGameSettings(settings);
        parseSceneSettings(settings);
    }
}

void ConfigurationManager::parseGameSettings(const rapidjson::Value& value)
{
    if (value.HasMember("settings"))
    {
        gameSettings.interpret(value["settings"]);
    }
}

void ConfigurationManager::parseSceneSettings(const rapidjson::Value& value)
{
    if (value.HasMember("scene"))
    {
        sceneSettings.interpret(value["scene"]);
    }
}