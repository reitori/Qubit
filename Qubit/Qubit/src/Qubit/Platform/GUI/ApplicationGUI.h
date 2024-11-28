#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Qubit/Application/Base/ApplicationWindow.h"
#include "Qubit/Layer/Layer/Layer.h"
#include "Qubit/Platform/GUI/UI/SceneViewGUI.h"
#include "Qubit/Events/Base/KeyCodes.h"

//220 230 not offered in summer
namespace Qubit{
	class GUI : public layer{
	public:
		static void Init(GLFWwindow* window, unsigned int width, unsigned int height);
		static GUI* s_GUIInstance;

		void Render();

		void OnAttatch() override;
		void OnDetatch() override;

		void OnUpdate() override;
		void OnEvent(event& e) override;

		void Begin();
		void End();
	
		void setApplicationWidth(unsigned int width) { s_GUIInstance->m_ApplicationWidth = width; }
		void setApplicationHeight(unsigned int height) { s_GUIInstance->m_ApplicationHeight = height; }
		~GUI();
	protected:

	private:
		GUI() = default;
		GUI(GLFWwindow* window, unsigned int width, unsigned int height);
		//GUI(GLFWwindow* window, unsigned int width, unsigned int height);
		void EnableStartUp();
		ImGuiWindowFlags m_DockspaceFlags, m_WindowFlags;
		ImGuiID m_DockspaceID;
		ImGuiContext* context = NULL;

		uint16_t m_ApplicationWidth = 1920;
		uint16_t m_ApplicationHeight = 1080;
		float m_Time = 0.0f;

		static bool ApplicationStartUpAlreadyInit;

		//UI stuff
		std::shared_ptr<SceneView> m_SceneView;
		std::shared_ptr<Renderer> m_RenderInstance;
		glm::vec3 color;
	};
}