//
//  main.cpp
//  OpenGL
//
//  Created by ddk on 2017/3/18.
//  Copyright © 2017年 ddk. All rights reserved.
//

#include <iostream>

//glew
#define GLEW_STATIC
#include <GL/glew.h>

//glfw
#include <GLFW/glfw3.h>

#include <math.h>
#include <SOIL/SOIL.h>

#include "ShaderFactory.h"
#include "DataCollect.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#ifdef OS_MAC
#include "ImageLib.h"
#endif

static float g_mixValue = 0.0;

GLFWwindow* createWindow(int x = 0, int y = 0, int width = 800, int heigth = 600)
{
    GLFWwindow* pWindow = glfwCreateWindow(width, heigth, "OpenGL", NULL, NULL);

    if ( NULL == pWindow )
    {
        std::cout << "failed to create window" << std::endl;
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(pWindow);

    //glfwSetKeyCallback(window, keyCallBack);

    glewExperimental = GL_TRUE;
    if ( glewInit() != GLEW_OK )
    {
        std::cout << "failed to init glew" << std::endl;
        glfwTerminate();
        return NULL;
    }

    int w, h;
    glfwGetFramebufferSize(pWindow, &w, &h);
    glViewport(x, y, w, h);

    return pWindow;
}

void keyCallBack(GLFWwindow* window, int key, int scannode, int action, int mode)
{
	switch ( key) {
	case GLFW_KEY_ESCAPE:
		if ( action == GLFW_PRESS ) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	case GLFW_KEY_UP:
		if ( action == GLFW_PRESS ) {
			g_mixValue += 0.1f;
		}
		break;
	case GLFW_KEY_DOWN:
		if ( action == GLFW_PRESS ) {
			g_mixValue -= 0.1f;
		}
		break;
	default:
		break;
	}
}

int main(int argc, const char * argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window       = createWindow(0, 0, 800, 480);
    GLuint  shaderProgram    = ShaderFactory::getInstance()->createShader("shader/VertexShader.c", "shader/FragmentShader.c");

    glfwSetKeyCallback(window, keyCallBack);

    GLuint VAO, VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof( GLfloat )));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof( GLfloat )));
	glEnableVertexAttribArray(2);

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

	glBindVertexArray(0);

	//load texture
	GLuint texture1, texture2;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

#ifdef OS_MAC
    ImageLib img;
    img.LoadImageFile("/Users/ddk/Desktop/Project/OpenGL/OpenGL/resource/texture.png");

#elif OS_WIN

	int imgWidth, imgHeigth;
    unsigned char* image = SOIL_load_image("resource/container.jpg", &imgWidth, &imgHeigth, 0,SOIL_LOAD_RGB);

    memset(image, 0, 1024);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeigth, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
	glGenerateMipmap( GL_TEXTURE_2D );
	SOIL_free_image_data(image);
	glBindTexture( GL_TEXTURE_2D, 0 );

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );

	image = SOIL_load_image("resource/awesomeface.png", &imgWidth, &imgHeigth, 0, SOIL_LOAD_RGB);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeigth, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
	glGenerateMipmap( GL_TEXTURE_2D );
	SOIL_free_image_data(image);
	glBindTexture( GL_TEXTURE_2D, 0 );
#endif

    while ( !glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram( shaderProgram );
		glBindVertexArray( VAO );

		GLfloat timeValue = glfwGetTime();
		//GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		//GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glm::mat4 trans;
		trans = glm::rotate(trans, glm::radians(timeValue * 50.0f), glm::vec3(0, 0, 1.0));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));

		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);

		glActiveTexture( GL_TEXTURE1 );
		glBindTexture( GL_TEXTURE_2D, texture2);
		glUniform1i( glGetUniformLocation( shaderProgram, "ourTexture2" ), 1 );
		glUniform1f( glGetUniformLocation( shaderProgram, "mixValue" ), g_mixValue );

		glUniformMatrix4fv( glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans) );
	//	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

		//===========second=========
		GLfloat scaleValue = sin(timeValue);
		trans = glm::mat4();

		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		trans = glm::scale(trans, glm::vec3(scaleValue, scaleValue, scaleValue));

		glUniformMatrix4fv( glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans) );
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}