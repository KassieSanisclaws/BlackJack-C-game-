#pragma once

#include "ShaderGL.h"

class BaseShaderGL : public ShaderGL
{
public:
	BaseShaderGL();

	static const std::string vertexShader;
	static const std::string fragmentShader;
};