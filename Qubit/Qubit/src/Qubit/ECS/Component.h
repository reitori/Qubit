#pragma once
#include <bitset>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Qubit/Platform/Renderer/Utility/Texture.h"

#define QBT_MAX_COMPONENTS 32
#define QBT_STD_COMPONENTS 8

namespace Qubit {
	struct Vertex {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

				


		/*Inherit from Component to define component type. Pass it through Manager::CreateNewComponentType() to instantiate it.
		
		Example:
			struct foo : public Component{
				int data;
			}

			Manager::CreateNewComponentType(foo);
		*/

		struct QBT_API Component {
			virtual ~Component() {};
		};

		struct QBT_API Transform : public Component {
			glm::vec3 pos;
			glm::quat rotation;
			glm::vec3 scale;
		};

		struct QBT_API Lighting : public Component {
			glm::vec3 normal;
			glm::vec3 tangent;
			glm::vec3 bitangent;
		};

		//Links an entity to a parent entity
		struct QBT_API Link : public Component {
		
		};

		//Contains batched Mesh data
		struct QBT_API EntityData : public Component {
			std::vector<Vertex> vertices;
			std::vector<uint16_t> indices;
			std::vector<Texture> textures;
			glm::vec4 color;
		};

		//Contains all of the meshes
		struct QBT_API Meshes : public Component {
			
		};

		struct QBT_API TextureComponent : public Component {

		};

		struct QBT_API Graphics : public Component {

		};

		struct QBT_API CameraComponent : public Component {

		};
	
}