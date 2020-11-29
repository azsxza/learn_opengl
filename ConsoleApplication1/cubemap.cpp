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
//	float vertices[] = {
//		// positions          // normals           // texture coords
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
//
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f
//
//	};
//	glm::vec3 cubePositions[] = {
//	  glm::vec3(0.0f,  0.0f,  0.0f),
//	  glm::vec3(2.0f,  5.0f, -15.0f),
//	  glm::vec3(-1.5f, -2.2f, -2.5f),
//	  glm::vec3(-3.8f, -2.0f, -12.3f),
//	  glm::vec3(2.4f, -0.4f, -3.5f),
//	  glm::vec3(-1.7f,  3.0f, -7.5f),
//	  glm::vec3(1.3f, -2.0f, -2.5f),
//	  glm::vec3(1.5f,  2.0f, -2.5f),
//	  glm::vec3(1.5f,  0.2f, -1.5f),
//	  glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//	glm::vec3 pointLightPositions[] = {
//	glm::vec3(0.7f,  0.2f,  2.0f),
//	glm::vec3(2.3f, -3.3f, -4.0f),
//	glm::vec3(-4.0f,  2.0f, -12.0f),
//	glm::vec3(0.0f,  0.0f, -3.0f)
//	};
//	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//		// positions   // texCoords
//		-1.0f,  1.0f,  0.0f, 1.0f,
//		-1.0f, -1.0f,  0.0f, 0.0f,
//		 1.0f, -1.0f,  1.0f, 0.0f,
//
//		-1.0f,  1.0f,  0.0f, 1.0f,
//		 1.0f, -1.0f,  1.0f, 0.0f,
//		 1.0f,  1.0f,  1.0f, 1.0f
//	};
//	float skyboxVertices[] = {
//		// positions          
//		-1.0f,  1.0f, -1.0f,
//		-1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		-1.0f,  1.0f, -1.0f,
//		 1.0f,  1.0f, -1.0f,
//		 1.0f,  1.0f,  1.0f,
//		 1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		 1.0f, -1.0f, -1.0f,
//		 1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		 1.0f, -1.0f,  1.0f
//	};
//
//	unsigned int VBO, VAO;
//	glGenBuffers(1, &VBO);
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//
//	unsigned int quadVAO, quadVBO;
//	glGenVertexArrays(1, &quadVAO);
//	glGenBuffers(1, &quadVBO);
//	glBindVertexArray(quadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//
//	unsigned int skyBoxVAO, skyBoxVBO;
//	glGenVertexArrays(1, &skyBoxVAO);
//	glGenBuffers(1, &skyBoxVBO);
//	glBindVertexArray(skyBoxVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//
//	texture frameBufferTexture(800, 600);
//
//	unsigned int framebuffer;
//	glGenFramebuffers(1, &framebuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTexture.id, 0);
//
//	unsigned int rbo;
//	glGenRenderbuffers(1, &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		cout << "ERROR::FRAMEBUFFER::framebuffer is not complete" << endl;
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_CULL_FACE);
//
//	vector<std::string> faces
//	{
//		"skybox/right.jpg",
//		"skybox/left.jpg",
//		"skybox/top.jpg",
//		"skybox/bottom.jpg",
//		"skybox/front.jpg",
//		"skybox/back.jpg"
//	};
//
//	unsigned int cubemap;
//	glGenTextures(1, &cubemap);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
//	int width, height, channels;
//	for (int i = 0; i < faces.size(); i++)
//	{
//		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
//		if (data)
//		{
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			stbi_image_free(data);
//		}
//		else
//		{
//			cout << "can not load cube map" << endl;
//			stbi_image_free(data);
//		}
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//
//
//	shader sd1("light1_vs.glsl", "light1_fs.glsl");
//	shader sd2("light1_vs.glsl", "light2_fs.glsl");
//	shader sdScreen("screen_vs.glsl", "screen_fs.glsl");
//	shader sdCube("skyBox_vs.glsl", "skyBox_fs.glsl");
//
//	sdScreen.use();
//	sdScreen.setInt("screenTexture", 2);
//	sdScreen.setInt("skybox", 3);
//
//	texture t1("container2.png");
//	texture t2("container2_specular.png");
//	sd1.use();
//
//
//	auto modelLoc = sd1.getUniformLocation("model");
//	auto viewLoc = sd1.getUniformLocation("view");
//	auto projectionLoc = sd1.getUniformLocation("projection");
//	auto viewPosLoc = sd1.getUniformLocation("viewPos");
//
//	sd1.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//	sd1.setFloat("material.shininess", 64.0f);
//	sd1.setInt("material.diffuse", 0);
//	sd1.setInt("material.specular", 1);
//	t1.active(GL_TEXTURE0);
//	t2.active(GL_TEXTURE1);
//
//	// directional light
//	sd1.setVec3("dLight.direction", -0.2f, -1.0f, -0.3f);
//	sd1.setVec3("dLight.ambient", 0.05f, 0.05f, 0.05f);
//	sd1.setVec3("dLight.diffuse", 0.4f, 0.4f, 0.4f);
//	sd1.setVec3("dLight.specular", 0.5f, 0.5f, 0.5f);
//	// point light 1
//	sd1.setVec3("pLight[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
//	sd1.setVec3("pLight[0].ambient", 0.05f, 0.05f, 0.05f);
//	sd1.setVec3("pLight[0].diffuse", 0.8f, 0.8f, 0.8f);
//	sd1.setVec3("pLight[0].specular", 1.0f, 1.0f, 1.0f);
//	sd1.setFloat("pLight[0].constant", 1.0f);
//	sd1.setFloat("pLight[0].linear", 0.09);
//	sd1.setFloat("pLight[0].quadratic", 0.032);
//	// point light 2
//	sd1.setVec3("pLight[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
//	sd1.setVec3("pLight[1].ambient", 0.05f, 0.05f, 0.05f);
//	sd1.setVec3("pLight[1].diffuse", 0.8f, 0.8f, 0.8f);
//	sd1.setVec3("pLight[1].specular", 1.0f, 1.0f, 1.0f);
//	sd1.setFloat("pLight[1].constant", 1.0f);
//	sd1.setFloat("pLight[1].linear", 0.09);
//	sd1.setFloat("pLight[1].quadratic", 0.032);
//	// point light 3
//	sd1.setVec3("pLight[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
//	sd1.setVec3("pLight[2].ambient", 0.05f, 0.05f, 0.05f);
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
//	
//
//	while (!glfwWindowShouldClose(window))
//	{
//		cam.deltaTime = glfwGetTime() - cam.lastFrame;
//		cam.lastFrame = glfwGetTime();
//
//		processInput(window);
//
//		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//		glEnable(GL_DEPTH_TEST);
//		glClearColor(0.2, 0.3, 0.3, 1.0);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//
//
//		sd2.use();
//		glBindVertexArray(VAO);
//		sd2.setMat4("view", cam.getViewMatrix());
//		sd2.setMat4("projection", cam.getProjectionMatrix());
//
//		for (int i = 0; i < 4; i++)
//		{
//			glm::mat4 model;
//			model = glm::translate(model, pointLightPositions[i]);
//			model = glm::scale(model, glm::vec3(0.2f));
//			sd2.setMat4("model", model);
//
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		std::map<float, glm::vec3> sorted;
//		for (unsigned int i = 0; i < 10; i++)
//		{
//			float distance = glm::length(cam.positon - cubePositions[i]);
//			sorted[distance] = cubePositions[i];
//		}
//
//		sd1.use();
//		glBindVertexArray(VAO);
//		sd1.setMat4(viewLoc, cam.getViewMatrix());
//		sd1.setMat4(projectionLoc, cam.getProjectionMatrix());
//		sd1.setVec3(viewPosLoc, cam.positon.x, cam.positon.y, cam.positon.z);
//		int i = 0;
//		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++, i++)
//		{
//			glm::mat4 model;
//			model = glm::translate(model, it->second);
//			model = glm::rotate(model, ((float)glfwGetTime() + i) * glm::radians(50.0f + i * 5), glm::vec3(0.5f, 1.0f, 0.3f));
//
//			sd1.setMat4(modelLoc, model);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//		glBindVertexArray(0);
//
//		glDepthFunc(GL_LEQUAL);
//		sdCube.use();
//		glm::mat4 view = glm::mat4(glm::mat3(cam.getViewMatrix()));
//		sdCube.setMat4("view", view);
//		sdCube.setMat4("projection", cam.getProjectionMatrix());
//		glActiveTexture(GL_TEXTURE3);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
//
//		glBindVertexArray(skyBoxVAO);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//		glDepthFunc(GL_LESS);
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glDisable(GL_DEPTH_TEST);
//
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		sdScreen.use();
//		glBindVertexArray(quadVAO);
//		frameBufferTexture.active(GL_TEXTURE2);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//
//	}
//	glfwTerminate();
//	return 0;
//}