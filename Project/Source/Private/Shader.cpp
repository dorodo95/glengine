#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//Retrieve Source Code from file
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//open file
		vShaderFile.open(vertexPath, std::ios::in);
		fShaderFile.open(fragmentPath, std::ios::in);

		//Create streams which will retain the buffer data
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		//rdbuf reads file's buffer content and sends to streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//convert stream to string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		//Close files
		vShaderFile.close();
		fShaderFile.close();
	}

	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_READ" << std::endl;
	}

	//Convert from string to char
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

#pragma region Shader Declaration

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //Creates an empty vertex shader program.

	glShaderSource(vertexShader, 1, &vShaderCode, nullptr); //Replaces the source code with the provided char.
	glCompileShader(vertexShader); //Compiles the shader. 

	//Has compilation succeeded?
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else
	{
		std::cout << "Successfully Compiled Vertex Shader!" << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Creates an empty vertex shader program.

	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr); //Replaces the source code with the provided char.
	glCompileShader(fragmentShader); //Compiles the shader. 

	//Has compilation succeeded?
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else
	{
		std::cout << "Successfully Compiled Fragment Shader!" << std::endl;
	}

#pragma region Shader Link
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);

	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
	else
	{
		std::cout << "Successfully Linked Shader!" << std::endl;
	}
#pragma endregion


	//Delete Shaders as they are now unnecessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

#pragma endregion
};

void Shader::Use()
{
	glUseProgram(shaderProgramID);
}