//
//  main.cpp
//  OpenGL
//
//  Created by ddk on 2017/3/18.
//  Copyright © 2017年 ddk. All rights reserved.
//

#include <iostream>
#include <unistd.h>

//glew
#define GLEW_STATIC
#include <GL/glew.h>

//glfw
#include <GLFW/glfw3.h>

#include <math.h>

#include "SOIL/SOIL.h"

#include "ShaderFactory.h"
#include "DataCollect.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define DEF_WIDTH 800
#define DEF_HEIGHT 480

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
#if defined(OS_MAC)
    chdir("/Users/ddk/Desktop/Project/OpenGL/OpenGL/");
#elif defined(OS_WINDOW)
    chdir("/Users/ddk/Desktop/Project/OpenGL/OpenGL/");
#endif
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window       = createWindow(0, 0, DEF_WIDTH, DEF_HEIGHT);
    GLuint  shaderProgram    = ShaderFactory::getInstance()->createShader("shader/VertexShader.c", "shader/FragmentShader.c");

    glfwSetKeyCallback(window, keyCallBack);
    
    glEnable(GL_DEPTH_TEST);
    
    GLuint VAO, VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    /*
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof( GLfloat )));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof( GLfloat )));
	glEnableVertexAttribArray(2);
    */
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices_box), vertices_box, GL_STATIC_DRAW );
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0 );
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof( GLfloat )));
    glEnableVertexAttribArray(1);

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

	int imgWidth, imgHeigth;
    unsigned char* image = SOIL_load_image("resource/container.jpg", &imgWidth, &imgHeigth, 0,SOIL_LOAD_RGB);

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

    while ( !glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram( shaderProgram );
		glBindVertexArray( VAO );

		GLfloat timeValue = glfwGetTime();
		//GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		//GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glm::mat4 trans;
		//trans = glm::rotate(trans, glm::radians(timeValue * 50.0f), glm::vec3(0, 0, 1.0));
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));

		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);

		glActiveTexture( GL_TEXTURE1 );
		glBindTexture( GL_TEXTURE_2D, texture2);
		glUniform1i( glGetUniformLocation( shaderProgram, "ourTexture2" ), 1 );
		glUniform1f( glGetUniformLocation( shaderProgram, "mixValue" ), g_mixValue );

		glUniformMatrix4fv( glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans) );
        
        glm::mat4 model, view, projection;
        //model = glm::rotate(model, glm::radians(timeValue * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        view    = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f) );
        projection = glm::perspective(glm::radians(45.0f), (GLfloat)DEF_WIDTH/(GLfloat)DEF_HEIGHT, 0.1f, 100.0f);
        
        //glUniformMatrix4fv( glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model) );
        glUniformMatrix4fv( glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view) );
        glUniformMatrix4fv( glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection) );
        
        for ( int i=0; i < 10; ++i) {
            glm::mat4 _model;
            _model = glm::translate(_model, cubePositions[i]);
            GLfloat angle;
            if ( i%3 == 0 ) {
                angle = 20.0f * ( i + 0.1f) * timeValue; 
            } else {
                angle = 20.0f * i;
            }
            _model = glm::rotate(_model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv( glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(_model) );
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        

       
       // glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
        
		//===========second=========
        /*
		GLfloat scaleValue = fabs(sin(timeValue));
		trans = glm::mat4();

		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		trans = glm::scale(trans, glm::vec3(scaleValue, scaleValue, scaleValue));

		glUniformMatrix4fv( glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans) );
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
         */
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
