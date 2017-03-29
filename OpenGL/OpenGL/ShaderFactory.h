#ifndef __SHADER_FACTORY_H__
#define __SHADER_FACTORY_H__

#include <GL/glew.h>

class ShaderFactory
{
public:
	ShaderFactory(void);
	~ShaderFactory(void);

	static ShaderFactory* getInstance();
	static void delInstance();

	GLuint createShader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void useShaderProgram();

private:
	static ShaderFactory* s_pInstance;

	GLuint	m_uiGLProgram;
};

#endif
