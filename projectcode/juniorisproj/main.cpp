#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

//vertex shader -written in glsl and converted to a string
//the output of our shader (gl_position) is the coordinates of our vector (that is of size 4)

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"

    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
   // "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0); \n"
    "}\0";

//fragment shader in glsl that defines the color of our vertices
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
   // "uniform vec4 ourColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\n\0";


int main()
{
    //initialize glfw with opengl version 3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //final hint that's neccessary for mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    //creates window object with width to scale and height to scale
    GLFWwindow* window = glfwCreateWindow(800, 600, "Luca's First Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //makes this window the current context
    glfwMakeContextCurrent(window);
    
    //calls the callback function to make sure opengl viewport is same size as window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   //load glad - from tutorial
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //defines 3d coordinates for the triangle (length, width, depth) and color values for each vertex
    float vertices[] {
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f
        
       // -0.125f, -0.125f, 0.0f,
        //0.125f, -0.125f, 0.0f,
        //0.0f, 0.0f, 0.0f,
    };
    
    //creates an opengl vertex buffer object - buffer that holds data about vertices for graphics card
    unsigned int VBO;
    
    glGenBuffers(1, &VBO);
    //binds the buffer type ( gl_array_buffer) with VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //creates a vertix attribute object and bind it
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    //this function copies our vertice data into the currently bound buffer (vbo)
    //gl_static_draw specifies that the data is set only once and used many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //as of right now our vertice data is stored in a buffer (vbo) which stored in memory on graphics card- need vertex and fragment shaders to process this data
    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    //links and compiles the vertexshader object with vertexshader source
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    //checks for erros with vertex shader - from tutorial
    int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    
    //also need a fragment shader to dictate the color of our pixels
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    //check for erros with fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
       if (!success)
       {
           glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
           std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
       }
    
    //now that both shaders are compiled, we need to build shader program to use during rendering
    //shader program object is the linked version of multiple shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //we still have to instruct gpu how to interpret the vertex data and link it with the shaders
    
    //position attribute for vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    //color attribute for vertex
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    
    
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        //processes keyboard input
        processInput(window);

        //specifies what color to clear the window
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //clears the window with that color
        glClear(GL_COLOR_BUFFER_BIT);

        //implements the shader program, the voa, and draws the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        //used for multiple triangles
       // glUseProgram(shaderProgram);
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        
        //sets color of uniform for triangle
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.5, 0.5, 0.0, 1.0);
        
        //swaps the color buffers
        glfwSwapBuffers(window);
        
        //checks for keyboard input or mouse movement
        glfwPollEvents();
    }

    //clears everything when process is terminated
    glfwTerminate();
    return 0;
}

//processes keyboard input: if escape key is pressed it closes window
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //tells opengl the dimensions of our window
    //this function changes the viewport everytime the window size is changed
    glViewport(0, 0, width, height);
}
