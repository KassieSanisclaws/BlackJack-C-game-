#include "BaseShaderGL.h"

BaseShaderGL::BaseShaderGL()
{
	GLuint vertex = compileShader(vertexShader.c_str(), ShaderType::VERTEX);
	GLuint fragment = compileShader(fragmentShader.c_str(), ShaderType::FRAGMENT);

	createShader(vertex, fragment);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

const std::string BaseShaderGL::vertexShader = "#version 330 core\nlayout(location = 0) in vec3 inPos;\nlayout(location = 1) in vec3 inColor;\nlayout(location = 2) in vec2 inTexCoord;\nout vec3 outColor;\nout vec2 outTexCoord;\nvoid main() { gl_Position = vec4(inPos, 1.0);\noutColor = inColor;\noutTexCoord = inTexCoord; }";
const std::string BaseShaderGL::fragmentShader = "#version 330 core\nout vec4 FragColor;\nin vec3 outColor;\nin vec2 outTexCoord;\nuniform sampler2D sampleTexture;\nvoid main() { FragColor = texture(sampleTexture, outTexCoord); }";