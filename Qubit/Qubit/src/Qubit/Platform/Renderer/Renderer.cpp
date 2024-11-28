#include <QubitPCH.h>
#include "Qubit/Platform/Renderer/Renderer.h"
#include <iostream>

namespace Qubit {

	std::unordered_map<uint8_t, std::string> Renderer::s_UniformLocations;

	Renderer::~Renderer() {
		
	}

	void Renderer::EnableLighting() {
		m_Shader = std::unique_ptr<Shader>(new Shader("../Shaders/VertexLighting.glsl", "../Shaders/FragmentLighting.glsl"));
		lightingEnabled = true;
	}

	void Renderer::DisableLighting() {
		m_Shader = std::unique_ptr<Shader>(new Shader("../Shaders/VertexNormal.glsl", "../Shaders/FragmentNormal.glsl"));
	}

	void Renderer::SetShader(Shader& shader, Camera& cam) {

	}

	void Renderer::UseShader() {
		m_Shader->UseProgram();
		
	}

	void Renderer::LoadCallbacks() {
		std::lock_guard<std::mutex> lock(Texture::s_Mute);
		while (!Texture::s_Callbacks.empty()) {
			Texture::s_Callbacks.front()->Initialize();
			Texture::s_Callbacks.pop_front();
		}

		//while (!ModelType::s_Callbacks.empty()) {
		//	ModelType::s_Callbacks.front()->Initialize();
		//	ModelType::s_Callbacks.pop_front();
		//}
	}

	void Renderer::Render(){
		LoadCallbacks();
		m_Framebuffer->Bind();

		glClearColor(BackgroundColor.x, BackgroundColor.y, BackgroundColor.z, BackgroundColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		


		//m_Shader->useProgram();
		//Scene->Draw();
		//for (int i = 0; i < m_Models.size(); i++) {
		//	m_Models[i]->Draw(*m_Shader);
		//}


		m_Framebuffer->UnBind();
	}

	void Renderer::PreRender(FramebufferSpecification& spec) {
		if (spec.width == width && spec.height == height) {
			return;
		}
		else {
			m_Framebuffer->ResetFramebuffer(spec);
			width = spec.width;
			height = spec.height;
		}
	}

	void Renderer::PreRender(FramebufferSpecification&& spec) {
		if (spec.width == width && spec.height == height) {
			return;
		}
		else {
			m_Framebuffer->ResetFramebuffer(spec);
			width = spec.width;
			height = spec.height;
		}
	}

	void Renderer::LoadScene(/*Scene* scene*/) {

	}

	//void Renderer::CreateSkyBox(Texture2D* texture) {
	//
	//}

	Renderer::Renderer() {
		BackgroundColor.x = 0.0f;
		BackgroundColor.y = 0.0f;
		BackgroundColor.z = 0.0f;
		BackgroundColor.w = 1.0f;

		m_Cam = std::unique_ptr<Camera>(new Camera(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, -1.0f), 10.0f, 100.0f));
		//m_Shader = new Shader("../API/Shaders/VertexNormal.glsl", "../API/Shaders/FragmentNormal.glsl");
	}

	std::shared_ptr<Framebuffer>& Renderer::GetFrameBuffer(){
		return m_Framebuffer;
	}

	void Renderer::OnEvent(event& e) {
		switch (e.getEventCat()){
		default:
			break;
		case (Qubit::eventCategory::eventCatApp): {
			switch (e.getEventType()){
				default:
					break;
			case(Qubit::eventType::windowResize) : {
		
				//m_Framebuffer = new Framebuffer(FramebufferSpecification())
					}
				}
			}
		}




	}
	
	void Renderer::SetPerspective(float* zoom, uint16_t aspectWidth, uint16_t aspectHeight, float nearPlane, float farPlane) {
		m_Shader->UseProgram();
		projection = glm::perspective<float>(*zoom, (float)aspectWidth/(float)aspectHeight, nearPlane, farPlane);
		
	}

	void Renderer::SetOrthographic(float width, float height, float nearPlane, float farPlane) {
		m_Shader->UseProgram();
		projection = glm::ortho<float>(0.0f, width, height, 0.0f, nearPlane, farPlane);
		

	}

	void Renderer::SetFramebuffer(FramebufferSpecification& spec) {
		m_Framebuffer = std::shared_ptr<Framebuffer>(new Framebuffer(spec));
	}

	void Renderer::SetFramebuffer(FramebufferSpecification&& spec) {
		m_Framebuffer = std::shared_ptr<Framebuffer>(new Framebuffer(spec));
	}

}