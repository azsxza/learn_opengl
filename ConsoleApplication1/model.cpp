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
//
//using namespace std;
//camera cam;
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
//int main()
//{
//	glfwInit();
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(800, 600, "123", NULL, NULL);
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
//	glViewport(0, 0, 800, 600);
//	glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_CULL_FACE);
//
//	glm::vec3 pointLightPositions[] = {
//glm::vec3(0.7f,  0.2f,  2.0f),
//glm::vec3(2.3f, -3.3f, -4.0f),
//glm::vec3(-4.0f,  2.0f, -12.0f),
//glm::vec3(0.0f,  0.0f, -3.0f)
//	};
//
//	model mModel("./nanosuit/nanosuit.obj");
//	shader sd1("model1_vs.glsl", "model1_fs.glsl");
//	sd1.use();
//
//	sd1.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//	sd1.setFloat("material.shininess", 64.0f);
//
//
//	// directional light
//	sd1.setVec3("dLight.direction", -0.2f, -1.0f, -0.3f);
//	sd1.setVec3("dLight.ambient", 0.35f);
//	sd1.setVec3("dLight.diffuse", 0.9f);
//	sd1.setVec3("dLight.specular", 0.9f);
//	// point light 1
//	sd1.setVec3("pLight[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
//	sd1.setVec3("pLight[0].ambient", 0.15f);
//	sd1.setVec3("pLight[0].diffuse", 0.8f, 0.8f, 0.8f);
//	sd1.setVec3("pLight[0].specular", 1.0f, 1.0f, 1.0f);
//	sd1.setFloat("pLight[0].constant", 1.0f);
//	sd1.setFloat("pLight[0].linear", 0.09);
//	sd1.setFloat("pLight[0].quadratic", 0.032);
//	// point light 2
//	sd1.setVec3("pLight[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
//	sd1.setVec3("pLight[1].ambient", 0.15f);
//	sd1.setVec3("pLight[1].diffuse", 0.8f, 0.8f, 0.8f);
//	sd1.setVec3("pLight[1].specular", 1.0f, 1.0f, 1.0f);
//	sd1.setFloat("pLight[1].constant", 1.0f);
//	sd1.setFloat("pLight[1].linear", 0.09);
//	sd1.setFloat("pLight[1].quadratic", 0.032);
//	// point light 3
//	sd1.setVec3("pLight[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
//	sd1.setVec3("pLight[2].ambient", 0.15f);
//	sd1.setVec3("pLight[2].diffuse", 0.8f, 0.8f, 0.8f);
//	sd1.setVec3("pLight[2].specular", 1.0f, 1.0f, 1.0f);
//	sd1.setFloat("pLight[2].constant", 1.0f);
//	sd1.setFloat("pLight[2].linear", 0.09);
//	sd1.setFloat("pLight[2].quadratic", 0.032);
//	// point light 4
//	sd1.setVec3("pLight[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
//	sd1.setVec3("pLight[3].ambient", 0.05f, 0.05f, 0.05f);
//	sd1.setVec3("pLight[3].diffuse", 0.8f, 0.8f, 0.8f);
//	sd1.setVec3("pLight[3].specular", 1.0f, 1.0f, 1.0f);
//	sd1.setFloat("pLight[3].constant", 1.0f);
//	sd1.setFloat("pLight[3].linear", 0.09);
//	sd1.setFloat("pLight[3].quadratic", 0.032);
//
//	auto modelLoc = sd1.getUniformLocation("model");
//	auto viewLoc = sd1.getUniformLocation("view");
//	auto projectionLoc = sd1.getUniformLocation("projection");
//	auto viewPosLoc = sd1.getUniformLocation("viewPos");
//
//
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
//		sd1.use();
//		sd1.setMat4(viewLoc, cam.getViewMatrix());
//		sd1.setMat4(projectionLoc, cam.getProjectionMatrix());
//		sd1.setVec3(viewPosLoc, cam.positon.x, cam.positon.y, cam.positon.z);
//
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	
//		sd1.setMat4("model", model);
//		mModel.draw(sd1);
//		
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//
//	}
//	glfwTerminate();
//	return 0;
//}