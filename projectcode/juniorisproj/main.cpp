//
//  main.cpp
//  juniorisproj
//
//  Created by Luca Napora on 2/21/23.
//
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

//#include <GL/glew.h>
#include <GLFW/glfw3.h>
//include shader file
#include "shader.hpp"

//using namespace glm;


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Luca Napora", NULL, NULL);
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    
    //trying to make a triangle
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    //three points initialized to make a triangle
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    
    //create a buffer so the triangle can be given to OpenGL
    GLuint vertexbuffer;
    //creates one buffer who's identifier is stored in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    //give our vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glDrawArrays(GL_TRIANGLES,0,3); //this is where you start
    glDisableVertexAttribArray(0);
        
                          
                          
    GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
    
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programID);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
