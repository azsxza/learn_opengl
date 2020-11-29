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
//	glfwWindowHint(GLFW_SAMPLES, 4);
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
//	model rock("rock/rock.obj");
//	model mPlanet("planet/planet.obj");
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
//	shader sd1("model1_vs.glsl", "model1_fs.glsl");
//	shader sd2("instance2_vs.glsl", "instance2_fs.glsl");
//	shader sdScreen("screen_vs.glsl", "screen_fs.glsl");
//	shader sdCube("skyBox_vs.glsl", "skyBox_fs.glsl");
//
//	unsigned int amount = 10000;
//	glm::mat4* modelMatrices;
//	modelMatrices = new glm::mat4[amount];
//	srand(glfwGetTime()); // initialize random seed	
//	float radius = 150.0;
//	float offset = 20.0f;
//	for (unsigned int i = 0; i < amount; i++)
//	{
//		glm::mat4 model = glm::mat4(1.0f);
//		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
//		float angle = (float)i / (float)amount * 360.0f;
//		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float x = sin(angle) * radius + displacement;
//		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
//		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float z = cos(angle) * radius + displacement;
//		model = glm::translate(model, glm::vec3(x, y, z));
//
//		// 2. scale: Scale between 0.05 and 0.25f
//		float scale = (rand() % 20) / 100.0f + 0.05;
//		model = glm::scale(model, glm::vec3(scale));
//
//		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
//		float rotAngle = (rand() % 360);
//		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
//
//		// 4. now add to list of matrices
//		modelMatrices[i] = model;
//	}
//
//	// configure instanced array
//	// -------------------------
//	unsigned int buffer;
//	glGenBuffers(1, &buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, buffer);
//	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
//
//	// set transformation matrices as an instance vertex attribute (with divisor 1)
//	// note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
//	// normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
//	// -----------------------------------------------------------------------------------------------------------------------------------
//	for (unsigned int i = 0; i < rock.meshes.size(); i++)
//	{
//		unsigned int VAO = rock.meshes[i].VAO;
//		glBindVertexArray(VAO);
//		// set attribute pointers for matrix (4 times vec4)
//		glEnableVertexAttribArray(3);
//		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
//		glEnableVertexAttribArray(4);
//		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
//		glEnableVertexAttribArray(5);
//		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
//		glEnableVertexAttribArray(6);
//		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
//
//		glVertexAttribDivisor(3, 1);
//		glVertexAttribDivisor(4, 1);
//		glVertexAttribDivisor(5, 1);
//		glVertexAttribDivisor(6, 1);
//
//		glBindVertexArray(0);
//	}
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
//	glEnable(GL_MULTISAMPLE);
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
//	
//	sdScreen.use();
//	sdScreen.setInt("screenTexture", 4);
//
//	sd1.use();
//	sd1.setInt("skybox", 3);
//
//	auto modelLoc = sd1.getUniformLocation("model");
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
//	sd2.use();
//	sd2.setInt("skybox", 3);
//
//	auto viewPosLoc1 = sd2.getUniformLocation("viewPos");
//
//	sd2.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//	sd2.setFloat("material.shininess", 64.0f);
//	// directional light
//	sd2.setVec3("dLight.direction", -0.2f, -1.0f, -0.3f);
//	sd2.setVec3("dLight.ambient", 0.05f, 0.05f, 0.05f);
//	sd2.setVec3("dLight.diffuse", 0.4f, 0.4f, 0.4f);
//	sd2.setVec3("dLight.specular", 0.5f, 0.5f, 0.5f);
//	// point light 1
//	sd2.setVec3("pLight[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
//	sd2.setVec3("pLight[0].ambient", 0.5f, 0.5f, 0.5f);
//	sd2.setVec3("pLight[0].diffuse", 0.8f, 0.8f, 0.8f);
//	sd2.setVec3("pLight[0].specular", 1.0f, 1.0f, 1.0f);
//	sd2.setFloat("pLight[0].constant", 1.0f);
//	sd2.setFloat("pLight[0].linear", 0.09);
//	sd2.setFloat("pLight[0].quadratic", 0.032);
//	// point light 2
//	sd2.setVec3("pLight[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
//	sd2.setVec3("pLight[1].ambient", 0.05f, 0.05f, 0.05f);
//	sd2.setVec3("pLight[1].diffuse", 0.8f, 0.8f, 0.8f);
//	sd2.setVec3("pLight[1].specular", 1.0f, 1.0f, 1.0f);
//	sd2.setFloat("pLight[1].constant", 1.0f);
//	sd2.setFloat("pLight[1].linear", 0.09);
//	sd2.setFloat("pLight[1].quadratic", 0.032);
//	// point light 3
//	sd2.setVec3("pLight[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
//	sd2.setVec3("pLight[2].ambient", 0.05f, 0.05f, 0.05f);
//	sd2.setVec3("pLight[2].diffuse", 0.8f, 0.8f, 0.8f);
//	sd2.setVec3("pLight[2].specular", 1.0f, 1.0f, 1.0f);
//	sd2.setFloat("pLight[2].constant", 1.0f);
//	sd2.setFloat("pLight[2].linear", 0.09);
//	sd2.setFloat("pLight[2].quadratic", 0.032);
//	// point light 4
//	sd2.setVec3("pLight[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
//	sd2.setVec3("pLight[3].ambient", 0.05f, 0.05f, 0.05f);
//	sd2.setVec3("pLight[3].diffuse", 0.8f, 0.8f, 0.8f);
//	sd2.setVec3("pLight[3].specular", 1.0f, 1.0f, 1.0f);
//	sd2.setFloat("pLight[3].constant", 1.0f);
//	sd2.setFloat("pLight[3].linear", 0.09);
//	sd2.setFloat("pLight[3].quadratic", 0.032);
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
//		sd1.use();
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
//		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
//		sd1.setMat4(modelLoc, model);
//		mPlanet.draw(sd1);
//
//		sd2.use();
//		sd2.setMat4("projection", cam.getProjectionMatrix());
//		sd2.setMat4("view", cam.getViewMatrix());
//		sd2.setInt("texture_diffuse1", 0);
//		sd2.setVec3(viewPosLoc1, cam.positon);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
//		for (unsigned int i = 0; i < rock.meshes.size(); i++)
//		{
//			glBindVertexArray(rock.meshes[i].VAO);
//			glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
//			glBindVertexArray(0);
//		}
//
//
//
//
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