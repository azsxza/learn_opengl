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
//	texture frameBufferTexture(sWidth, sHeight);
//
//	unsigned int framebuffer;
//	glGenFramebuffers(1, &framebuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTexture.id, 0);
//
//	unsigned int rbo;
//	glGenRenderbuffers(1, &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, sWidth, sHeight);
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
//	//glEnable(GL_PROGRAM_POINT_SIZE);
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
//	stbi_set_flip_vertically_on_load(true);
//	model mModel("./nanosuit_reflection/nanosuit.obj");
//
//	shader sd1("model2_vs.glsl", "model2_fs.glsl", "model1_gs.glsl");
//	shader sdScreen("screen_vs.glsl", "screen_fs.glsl");
//	shader sdCube("skyBox_vs.glsl", "skyBox_fs.glsl");
//
//	sdScreen.use();
//	sdScreen.setInt("screenTexture", 4);
//	
//
//	sd1.use();
//	sd1.setInt("skybox", 3);
//
//	auto modelLoc = sd1.getUniformLocation("model");
//	auto viewLoc = sd1.getUniformLocation("view");
//	auto projectionLoc = sd1.getUniformLocation("projection");
//	auto viewPosLoc = sd1.getUniformLocation("viewPos");
//
//	sd1.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//	sd1.setFloat("material.shininess", 64.0f);
//
//
//	// directional light
//	sd1.setVec3("dLight.direction", -0.2f, -1.0f, -0.3f);
//	sd1.setVec3("dLight.ambient", 0.05f, 0.05f, 0.05f);
//	sd1.setVec3("dLight.diffuse", 0.4f, 0.4f, 0.4f);
//	sd1.setVec3("dLight.specular", 0.5f, 0.5f, 0.5f);
//	// point light 1
//	sd1.setVec3("pLight[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
//	sd1.setVec3("pLight[0].ambient", 0.5f, 0.5f, 0.5f);
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
//	unsigned int uniformBlock = glGetUniformBlockIndex(sd1.shaderProgram, "Matrices");
//	glUniformBlockBinding(sd1.shaderProgram, uniformBlock, 0);
//
//	unsigned int uboMatrices;
//	glGenBuffers(1, &uboMatrices);
//	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
//	glBindBuffer(GL_UNIFORM_BUFFER, 0);
//	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
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
//		sd1.use();
//		sd1.setVec3(viewPosLoc, cam.positon);
//
//		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(cam.getViewMatrix()));
//		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(cam.getProjectionMatrix()));
//		glBindBuffer(GL_UNIFORM_BUFFER, 0);
//
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
//		sd1.setMat4("model", model);
//		sd1.setFloat("time", glfwGetTime());
//		mModel.draw(sd1);
//		glBindVertexArray(0);
//
//		//skybox
//		glDepthFunc(GL_LEQUAL);
//		sdCube.use();
//		glm::mat4 view = glm::mat4(glm::mat3(cam.getViewMatrix()));
//		sdCube.setMat4("view", view);
//		sdCube.setMat4("projection", cam.getProjectionMatrix());
//		glActiveTexture(GL_TEXTURE3);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
//
//		glBindVertexArray(skyBoxVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//		glDepthFunc(GL_LESS);
//		
//		//framebuffer
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glDisable(GL_DEPTH_TEST);
//
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		sdScreen.use();
//		glBindVertexArray(quadVAO);
//		frameBufferTexture.active(GL_TEXTURE4);
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