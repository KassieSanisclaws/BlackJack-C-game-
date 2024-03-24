#pragma once

#include "rapidjson/document.h"

class JSONExpression 
{
public:
    virtual ~JSONExpression() = default;
    virtual void interpret(const rapidjson::Value& value) = 0;
};
