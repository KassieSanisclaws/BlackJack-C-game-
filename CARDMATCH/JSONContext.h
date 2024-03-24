#pragma once

#include <iostream>
#include <string>

#include "rapidjson/Document.h"

class JSONContext 
{
public:
    explicit JSONContext(const std::string& jsonText) 
    {
        document.Parse(jsonText.c_str());

        if (document.HasParseError())
        {
            std::cout << "Error parsing config file." << std::endl;
            return;
        }
    }

    const rapidjson::Document& getDocument() const 
    {
        return document;
    }

private:
    rapidjson::Document document;
};