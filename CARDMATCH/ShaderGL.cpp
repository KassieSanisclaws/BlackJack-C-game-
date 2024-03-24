#include "ShaderGL.h"
#include "ImageGL.h"

ShaderGL::ShaderGL() : vertexFilename(""), fragmentFilename("")
{

}

ShaderGL::ShaderGL(std::string vertexPath, std::string fragmentPath) : vertexFilename(vertexPath), fragmentFilename(fragmentPath)
{
	vertexCode = readShaderFile(vertexFilename);
	fragmentCode = readShaderFile(fragmentFilename);

	GLuint vertex = compileShader(vertexCode.c_str(), ShaderType::VERTEX);
	GLuint fragment = compileShader(fragmentCode.c_str(), ShaderType::FRAGMENT);

	createShader(vertex, fragment);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

ShaderGL::~ShaderGL()
{
	std::cout << "Removing shader..." << std::endl;

	glDeleteProgram(shaderID);
}

std::string ShaderGL::readShaderFile(const std::string& filename)
{
	try
	{
		std::ifstream file(filename);
		std::stringstream buffer;

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		buffer << file.rdbuf();

		return buffer.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR: Shader could not be opened" << std::endl;
	}
}

void ShaderGL::createShader(GLuint vertex, GLuint fragment)
{
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);
	checkCompileErrors(shaderID, ShaderType::PROGRAM);
}

GLuint ShaderGL::compileShader(const std::string& shaderData, ShaderType shaderType)
{
	GLenum type;

	if (shaderType == ShaderType::VERTEX)
		type = GL_VERTEX_SHADER;
	if (shaderType == ShaderType::FRAGMENT)
		type = GL_FRAGMENT_SHADER;

	GLuint shader = glCreateShader(type);
	const char* source = shaderData.c_str();
	
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	
	checkCompileErrors(shader, shaderType);

	return shader;
}

void ShaderGL::bindImage(const ImageGL& image)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(float), image.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), image.indices, GL_STATIC_DRAW);
}

void ShaderGL::bindImage(const OpenGLImage& image)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(float), image.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), image.indices, GL_STATIC_DRAW);
}

void ShaderGL::unbindImage() 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}


void ShaderGL::applyShader()
{
	glUseProgram(shaderID);
}

void ShaderGL::removeShader()
{
	glUseProgram(0);
}

void ShaderGL::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}

void ShaderGL::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void ShaderGL::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void ShaderGL::setVertexAttribPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride)
{
	glVertexAttribPointer(currentAttribIndex, size, type, normalized, stride, (void*)currentOffset);
	glEnableVertexAttribArray(currentAttribIndex);

	currentOffset += size * sizeof(type);
	currentAttribIndex++;
}

void ShaderGL::checkCompileErrors(unsigned int shader, ShaderType type)
{
	int success;
	char infoLog[1024];
	if (type != ShaderType::PROGRAM)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR: Shader could not be compiled" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR: Shader cannot be linked" << std::endl;
		}
	}
}