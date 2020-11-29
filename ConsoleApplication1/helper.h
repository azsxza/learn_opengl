#pragma once
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
using namespace std;

class camera;

class helper
{
public:
	char infoLog[512];
	int success;

	string getShaderSource(string shaderName);
	unsigned int getShader(const char* shaderSource, unsigned int shaderClass);
	unsigned int getShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
	unsigned int getShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader);

	void updateCameraVectors(glm::vec3& front, glm::vec3& right, glm::vec3& up, glm::vec3& wordUp, float yaw, float pitch);
	void updateCameraVectorsCam(camera& cam, float yaw, float pitch);
};

class shader
{
public:
	helper hp;
	unsigned int shaderProgram;

	bool hasGeometryShader = false;
	string vertexShaderSourceString;
	string fragmentShaderSourceString;
	string geometryShaderSourceString;
	const char* vertexShaderSource;
	const char* fragmentShaderSource;
	const char* geometryShaderSource;

	shader(string vertexShaderFile, string fragmentShaderFile, string geometryShaderFile = "");
	void use();

	void setBool(const string& name, bool v);
	void setInt(const string& name, int v);
	void setInt(int loc, int v);
	void setFloat(const string& name, float v);
	void setFloat(int loc, float v);
	void setVec2(const string& name, float v1, float v2);
	void setVec2(const string& name, float v);
	void setVec2(const string& name, glm::vec2 v);
	void setVec2(int loc, float v1, float v2);
	void setVec2(int loc, float v);
	void setVec2(int loc, glm::vec2 v);
	void setVec3(const string& name, float v1, float v2, float v3);
	void setVec3(const string& name, float v);
	void setVec3(const string& name, glm::vec3 v);
	void setVec3(int loc, float v1, float v2, float v3);
	void setVec3(int loc, float v);
	void setVec3(int loc, glm::vec3 v);
	void setVec4(const string& name, float v1, float v2, float v3, float v4);
	void setVec4(const string& name, float v);
	void setVec4(const string& name, glm::vec4 v);
	void setVec4(int loc, float v1, float v2, float v3, float v4);
	void setVec4(int loc, float v);
	void setVec4(int loc, glm::vec4 v);
	void setMat4(const string& name, glm::mat4 v);
	void setMat4(int loc, glm::mat4 v);
	
	int getUniformLocation(const string& name);
};
class texture
{
public:
	unsigned int id;
	int width;
	int height;
	int channels;
	string type;

	string path;
	texture(int width, int height,unsigned int format=GL_RGB,unsigned int type = GL_UNSIGNED_INT);
	texture(string imagePath, string type = "None", unsigned int format = 0, bool filp = false, bool vertical = false);
	void active(unsigned int index);
};

enum cameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class camera
{
public:
	helper hp;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX;
	float lastY;
	bool isFirst = true;
	float mouseSensitivity = 0.5f;
	float moveSpeed = 2.5f;
	bool rightMouseDown = false;
	float deltaTime = 0.0f; // 当前帧与上一帧的时间差
	float lastFrame = 0.0f; // 上一帧的时间
	float fov=45.0f;

	float sWidth = 800.0f;
	float sHeight = 600.0f;
	float aspect = sWidth / sHeight;
	float zNear = 0.1f;
	float zFar = 10000.0f;

	glm::vec3 positon = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 wordUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::normalize(glm::cross(front, up));

	camera(glm::vec3 position_, glm::vec3 wordUp_, float yaw_, float pitch_, float mouseSensitivity_, float moveSpeed_, float sWidth_, float sHeight_, float zFar_, float zNear_);
	camera();
	void updateWH(float width, float height);
	void mouseMove(float xpos, float ypos, bool contrainPitch = true);
	void keyDown(cameraMovement key);
	void mouseScroll(float yoffset);


	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};

struct vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class mesh
{
public:
	unsigned int VAO, VBO, EBO;
	vector<vertex> vertices;
	vector<unsigned int> indices;
	vector<texture> textures;

	mesh(vector<vertex> vertices, vector<unsigned int> indices, vector<texture> textures);
	
	void setupMesh();
	void draw(shader& sd);
};

class model
{
public:
	vector<mesh> meshes;
	string directory;
	vector<texture> textures_loaded;

	model(string path);
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

	void draw(shader& sd);

};

struct character
{
	GLuint     TextureID;  // 字形纹理的ID
	glm::ivec2 Size;       // 字形大小
	glm::ivec2 Bearing;    // 从基准线到字形左部/顶部的偏移值
	GLuint     Advance;    // 原点距下一个字形原点的距离
};