#pragma once
#include <future>
#include <mutex>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "stb_image/stb_image.h"
#include "Qubit/Platform/Renderer/Utility/Shader.h"
#include "Qubit/Platform/Renderer/Utility/Texture.h"

namespace Qubit {
	struct Vertex { 
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	struct ModelTexture {
		unsigned int ID;
		int width, height, nrChannels;
		unsigned char* data;
		std::string type;
		std::string path;
	};

	struct Material {
		glm::vec4 color;
	};

	struct ModelInstance {
		glm::mat4 transformation;
		glm::vec4 color;
		std::string name;
	};

	class Entity {
	public:
		Entity() = default;
		Entity(std::string& path, std::string& name);
		Entity(std::vector<Vertex>& vertices, std::vector<unsigned int> indices, std::vector<std::string> textureKeys, std::string& name);
		Entity(Entity& model);

		void Initialize();
		void CreateNewModelInstance();
		void Draw(Shader& shader);
		~Entity() = default;
		
		virtual void ChangeColor(glm::vec4 color);
		virtual void ChangeMaterial(Material material);
		virtual void Translate(glm::vec3 translation);
		virtual void RotateDeg(float degrees);
		virtual void RotateRad(float radians);

		static std::unordered_map<std::string, Entity> s_ModelAtlas;
		static std::deque<std::shared_ptr<Entity>> s_Callbacks;
		std::vector<std::shared_ptr<ModelInstance>> m_ModelInstances;
		std::unordered_map<std::string, std::shared_ptr<ModelInstance>> m_ModelInstanceAtlas;

		std::string m_Name, m_TypeName;
	private:
		std::string directory, m_Path;
		const aiScene* m_Scene;
		bool loadFinished, initGL, initTex;
		unsigned int VAO = 0, VBOVertex = 0, VBOInstance = 0, EBO = 0, loadedTextures = 0, totalTextures = 0;
		Shader* m_Shader;

		//-------------------------------------- VAO Data
		std::vector<Vertex> m_Vertices; //VBO data
		std::vector<unsigned int> m_Indices; //EBO data
		std::vector<Texture> m_Textures;
		//-------------------------------------- VAO Data

		void LoadModel();
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);
		void loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

		//Async stuff
		void textureDataLoad(ModelTexture texture, std::string filepath);

		std::future<void> m_Future;
		std::vector<std::future<unsigned char*>> m_TextureFuture;
		std::vector<std::future<void>> m_FutureVoids;
		std::mutex mute;
	};
}