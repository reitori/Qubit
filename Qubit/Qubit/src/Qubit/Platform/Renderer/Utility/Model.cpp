#include <QubitPCH.h>
#include "Model.h"

namespace Qubit {
	Entity::Entity(std::string& path, std::string& name) : m_Path(path), m_Name(name) {
		loadFinished = false;
		initGL = false;
		initTex = false;
		m_Scene = NULL;
		m_FutureVoids.push_back(std::async(std::launch::async, &ModelType::LoadModel, this));
		//m_FutureVoids.push_back(std::async(std::launch::async, &ModelType::loadModelTextures, this));

		std::string modelName = m_Name + '1';
		ModelInstance instance = { glm::mat4(1.0f), glm::vec4(1.0f), modelName };
		m_ModelInstances.push_back(instance);
	}

	void Entity::LoadModel() {
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(m_Path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
		m_Vertices.reserve(scene->mNumMeshes);
		m_Indices.reserve(scene->mNumMeshes);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
			std::string str = "ASSIMP:\n";
			str += import.GetErrorString() + '\n';
			Qubit::Log::printError(str.c_str(), Qubit::Log::getCoreLogger());
			return;
		}
		
		directory = m_Path.substr(0, m_Path.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
		loadFinished = true;
		initGL = true;
	}

	void Entity::ProcessNode(aiNode* node, const aiScene* scene) {
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh, scene);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			ProcessNode(node->mChildren[i], scene);
		}
	}

	void Entity::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vert;
			vert.pos.x = mesh->mVertices[i].x;
			vert.pos.y = mesh->mVertices[i].y;
			vert.pos.z = mesh->mVertices[i].z;

			if (mesh->mTextureCoords[0]) {
				vert.texCoords.x = mesh->mTextureCoords[0][i].x;
				vert.texCoords.y = mesh->mTextureCoords[0][i].y;
			}
			else
				vert.texCoords = glm::vec2(0.0f, 0.0f);

			if (mesh->HasNormals()) {
				vert.normal.x = mesh->mNormals[i].x;
				vert.normal.y = mesh->mNormals[i].y;
				vert.normal.z = mesh->mNormals[i].z;
			}
			
			m_Vertices.push_back(vert);
		}

		unsigned int offset = m_Indices.size();
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				m_Indices.push_back(face.mIndices[j] + offset);
			}
		}

		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
			loadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
			loadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular");
			loadMaterialTextures(mat, aiTextureType_HEIGHT, "texture_normal");
		}

	}

	void Entity::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			if (Texture::s_TextureAtlas.find(str.C_Str()) != Texture::s_TextureAtlas.end())
				break;

			else{
				// if texture hasn't been loaded already, load it
				std::string filepath = directory + '/' + str.C_Str();
				std::string textureName = std::string(m_Name + '_' + typeName);
				Texture texture(Qubit::texturelaunch::onthreadcallback, filepath, typeName, textureName);
			}
		}
	}

	void Entity::Initialize() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBOVertex);
		glGenBuffers(1, &VBOInstance);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBOVertex);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));


		glBindBuffer(GL_ARRAY_BUFFER, VBOInstance);
		glBufferData(GL_ARRAY_BUFFER, m_ModelInstances.size() * sizeof(ModelInstance), &m_ModelInstances[0], GL_STATIC_DRAW);

		std::size_t glmVec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(ModelInstance), (GLvoid*)offsetof(ModelInstance, color));

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(ModelInstance), (GLvoid*)(0));

		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(ModelInstance), (GLvoid*)(1 * glmVec4Size));

		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(ModelInstance), (GLvoid*)(2 * glmVec4Size));

		glEnableVertexAttribArray(7);
		glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(ModelInstance), (GLvoid*)(3 * glmVec4Size));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glVertexAttribDivisor(7, 1);

		glBindVertexArray(0);
	
		
	}

	void Entity::Draw(Shader& shader) {
			unsigned int diffuseCount = 1;
			unsigned int specularCount = 1;
			unsigned int normalCount = 1;

			std::string name;
			for (int i = 0; i < m_Textures.size(); i++) {
				if (m_Textures[i].GetType() == "texture_diffuse")
					name = m_Textures[i].GetType() + std::to_string(diffuseCount++);
				else if (m_Textures[i].GetType() == "texture_specular")
					name = m_Textures[i].GetType() + std::to_string(specularCount++);
				else if (m_Textures[i].GetType() == "texture_normal")
					name = m_Textures[i].GetType() + std::to_string(normalCount++);

				std::string str = "material." + name;
				m_Textures[i].EnableTexture(shader, str, i);
			}

			glBindVertexArray(VAO);
			glDrawElementsInstanced(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0, m_ModelInstances.size());
			glBindVertexArray(0);

			glActiveTexture(GL_TEXTURE0);
		}
		
	void Entity::CreateNewModelInstance() {

	}
}