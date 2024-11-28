#pragma once
#include "Qubit/Platform/Renderer/Utility/Shader.h"
//#include "Utility/Model.h"
#include "Qubit/Platform/Renderer/Utility/Texture.h"
#include "Qubit/Platform/Renderer/Utility/Framebuffer.h"
#include "Qubit/Platform/Renderer/Utility/Camera.h"
#include "Qubit/Events/Event.h"
#include "Qubit/Events/ApplicationEvent.h"


namespace Qubit {
	class Renderer {
	public:
		Renderer();
		~Renderer();

		void Render();
		void PreRender(FramebufferSpecification& spec);
		void PreRender(FramebufferSpecification&& spec);

		void loadFramebuffer();
	//	void LoadModel(Model* model);
		void LoadScene(/*Scene* scene*/);
		//void LoadTexture(Texture2D* texture);
		//void CreateSkyBox(Texture2D* texture);

		void SetShader(Shader& shader, Camera& cam);
		void UseShader();
		void EnableLighting();
		void DisableLighting();
		void SetPerspective(float* zoom, uint16_t aspectWidth, uint16_t aspectHeight, float nearPlane, float farPlane);
		void SetOrthographic(float width, float height, float nearPlane, float farPlane);

		std::shared_ptr<Framebuffer>& GetFrameBuffer();
		void SetFramebuffer(FramebufferSpecification& spec);
		void SetFramebuffer(FramebufferSpecification&& spec);

		void OnEvent(event& e);

		//Renderer stuff
		//I wroote this code on like 3 hours of sleep so no judge
		static std::unordered_map<uint8_t, std::string> s_UniformLocations;
		glm::vec4 BackgroundColor;
		std::unique_ptr<Camera> m_Cam;
		unsigned int width, height;
	private:
		void LoadCallbacks();

		std::shared_ptr<Framebuffer> m_Framebuffer;
		std::unique_ptr<Shader> m_Shader;
		uint8_t m_TextureCount;

		glm::mat4 projection;
		bool lightingEnabled;
		//std::vector<Model*> m_Models;
		//Scene* scene;
	};
}