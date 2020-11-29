//#include<iostream>
//#include<glad/glad.h>
//#include<GLFW/glfw3.h>
//#include <string>
//#include <fstream>
//#include "helper.h"
//#include "stb_image.h";
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <map>
//#include <sstream>
//
//using namespace std;
//camera cam;
//float sWidth = 800;
//float sHeight = 600;
//void frameBuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//	cam.updateWH(width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		cam.keyDown(FORWARD);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		cam.keyDown(BACKWARD);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		cam.keyDown(LEFT);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		cam.keyDown(RIGHT);
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	cam.mouseMove(xpos, ypos);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	cam.mouseScroll(yoffset);
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	if (button == GLFW_MOUSE_BUTTON_RIGHT)
//	{
//		if (action == GLFW_PRESS)
//		{
//			cam.rightMouseDown = true;
//			cam.isFirst = true;
//		}
//		else if (action == GLFW_RELEASE)
//		{
//			cam.rightMouseDown = false;
//		}
//	}
//}
//
//
//void GLClearError()
//{
//	while (glGetError() != GL_NO_ERROR);
//}
//
//void GLCheckError()
//{
//	while (GLenum error = glGetError())
//	{
//		cout << "[OpenGL Error] (" << error << " )" << endl;
//	}
//}
//
//int main()
//{
//	glfwInit();
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(sWidth, sHeight, "123", NULL, NULL);
//	if (!window)
//	{
//		cout << "fail to init()" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		cout << "fail glad init()" << endl;
//		return -1;
//	}
//
//	glViewport(0, 0, sWidth, sHeight);
//	glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
//
//	float quadVertices[] = {
//		// Î»ÖÃ          // ÑÕÉ«
//		-0.005f,  0.005f,  1.0f, 0.0f, 0.0f,
//		 0.005f, -0.005f,  0.0f, 1.0f, 0.0f,
//		-0.005f, -0.005f,  0.0f, 0.0f, 1.0f,
//
//		-0.005f,  0.005f,  1.0f, 0.0f, 0.0f,
//		 0.005f, -0.005f,  0.0f, 1.0f, 0.0f,
//		 0.005f,  0.005f,  0.0f, 1.0f, 1.0f
//	};
//	glm::vec2 translations[10000];
//	int index = 0;
//	float offset = 0.01f;
//	for (int y = -100; y < 100; y += 2)
//	{
//		for (int x = -100; x < 100; x += 2)
//		{
//			glm::vec2 translation;
//			translation.x = (float)x / 100.0f + offset;
//			translation.y = (float)y / 100.0f + offset;
//			translations[index++] = translation;
//		}
//	}
//
//	unsigned int instanceVBO;
//	glGenBuffers(1, &instanceVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 10000, &translations[0], GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	unsigned int quadVAO, quadVBO;
//	glGenVertexArrays(1, &quadVAO);
//	glGenBuffers(1, &quadVBO);
//	glBindVertexArray(quadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//	glVertexAttribDivisor(2, 1);
//
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	//glEnable(GL_CULL_FACE);
//
//	shader sd1("instance1_vs.glsl", "instance1_fs.glsl");
//	sd1.use();
//
//	while (!glfwWindowShouldClose(window))
//	{
//		cam.deltaTime = glfwGetTime() - cam.lastFrame;
//		cam.lastFrame = glfwGetTime();
//
//		processInput(window);
//
//		glClearColor(0.2, 0.3, 0.3, 1.0);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		GLClearError();
//		sd1.setFloat("time", glfwGetTime());
//		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 10000);
//		GLCheckError();
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//
//	}
//	glfwTerminate();
//	return 0;
//}