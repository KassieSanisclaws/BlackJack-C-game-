#pragma once

#include <iostream>
#include <string>

#include "JSONExpression.h"
#include "rapidjson/Document.h"

class SceneExpression : public JSONExpression
{
public:
    ~SceneExpression();

    void interpret(const rapidjson::Value&);
};
