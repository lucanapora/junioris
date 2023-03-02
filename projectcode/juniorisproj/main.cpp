//
//  main.cpp
//  juniorisproj
//
//  Created by Luca Napora on 2/21/23.
//
//#ifdef __APPLE__
//#include <OpenGL/gl3.h>
//#include <OpenGL/gl3ext.h>
//#endif
//allows dynamic version of library

#include <glad/glad.h>
//#define GLFW_DLL
#include <GLFW/glfw3.h>
//#include <GL/glew.h>

#include <iostream>

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
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

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

