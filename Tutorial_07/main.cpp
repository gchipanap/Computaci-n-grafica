#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#define PI 3.14159f

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Circulo
    float radius = 0.5f;
    constexpr int lados = 1024; //invariable
    float step = (2 * PI) / (float)lados;

    float vertices[lados * 3 + 3];
    int i = 0;
    for (float a = 0.0f; a < 2 * PI; a += step)
    {
        vertices[i + 0] = radius * cos(a);
        vertices[i + 1] = radius * sin(a);
        vertices[i + 2] = 0.0f;
        i += 3;
    }

    vertices[lados * 3 + 0] = 0.0f;
    vertices[lados * 3 + 1] = 0.0f;
    vertices[lados * 3 + 2] = 0.0f;

    unsigned int indices[lados * 3];
    for (int i = 0; i < lados-1; i += 1)
    {
        indices[3 * i + 0] = lados;
        indices[3 * i + 1] = i;
        indices[3 * i + 2] = i + 1;
    }

    indices[3 * (lados - 1) + 0] = lados;
    indices[3 * (lados - 1) + 1] = lados - 1;
    indices[3 * (lados - 1) + 0] = 0;

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    float redvalue = 1.0f;
    float bluevalue = 1.0f;

    float* colors = new float [lados];
    for (int i = 0; i < lados; i++)
    {
        colors[i] = (float)i / (float)(lados-1);
    }
    float colorIdx = 0.0f;
    double lastTimeValue = glfwGetTime();
    double segs = 0.002;
    
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //
        glUseProgram(shaderProgram);


        double  timeValue = glfwGetTime();
        double deltaTime = timeValue - lastTimeValue;
        lastTimeValue = timeValue;

            
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        colorIdx += deltaTime/segs;
        

        glBindVertexArray(VAO);
        for (int i = 0; i < lados; i++)
        {
            glUniform4f(vertexColorLocation, cos(colorIdx*segs*0.5) / 2 + 0.5, colors[((int)colorIdx + i) % lados], sin(colorIdx*segs*0.5) / 2 + 0.5, 1.0f);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (const void *)(i*3*sizeof(unsigned int)));
        }

        
        glBindVertexArray(0);

        // render the triangle
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    delete[] colors;


    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}