#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void renderTriangules(int i, int f, unsigned int shaderprogram, unsigned int* VAO);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);\n"  //red
"}\n\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 0.0f);\n"  //rellow
"}\n\0";

const char* fragmentShaderSource3 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.0f, 1.0f, 0.0f);\n"  //purple
"}\n\0";

const char* fragmentShaderSource4 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"  //lightblue
"}\n\0";

const char* fragmentShaderSource5 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.0f, 0.0f);\n"  //orange
"}\n\0";

const char* fragmentShaderSource6 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.1f, 0.1f);\n"  //
"}\n\0";

const char* fragmentShaderSource7 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.0f, 1.9f);\n"  //
"}\n\0";

const char* fragmentShaderSource8 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 0.0f);\n"  //white
"}\n\0";

int main()
{
    //Inicializa y configura glfw  

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Turorial3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // vertex shader
    std::vector< const char*> fragmentCod;
    fragmentCod.reserve(8);
    fragmentCod.push_back(fragmentShaderSource);
    fragmentCod.push_back(fragmentShaderSource2);
    fragmentCod.push_back(fragmentShaderSource3);
    fragmentCod.push_back(fragmentShaderSource4);
    fragmentCod.push_back(fragmentShaderSource5);
    fragmentCod.push_back(fragmentShaderSource6);
    fragmentCod.push_back(fragmentShaderSource7);
    fragmentCod.push_back(fragmentShaderSource8);

    std::vector<unsigned int> fragmentShaders;
    fragmentShaders.reserve(8);

    for (int i = 0; i < 8; i++)
    {
        fragmentShaders.push_back(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fragmentShaders[i], 1, &fragmentCod[i], NULL);
        glCompileShader(fragmentShaders[i]);

        int success;
        char infoLog[512];

        glGetShaderiv(fragmentShaders[i], GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShaders[i], 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    

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

    
    std::vector<unsigned int> shaderPrograms;
    shaderPrograms.reserve(8);

    for (int i = 0; i < 8; i++)
    {
        shaderPrograms.push_back(glCreateProgram());

        glAttachShader(shaderPrograms[i], vertexShader);
        glAttachShader(shaderPrograms[i], fragmentShaders[i]);
        glLinkProgram(shaderPrograms[i]);

        int success;
        char infoLog[512];

        glGetProgramiv(shaderPrograms[i], GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderPrograms[i], 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }

    glDeleteShader(vertexShader);
    for (int i = 0; i < 8; i++)
        glDeleteShader(fragmentShaders[i]);
    

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float T1[] = {
        -0.7f, -0.5f, 0.0f,
        -0.7f, 0.5f, 0.0f, 
        -0.5f, 0.5f, 0.0f
    };

    float T2[] = { 
         -0.7f, -0.5f, 0.0f, 
         -0.5f, 0.5f, 0.0f,
         -0.5f, -0.5f, 0.0f
    };
    float T3[] = {  
        -0.5f, 0.5f, 0.0f, // C  
        -0.5f, -0.5f, 0.0f,
        -0.3f,  0.5f, 0.0f  // 4   
    };
    float T4[] = { 
        -0.5f, -0.5f, 0.0f, //D
        -0.3f, -0.5f, 0.0f,
        -0.3f,  0.5f, 0.0f // 5
    };
    float T5[] = {//5
        -0.1f, 0.5f, 0.0f, // E
        -0.3f, -0.5f, 0.0f,
        -0.3f,  0.5f, 0.0f
    };

    float T6[] = { 
        -0.1f, 0.5f, 0.0f,
        -0.1f, -0.5f, 0.0f,
        -0.3f, -0.5f, 0.0f //7
    };
    float T7[] = {
        -0.1f, 0.5f, 0.0f,
        -0.1f, -0.5f, 0.0f,
        0.1f, 0.5f, 0.0f //8
    };
    float T8[] = {
        0.1f, -0.5f, 0.0f,
        0.1f, 0.5f, 0.0f,
        -0.1f, -0.5f, 0.0f
    };
    float T9[] = {
        0.1f, -0.5f, 0.0f,
        0.1f, 0.5f, 0.0f,
        0.3f, -0.5f, 0.0f
    };
    float T10[] = {
        0.3f, -0.5f, 0.0f,
        0.3f, 0.5f, 0.0f,
        0.1f, 0.5f, 0.0f
    };
    float T11[] = {
        0.3f, -0.5f, 0.0f,
        0.3f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };
    float T12[] = {
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.3f, -0.5f, 0.0f
    };
    float T13[] = {
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.7f, -0.5f, 0.0f
    };
    float T14[] = {
        0.7f, -0.5f, 0.0f,
        0.7f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };
    unsigned int VBO[14], VAO[14]; 
    glGenVertexArrays(14, VAO);
    glGenBuffers(14, VBO);

    //1
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T1), T1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //2
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T2), T2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //3
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T3), T3, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //4
    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T4), T4, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //5
    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T5), T5, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //6
    glBindVertexArray(VAO[5]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T6), T6, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //7
    glBindVertexArray(VAO[6]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T7), T7, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //8
    glBindVertexArray(VAO[7]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T8), T8, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //9
    glBindVertexArray(VAO[8]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[8]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T9), T9, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //10
    glBindVertexArray(VAO[9]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T10), T10, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //11
    glBindVertexArray(VAO[10]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T11), T11, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //12
    glBindVertexArray(VAO[11]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[11]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T12), T12, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //13
    glBindVertexArray(VAO[12]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[12]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T13), T13, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //14
    glBindVertexArray(VAO[13]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[13]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T14), T14, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    int iterator = 0;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.1f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (iterator == 0)
        {
            renderTriangules(0, 2, shaderPrograms[0], VAO);
            renderTriangules(2, 4, shaderPrograms[1], VAO);
            renderTriangules(4, 6, shaderPrograms[2], VAO);
            renderTriangules(6, 8, shaderPrograms[3], VAO);
            renderTriangules(8, 10, shaderPrograms[4], VAO);
            renderTriangules(10, 12, shaderPrograms[5], VAO);
            renderTriangules(12, 14, shaderPrograms[6], VAO);

            iterator = 1;
        }
        else if (iterator == 1)
        {
            renderTriangules(0, 2, shaderPrograms[6], VAO);
            renderTriangules(2, 4, shaderPrograms[0], VAO);
            renderTriangules(4, 6, shaderPrograms[1], VAO);
            renderTriangules(6, 8, shaderPrograms[2], VAO);
            renderTriangules(8, 10, shaderPrograms[3], VAO);
            renderTriangules(10, 12, shaderPrograms[4], VAO);
            renderTriangules(12, 14, shaderPrograms[5], VAO);

            iterator = 2;
        }
        else if (iterator == 2)
        {
            renderTriangules(0, 2, shaderPrograms[5], VAO);
            renderTriangules(2, 4, shaderPrograms[6], VAO);
            renderTriangules(4, 6, shaderPrograms[0], VAO);
            renderTriangules(6, 8, shaderPrograms[1], VAO);
            renderTriangules(8, 10, shaderPrograms[2], VAO);
            renderTriangules(10, 12, shaderPrograms[3], VAO);
            renderTriangules(12, 14, shaderPrograms[4], VAO);

            iterator = 3;
        }
        else if (iterator == 3)
        {
            renderTriangules(0, 2, shaderPrograms[4], VAO);
            renderTriangules(2, 4, shaderPrograms[5], VAO);
            renderTriangules(4, 6, shaderPrograms[6], VAO);
            renderTriangules(6, 8, shaderPrograms[0], VAO);
            renderTriangules(8, 10, shaderPrograms[1], VAO);
            renderTriangules(10, 12, shaderPrograms[2], VAO);
            renderTriangules(12, 14, shaderPrograms[3], VAO);

            iterator = 4;
        }
        else if (iterator == 4)
        {
            renderTriangules(0, 2, shaderPrograms[3], VAO);
            renderTriangules(2, 4, shaderPrograms[4], VAO);
            renderTriangules(4, 6, shaderPrograms[5], VAO);
            renderTriangules(6, 8, shaderPrograms[6], VAO);
            renderTriangules(8, 10, shaderPrograms[0], VAO);
            renderTriangules(10, 12, shaderPrograms[1], VAO);
            renderTriangules(12, 14, shaderPrograms[2], VAO);

            iterator = 5;
        }
        else if (iterator == 5)
        {
            renderTriangules(0, 2, shaderPrograms[2], VAO);
            renderTriangules(2, 4, shaderPrograms[3], VAO);
            renderTriangules(4, 6, shaderPrograms[4], VAO);
            renderTriangules(6, 8, shaderPrograms[5], VAO);
            renderTriangules(8, 10, shaderPrograms[6], VAO);
            renderTriangules(10, 12, shaderPrograms[0], VAO);
            renderTriangules(12, 14, shaderPrograms[1], VAO);

            iterator = 6;
        }
        else if (iterator == 6)
        {
            renderTriangules(0, 2, shaderPrograms[1], VAO);
            renderTriangules(2, 4, shaderPrograms[2], VAO);
            renderTriangules(4, 6, shaderPrograms[3], VAO);
            renderTriangules(6, 8, shaderPrograms[4], VAO);
            renderTriangules(8, 10, shaderPrograms[5], VAO);
            renderTriangules(10, 12, shaderPrograms[6], VAO);
            renderTriangules(12, 14, shaderPrograms[0], VAO);

            iterator = 0;
        }
  

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(13, VAO);
    glDeleteBuffers(13, VBO);
    for (int i = 0; i < 8; i++)
        glDeleteProgram(shaderPrograms[i]);

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

void renderTriangules(int i, int f, unsigned int shaderprogram, unsigned int* VAO)
{
    for (int k = i; k < f; k++)
    {
        glUseProgram(shaderprogram);
        glBindVertexArray(VAO[k]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
}

void renderTriangules(std::vector<unsigned int> shaderprogram, unsigned int* VAO, int i)
{
    renderTriangules(i+0, i+2, shaderprogram[i], VAO);
    renderTriangules(i+2, i+4, shaderprogram[i], VAO);
    renderTriangules(i+4, i+6, shaderprogram[i], VAO);
    renderTriangules(i+6, i+8, shaderprogram[i], VAO);
    renderTriangules(i+8, i+10, shaderprogram[i], VAO);
    renderTriangules(i+10, i+12, shaderprogram[i], VAO);
    renderTriangules(i+12, i+14, shaderprogram[i], VAO);
   
}