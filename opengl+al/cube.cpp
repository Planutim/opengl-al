#ifndef skiplol
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "camera.h"
#include "cube.h"
#include "sound.h"

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
double lastX = 800 / 2;
double lastY = 600 / 2;

Cube cubes[] = {
Cube(-6.0f, 0.3f, -3.0f, 1.2f, "StarWars3.wav"),
Cube(4.8f, -1.2f, -6.0f, 0.3f, "CantinaBand3.wav")
};

int main() {
	//init openal
	InitAL();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "mywindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

	Shader myShader("cube.vert", "cube.frag");


	float vertices[] = {
		//back
		-0.5f,-0.5f, -1.0f,
		-0.5f, 0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,
		-0.5f, 0.5f, -1.0f,
		0.5f, 0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,

		//left
		-0.5f, -0.5f, -1.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, -1.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f,  -1.0f,

		//right
		0.5f, -0.5f, -1.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, -1.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.5f,  -1.0f,

		//front
		- 0.5f,-0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,

		//up
		-0.5f,  0.5f, -1.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, -1.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, -1.0f,

		//down
		-0.5f,  -0.5f, -1.0f,
		-0.5f,  -0.5f, 0.0f,
		 0.5f,  -0.5f, -1.0f,
		-0.5f,  -0.5f, 0.0f,
		 0.5f,  -0.5f, 0.0f,
		 0.5f,  -0.5f, -1.0f,
	};





	unsigned int VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	myShader.use();
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	myShader.setMat4("projection", projection);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myShader.use();

		glm::mat4 view = camera.GetViewMatrix();
		myShader.setMat4("view", view);

		for (int i = 0; i < 2; i++)
		{
			glm::mat4 world = cubes[i].getWorldMatrix();

			myShader.setMat4("world", world);

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		cubes[0].play_sound();
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		cubes[1].play_sound();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		firstMouse = false;
		lastX = xpos;
		lastY = ypos;
	}

	float xoffset = (float)(xpos - lastX);
	float yoffset =(float)(lastY - ypos);

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset, true);
}

#endif