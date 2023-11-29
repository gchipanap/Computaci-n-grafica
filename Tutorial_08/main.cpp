#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include <iostream>
#include <cmath>

#define PI 3.14159f

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void RenderSineWave();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Scales
float ScaleX = 1.0f;
float ScaleY = 1.0f;
float ScaleZ = 1.0f;
//Transalte
float TranX = 0.0f;
float TranY = 0.0f;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;\n" //mat 4x4
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource ="#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 0.0f);\n"  //white
"}\n\0";

int main(int argc, char** argv)
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

    glfwSetKeyCallback(window, key_callback);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
    

      //Circulo
    float radius = 0.5f;
    float radius2 = 0.7f;
    constexpr int lados = 150; //invariable
    constexpr int olas = 200;  //20*10
    float step = ( 2 * PI) / (float)lados;

    float vertices[lados * 3 + 3];
    int i = 0;
    for (float a = 0.0f; a < 2*PI; a += step)
    {
        vertices[i + 0] = radius * cos(a);
        vertices[i + 1] = radius * sin(a);
        vertices[i + 2] = 0.0f;
        i += 3;
    }

    vertices[lados * 3 + 0] = 0.0f;
    vertices[lados * 3 + 1] = 0.0f;
    vertices[lados * 3 + 2] = 0.0f;

    float vertices2[lados * 3 + 3];
    i = 0;
    for (float a = 0.0f; a < 2*PI; a += step)
    {
        vertices2[i + 0] = radius2 * cos(a);
        vertices2[i + 1] = radius2 * sin(a);
        vertices2[i + 2] = 0.0f;
        i += 3;
    }

    vertices2[lados * 3 + 0] = 0.0f;
    vertices2[lados * 3 + 1] = 0.0f;
    vertices2[lados * 3 + 2] = 0.0f;

    unsigned int indices[lados * 3];
    for (int i = 0; i < lados - 1; i += 1)
    {
        indices[3 * i + 0] = lados;
        indices[3 * i + 1] = i;
        indices[3 * i + 2] = i + 1;
    }

    indices[3 * (lados - 1) + 0] = lados;
    indices[3 * (lados - 1) + 1] = lados - 1;
    indices[3 * (lados - 1) + 0] = 0;

    unsigned int VBO[2], VAO[2], EBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    //1
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //2
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    float* colors = new float[lados];
    for (int i = 0; i < lados; i++)
    {
        colors[i] = (float)i / (float)(lados - 1);
    }
    float colorIdx = 0.0f;
    double lastTimeValue = glfwGetTime();
    double segs = 0.01;


    float transformation[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    float transalate[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0, 0.0, 0.0, 1.0);  //  0.1f, 0.5f, 1.0f, 1.0f
        glClear(GL_COLOR_BUFFER_BIT);

        transformation[0 * 4 + 0] = ScaleX;
        transformation[1 * 4 + 1] = ScaleY;
        transformation[2 * 4 + 2] = ScaleZ;

        transformation[0 * 4 + 3] = TranX;
        transformation[1 * 4 + 3] = TranY;

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, transformation);

        glUseProgram(shaderProgram);

        double  timeValue = glfwGetTime();
        double deltaTime = timeValue - lastTimeValue;
        lastTimeValue = timeValue;

        
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        colorIdx += deltaTime / segs;

        glBindVertexArray(VAO[1]);
        for (int i = lados - 1; i >= 0; i--)
        {
            glUniform4f(vertexColorLocation, 1.0f, colors[((int)colorIdx + i) % lados], 1.0f, 0.0f);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (const void*)(i * 3 * sizeof(unsigned int)));
        }
        glBindVertexArray(0);
        
        glBindVertexArray(VAO[0]);
        for (int i = 0; i < lados; i++)
        {
            glUniform4f(vertexColorLocation, 1.0f , 0.0f, colors[((int)colorIdx + i) % lados], 0.0f);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (const void*)(i * 3 * sizeof(unsigned int)));
        }
        glBindVertexArray(0);    
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(2, EBO);
    glDeleteProgram(shaderProgram);
    delete[] colors;

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        ScaleX += 0.01f;
        ScaleY += 0.01f;
        ScaleZ += 0.01f;
    }
    else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        ScaleX -= 0.01f;
        ScaleY -= 0.01f;
        ScaleZ -= 0.01f;
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        TranY -= 0.1f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        TranY += 0.1f;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        TranX -= 0.1f;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        TranX += 0.1f;
    }
}
