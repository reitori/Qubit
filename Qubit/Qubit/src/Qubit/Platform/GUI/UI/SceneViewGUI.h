#include <imgui.h>
#include "Qubit/Platform/Renderer/Renderer.h"
#include "Qubit/Events/Event.h"

namespace Qubit {

	class SceneView{
	public:
		//Initializes the name of the scene view and the renderer that should bind to this instance
		SceneView() = default;
		SceneView(const char* name) : m_Name(name) { m_WindowFlags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus;}

		void InitializeDockSpace();
		void ChangeWindowFlags(ImGuiWindowFlags flag);
		void Render();

		//Process all events... different from ImGUI events which will be executed through a binded RendererReference
		void OnMouseEvent(event& e);
		void OnKeyboardEvent(event& e);
		Renderer* GetRenderInstance() { return &m_RenderInstance;  }
	private:
		Renderer m_RenderInstance;
		ImGuiWindowFlags m_WindowFlags;
		std::string m_Name;

		float mousePosX, mousePosY;
		uint16_t m_SceneHeight, m_SceneWidth;
		bool isHovered = false;
		ImVec2 m_Pos;
	};

}