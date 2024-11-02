#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"


const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;



bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.02f;

float curAngle = 0.0f;

//vertex shader
static const char* vShader = "Shader/shader.vert";

//fragement shader
static const char* fShader = "Shader/shader.frag";



void CreateObjects()
{
	unsigned int indices[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2

	};

	GLfloat vertices[] =
	{
		-1.0f, -1.0f,0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f,-1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
	
     Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);

}



void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromString(vShader, fShader);
	shaderList.push_back(*shader1);

 }

int main()
{
	if (!glfwInit())
	{
		std::cout << "glfw initialisation failed!" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "test window", NULL, NULL);
	if (!mainWindow)
	{
		std::cout << "glfw window failed" << std::endl;
		glfwTerminate();
		return 1;
	}

	//get buffer size info
	int bufferwidth, bufferheight;
	glfwGetFramebufferSize(mainWindow, &bufferwidth, &bufferheight);

	//set context for glfw to use
	glfwMakeContextCurrent(mainWindow);

	//allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew init failed" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}


	//depth buffer
	glEnable(GL_DEPTH_TEST);

	//set viewport size
	glViewport(0, 0, bufferwidth, bufferheight);

	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0, uniformModel = 0;

	glm::mat4 projection = glm::perspective(45.0f, GLfloat(bufferwidth / bufferheight), 0.1f, 100.0f);

	//loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		//get a handle user in put event
		glfwPollEvents();

		if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;

		}

		curAngle += 0.2f;
		if (curAngle >= 360)
		{
			curAngle -= 360;
		}

		//clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();

		glm::mat4x4 model(1.0f);
		
		model = glm::translate(model, glm::vec3(triOffset,0.0f, -2.5f));
		
		model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-triOffset, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);


	}


	return 0;
}