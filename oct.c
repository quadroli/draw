#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH	600
#define WINDOW_HEIGHT	600
#define WINDOW_TITLE	"Octa less goooooooo!!!!!"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = 
  "#version 330 core\n" 
  "layout (location = 0) in vec3 apos;\n" 
  "void main()\n" 
  "{\n"
  "	gl_Position = vec4(apos.x, apos.y, apos.z, 1.0);\n" 
  "}\0";

const char *fragmentShaderSource =
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  " FragColor = vec4(0.16f, 0.94f, 0.76f, 1.0f);\n "
  "}\0";

/*Unique points to draw*/
float vertices[9][3] = {
  {-0.25f,0.5f,0.0f},
  {0.25f,0.5f,0.0f},
  {0.5f,0.25f,0.0f},
  {0.5f,-0.25f,0.0f},
  {0.25f,-0.5f,0.0f},
  {-0.25f,-0.5f,0.0f},
  {-0.5f,-0.25f,0.0f},
  {-0.5f,0.25f,0.0f},
  {0.0f,0.0f,0.0f}
};
/*How to draw each point*/
unsigned int indices[24] =
{
0,1,8,
1,2,8,
2,3,8,
3,4,8,
4,5,8,
5,6,8,
6,7,8,
7,0,8
};

int
main()
{
/*Window initialisation*/
 glfwInit();
 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
 glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_TITLE,NULL,NULL);
  if (window == NULL){
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);/*makes created window current context in current thread*/
  glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);/*use window resize call back*/

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){/*load appropriate OpenGl functions and error checking*/
    /*Error handling*/
    printf("Failed to initialise GLAD");
    glfwTerminate();
    return -1;
  }

  unsigned int VAO,VBO,EBO;/*Vertex array object and vertex buffer object id initialization*/
  glGenVertexArrays(1,&VAO);/*Vertex Array Object creation*/

  glGenBuffers(1, &VBO);/*Vertex Buffer Object creation*/

  glGenBuffers(1, &EBO);/*Element Buffer Object creation*/

  glBindVertexArray(VAO);/*Bind Vertex array Object*/

  glBindBuffer(GL_ARRAY_BUFFER, VBO);/*Bind Vertex Buffer Object to GL_ARRAY_BUFFER*/
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);/*Copy data within multidimensional array vertices to buffer object*/
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);/*Bind to created EBO*/
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);/*copies data in indices to EBO*/

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);/*Initializes Vertex Shader*/
  glShaderSource(vertexShader,1, &vertexShaderSource,NULL);/*Creates Vertex Shader*/
  glCompileShader(vertexShader);/*Compiles vertex shader*/

  /*Same but now for the fragment shader*/
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
  glCompileShader(fragmentShader);

  /*Create shader program to be used*/
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  /*Attach shaders*/
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  /*Link program*/
  glLinkProgram(shaderProgram);

  /*Dispose of shaders now that they have been linked in shader program*/
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float), (void *) 0); /*Tell OpenGl how to interpret Vertex attributes*/
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)){/*loop while checking if window should close*/
    
    /*input*/
    processInput(window);

    /*Screen clearing*/
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);/*Use created shader program*/
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

    /*Buffer swapping, prevents artifact creation and tearing*/
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  /*You may flee*/
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}

/*call back for window resize*/
void
framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0,0,width,height);/*Set size of OpenGl viewport, first two parameters set position of bottom left corner*/
}

/*Escape key poll*/
void 
processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/*
 * author @Limisi
*/ 
