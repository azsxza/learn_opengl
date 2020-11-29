#include"helper.h"
#include<fstream>
#include "stb_image.h";

string helper::getShaderSource(string shaderName)
{
	ifstream shaderFile(shaderName);
	string source = "";
	string tmp;
	while (getline(shaderFile, tmp))
	{
		source += tmp + '\n';
	}
	shaderFile.close();
	source += '\0';
	return source;
}

void helper::updateCameraVectors(glm::vec3& front, glm::vec3& right, glm::vec3& up, glm::vec3& wordUp, float yaw, float pitch)
{
	front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, wordUp));
	up = glm::normalize(glm::cross(right, front));
}

void helper::updateCameraVectorsCam(camera& cam, float yaw, float pitch)
{
	updateCameraVectors(cam.front, cam.right, cam.up, cam.wordUp, yaw, pitch);
}

unsigned int helper::getShader(const char* shaderSource, unsigned int shaderClass)
{
	unsigned int shader = glCreateShader(shaderClass);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "+ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

unsigned int helper::getShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

unsigned int helper::getShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader)
{
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, geometryShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}



shader::shader(string vertexShaderFile, string fragmentShaderFile, string geometryShaderFile)
{
	vertexShaderSourceString = hp.getShaderSource(vertexShaderFile);
	fragmentShaderSourceString = hp.getShaderSource(fragmentShaderFile);
	vertexShaderSource = vertexShaderSourceString.c_str();
	fragmentShaderSource = fragmentShaderSourceString.c_str();
	unsigned int vertexShader = hp.getShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = hp.getShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	if (geometryShaderFile != "")
	{
		hasGeometryShader = true;
		geometryShaderSourceString = hp.getShaderSource(geometryShaderFile);
		geometryShaderSource = geometryShaderSourceString.c_str();
		unsigned int geometryShader = hp.getShader(geometryShaderSource, GL_GEOMETRY_SHADER);
		shaderProgram = hp.getShaderProgram(vertexShader, fragmentShader, geometryShader);
	}
	else
		shaderProgram = hp.getShaderProgram(vertexShader, fragmentShader);
}

void shader::use()
{
	glUseProgram(shaderProgram);
}

void shader::setBool(const string& name, bool v)
{
	setInt(name, v);
}

void shader::setInt(const string& name, int v)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), v);
}

void shader::setFloat(const string& name, float v)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), v);
}

void shader::setVec2(const string& name, float v1, float v2)
{
	glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), v1, v2);
}

void shader::setVec2(const string& name, float v)
{
	glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), v, v);
}

void shader::setVec2(const string& name, glm::vec2 v)
{
	glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), v.x, v.y);
}

void shader::setVec3(const string& name, float v1, float v2, float v3)
{
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), v1, v2, v3);
}

void shader::setVec3(const string& name, float v)
{
	setVec3(name, v, v, v);
}

void shader::setVec3(const string& name, glm::vec3 v)
{
	setVec3(name, v.x, v.y, v.z);
}

void shader::setVec4(const string& name, float v1, float v2, float v3, float v4)
{
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), v1, v2, v3, v4);
}

void shader::setVec4(const string& name, float v)
{
	setVec4(name, v, v, v, v);
}

void shader::setVec4(const string& name, glm::vec4 v)
{
	setVec4(name, v.x, v.y, v.z, v.w);
}

void shader::setMat4(const string& name, glm::mat4 v)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(v));
}

void shader::setInt(int loc, int v)
{
	glUniform1i(loc, v);
}

void shader::setFloat(int loc, float v)
{
	glUniform1f(loc, v);
}

void shader::setVec2(int loc, float v1, float v2)
{
	glUniform2f(loc, v1, v2);
}

void shader::setVec2(int loc, float v)
{
	glUniform2f(loc, v, v);
}

void shader::setVec2(int loc, glm::vec2 v)
{
	glUniform2f(loc, v.x, v.y);
}

void shader::setVec3(int loc, float v1, float v2, float v3)
{
	glUniform3f(loc, v1, v2, v3);
}

void shader::setVec3(int loc, float v)
{
	setVec3(loc, v, v, v);
}

void shader::setVec3(int loc, glm::vec3 v)
{
	setVec3(loc, v.x, v.y, v.z);
}

void shader::setVec4(int loc, float v1, float v2, float v3, float v4)
{
	glUniform4f(loc, v1, v2, v3, v4);
}

void shader::setVec4(int loc, float v)
{
	setVec4(loc, v, v, v, v);
}

void shader::setVec4(int loc, glm::vec4 v)
{
	setVec4(loc, v.x, v.y, v.z, v.w);
}

void shader::setMat4(int loc, glm::mat4 v)
{
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(v));
}

int shader::getUniformLocation(const string& name)
{
	return glGetUniformLocation(shaderProgram, name.c_str());
}

texture::texture(int width, int height, unsigned int format, unsigned int type)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

texture::texture(string imagePath,string type, unsigned int format, bool vertical, bool filp)
{
	this->type = type;
	stbi_set_flip_vertically_on_load(vertical);
	
	unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
	if (!data)
	{
		cout << "can not load image:" << imagePath << endl;
		return;
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (!format)
	{
		if (channels == 3)
			format = GL_RGB;
		if (channels == 4)
			format = GL_RGBA;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

void texture::active(unsigned int index)
{
	glActiveTexture(index);
	glBindTexture(GL_TEXTURE_2D, id);
}

camera::camera(glm::vec3 position_, glm::vec3 wordUp_, float yaw_, float pitch_, float mouseSensitivity_, float moveSpeed_, float sWidth_, float sHeight_, float zFar_, float zNear_)
{
	positon = position_;
	wordUp = wordUp_;
	mouseSensitivity = mouseSensitivity_;
	moveSpeed = moveSpeed_;
	sHeight = sHeight_;
	sWidth = sWidth_;
	aspect = sWidth / sHeight;
	zFar = zFar_;
	zNear = zNear_;

	yaw = yaw_;
	pitch = pitch_;

	hp.updateCameraVectors(front, right, up, wordUp, yaw, pitch);
}
camera::camera()
{
	hp.updateCameraVectors(front, right, up, wordUp, yaw, pitch);
}

void camera::mouseMove(float xpos, float ypos, bool contrainPitch)
{
	if (!rightMouseDown)
		return;
	if (isFirst)
	{
		lastX = xpos;
		lastY = ypos;
		isFirst = false;
	}
	yaw += (xpos - lastX)*mouseSensitivity;
	pitch += (lastY - ypos)*mouseSensitivity;
	lastX = xpos;
	lastY = ypos;

	if (contrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		else if (pitch < -89.0f)
			pitch = -89.0f;
	}
	hp.updateCameraVectorsCam(*this, yaw, pitch);
	
}

void camera::keyDown(cameraMovement key)
{
	if (key == FORWARD)
		positon += moveSpeed * deltaTime * front;
	else if (key == BACKWARD)
		positon -= moveSpeed * deltaTime * front;
	else if (key == RIGHT)
		positon += moveSpeed * deltaTime * right;
	else if (key == LEFT)
		positon -= moveSpeed * deltaTime * right;
}

void camera::mouseScroll(float yoffset)
{
	fov -= yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	else if (fov > 45.0f)
		fov = 45.0f;
}

void camera::updateWH(float width, float height)
{
	sWidth = width;
	sHeight = height;
	aspect = sWidth / sHeight;
}

glm::mat4 camera::getViewMatrix()
{
	return glm::lookAt(positon, positon + front, up);
}

glm::mat4 camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(fov), aspect, zNear, zFar);
}

mesh::mesh(vector<vertex> vertices, vector<unsigned int> indices, vector<texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	setupMesh();
}

void mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texCoords));

	glBindVertexArray(0);
}


void mesh::draw(shader& sd)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int reflectionNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
		// 获取纹理序号（diffuse_textureN 中的 N）
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else if (name == "texture_reflection")
			number = std::to_string(reflectionNr++);

		sd.setInt("material." + name + number, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// 绘制网格
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

model::model(string path)
{
	loadModel(path);
}

void model::draw(shader& sd)
{
	for (auto i : meshes)
		i.draw(sd);
}

void model::loadModel(string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void model::processNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

mesh model::processMesh(aiMesh* mMesh, const aiScene* scene)
{
	vector<vertex> vertices;
	vector<unsigned int> indices;
	vector<texture> textures;

	for (int i = 0; i < mMesh->mNumVertices; i++)
	{
		vertex verTex;
		verTex.position.x = mMesh->mVertices[i].x;
		verTex.position.y = mMesh->mVertices[i].y;
		verTex.position.z = mMesh->mVertices[i].z;

		verTex.normal.x = mMesh->mNormals[i].x;
		verTex.normal.y = mMesh->mNormals[i].y;
		verTex.normal.z = mMesh->mNormals[i].z;

		if (mMesh->mTextureCoords[0])
		{
			verTex.texCoords.x = mMesh->mTextureCoords[0][i].x;
			verTex.texCoords.y = mMesh->mTextureCoords[0][i].y;
		}
		else
			verTex.texCoords = glm::vec2(0, 0);

		vertices.push_back(verTex);
	}

	for (int i = 0; i < mMesh->mNumFaces; i++)
	{
		aiFace face = mMesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mMesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mMesh->mMaterialIndex];
		vector<texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		vector<texture> reflectionMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_reflection");
		textures.insert(textures.end(), reflectionMaps.begin(), reflectionMaps.end());
	}
	return mesh(vertices, indices, textures);
}

vector<texture> model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<texture> textures;
	for (int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (auto j : textures_loaded)
		{
			if (j.path == str.C_Str())
			{
				textures.push_back(j);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			texture texTure(directory + '/' + str.C_Str());
			texTure.type = typeName;
			texTure.path = str.C_Str();
			textures.push_back(texTure);
			textures_loaded.push_back(texTure);
		}
	}
	return textures;
}