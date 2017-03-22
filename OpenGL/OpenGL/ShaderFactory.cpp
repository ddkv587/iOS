#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "ShaderFactory.h"

ShaderFactory* ShaderFactory::s_pInstance = NULL;

ShaderFactory::ShaderFactory(void)
{
}

ShaderFactory::~ShaderFactory(void)
{
}

ShaderFactory* ShaderFactory::getInstance()
{
	if ( NULL == s_pInstance )
	{
		s_pInstance = new ShaderFactory();
	}
	return s_pInstance;
}

void ShaderFactory::delInstance()
{
	if ( NULL != s_pInstance )
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

GLuint ShaderFactory::createShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	//load file
	std::ifstream	vShaderFile;
	std::ifstream	fShaderFile;

	std::string		vShaderCode;
	std::string		fShaderCode;

	vShaderFile.exceptions( std::ifstream::badbit );
	fShaderFile.exceptions( std::ifstream::badbit );

	try
	{
		vShaderFile.open( vertexPath );
		fShaderFile.open( fragmentPath );

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vShaderCode = vShaderStream.str();
		fShaderCode = fShaderStream.str();
	} catch ( std::ifstream::failure e) {
		std::cout << "Error read file" << std::endl;
	}

	const GLchar* vertexCode = vShaderCode.c_str();
	const GLchar* fragmentCode = fShaderCode.c_str();

	//==============
	GLuint	vertex, fragment;
	GLint	success;
	GLchar	infoLog[512];

	//vertex shader
	vertex = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader( vertex );

	glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
	if ( !success )
	{
		glGetShaderInfoLog( vertex, 512, NULL, infoLog );
		std::cout << "error compile vertex shader: \n" << infoLog << std::endl;

		return 0;
	}

	//frame shader
	fragment = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader( fragment );

	glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
	if ( !success )
	{
		glGetShaderInfoLog( vertex, 512, NULL, infoLog );
		std::cout << "error compile vertex shader: \n" << infoLog << std::endl;

		return 0;
	}

	//shader program
	GLuint uiGLProgram = glCreateProgram();

	glAttachShader( uiGLProgram, vertex );
	glAttachShader( uiGLProgram, fragment );
	glLinkProgram( uiGLProgram );

	glGetProgramiv( uiGLProgram, GL_LINK_STATUS, &success );
	if ( !success )
	{
		glGetShaderInfoLog( uiGLProgram, 512, NULL, infoLog );
		std::cout << "error link shader program: \n" << infoLog << std::endl;

		return 0;
	}

	glDeleteShader( vertex );
	glDeleteShader( fragment );

	return uiGLProgram;
}

void ShaderFactory::useShaderProgram()
{
	glUseProgram( m_uiGLProgram );
}