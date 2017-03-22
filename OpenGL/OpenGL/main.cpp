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

#include "ShaderFactory.h"
#include "DataCollect.h"

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
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
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
    GLuint  shaderProgram       = ShaderFactory::getInstance()->createShader("./shader/VertexShader.c", "./shader/FragmentShader.c");
    
    glfwSetKeyCallback(window, keyCallBack);
    
    GLuint VBO;
    glGenBuffers( 1， &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    
    while ( !glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
    
        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}
