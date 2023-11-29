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
"   FragColor = vec4(0.0,0.0,3.0,2.0);\n"  //blue
"}\n\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.1f, 0.0f, 0.1f, 0.0f);\n"  //black
"}\n\0";

const char* fragmentShaderSource3 = "#version 330 core\n"
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


    // build and compile our shader program
    // ------------------------------------

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


    // 1 fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 2 fragment shader
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 3 fragment shader - Borde 

    unsigned int fragmentShader3 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader3, 1, &fragmentShaderSource3, NULL);
    glCompileShader(fragmentShader3);

    glGetShaderiv(fragmentShader3, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader3, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    // link shaders
    //1
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //2
    unsigned int shaderProgram2 = glCreateProgram();

    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    //3 
    unsigned int shaderProgram3 = glCreateProgram();

    glAttachShader(shaderProgram3, vertexShader);
    glAttachShader(shaderProgram3, fragmentShader3);
    glLinkProgram(shaderProgram3);

    // check for linking errors
    //1
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //2
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //3
    glGetProgramiv(shaderProgram3, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram3, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
 
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
    glDeleteShader(fragmentShader3);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float T1[] = {
        -0.7f, -0.3f, 0.0f, //A  
         0.0f, 0.0f, 0.0f, 
        -0.5f,  0.22f, 0.0f  //2   
    };

    float T2[] = { 
         -0.7f, 0.3f, 0.0f, //B 
         0.0f, 0.0f, 0.0f,
         -0.2175f,  0.5f, 0.0f  //3   
    };
    float T3[] = {  
       -0.3f, 0.7f, 0.0f, // C  
        0.0f, 0.0f, 0.0f,
        0.2175f,  0.5f, 0.0f  // 4   
    };
    float T4[] = { 
        0.3f, 0.7f, 0.0f, //D
        0.0f, 0.0f, 0.0f,
        0.5f, 0.22f, 0.0f // 5
    };
    float T5[] = {//5
        0.7f, 0.3f, 0.0f, // E
        0.0f, 0.0f, 0.0f,
        0.5f, -0.2175f, 0.0f //  6
    };

    float T6[] = { 
        0.7f, -0.3f, 0.0f, //F
        0.0f, 0.0f, 0.0f,
        0.218f, -0.5f, 0.0f //7
    };
    float T7[] = {
        0.3f, -0.7f, 0.0f, //G
        0.0f, 0.0f, 0.0f,
        -0.2175f, -0.5f, 0.0f //8
    };
    float T8[] = {
        -0.3f,  -0.7f, 0.0f, //H
        0.0f, 0.0f, 0.0f,
        -0.5f, -0.22f, 0.0f //1
    };

    float T9[] = {
        -0.7f, -0.3f, 0.0f,//A
        -0.422f, -0.4f, 0.0f, 
        -0.5f, -0.22f, 0.0f //1
    };
    float T10[] = {
        -0.585f,  0.0f, 0.0f,
        -0.5f,  0.2175f, 0.0f,  //2  
        -0.7f, 0.3f, 0.0f //B 
    };
    float T11[] = {
        0.0f,  0.585f, 0.0f, //c
        0.3f, 0.7f, 0.0f, //D  
        0.2175f,  0.5f, 0.0f//4
        
    };
    float T12[] = {
        -0.3f,  -0.7f, 0.0f,//H
        0.0f, -0.585f, 0.0f, 
        -0.2175f, -0.5f, 0.0f
    };
    float T13[] = {
        -0.45f,  0.4f, 0.0f,
        -0.3f, 0.7f, 0.0f, //C
         -0.22f,  0.5f, 0.0f  //3 
    };
    float T14[] = {
        0.4f,  0.455f, 0.0f,
        0.7f, 0.3f, 0.0f, // E
        0.5f, 0.22f, 0.0f // 5
    };
    float T15[] = {
        0.5f, -0.22f, 0.0f,
        0.7f, -0.3f, 0.0f, //F
        0.582f, 0.0f, 0.0f
    };
    float T16[] = {
         0.22f, -0.5f, 0.0f, //7
        0.4f, -0.42f, 0.0f,
        0.3f, -0.7f, 0.0f //G
    };

    unsigned int VBO[16], VAO[16]; 
    glGenVertexArrays(16, VAO);
    glGenBuffers(16, VBO);

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

    //15
    glBindVertexArray(VAO[14]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[14]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T15), T15, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //16
    glBindVertexArray(VAO[15]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[15]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T16), T16, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.1f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        renderTriangules(0, 8, shaderProgram, VAO);
        renderTriangules(8, 16, shaderProgram2, VAO);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        renderTriangules(0, 16, shaderProgram3, VAO);
      
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(13, VAO);
    glDeleteBuffers(13, VBO);
    glDeleteProgram(shaderProgram);

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