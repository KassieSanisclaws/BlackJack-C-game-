#pragma once

#include <iostream>
#include <string>

#include "JSONExpression.h"
#include "rapidjson/Document.h"

class SettingsExpression : public JSONExpression 
{
public:
    ~SettingsExpression();

    void interpret(const rapidjson::Value&);
};
