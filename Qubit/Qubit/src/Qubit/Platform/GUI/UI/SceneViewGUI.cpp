#include <QubitPCH.h>
#include "Qubit/Platform/GUI/UI/SceneViewGUI.h"

namespace Qubit {
	void SceneView::InitializeDockSpace() {
		ImGui::Begin(m_Name.c_str());
		ImVec2 size = ImGui::GetContentRegionAvail();
		ImGui::End();
		FramebufferSpecification spec{ size.x, size.y };
		m_RenderInstance.SetFramebuffer(spec);
	}

	void SceneView::ChangeWindowFlags(ImGuiWindowFlags flag) {
		m_WindowFlags |= flag;
	}

	void SceneView::Render() {
		ImGui::Begin(m_Name.c_str(), NULL, m_WindowFlags);
		ImGui::PopStyleVar(3);
		ImVec2 SceneViewSize = ImGui::GetContentRegionAvail();
		m_RenderInstance.PreRender({ SceneViewSize.x, SceneViewSize.y });
		m_RenderInstance.Render();
		std::shared_ptr<Framebuffer> framebuffer = m_RenderInstance.GetFrameBuffer();
		ImGui::Image(reinterpret_cast<void*>(framebuffer->GetFramebufferImage()), ImVec2{ framebuffer->m_Specification.width,  framebuffer->m_Specification.height }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		isHovered = ImGui::IsWindowHovered();
		if (isHovered)
			m_Pos = ImGui::GetWindowPos();
		ImGui::End();
	}

	void SceneView::OnKeyboardEvent(event& e) {

	}

	void SceneView::OnMouseEvent(event& e) {
		EventData* data;
		switch (e.getEventType())
		{
		case (Qubit::eventType::mouseMove):
			if (isHovered) {
				data = e.getData();
				ImGuiIO& io = ImGui::GetIO();
				m_RenderInstance.m_Cam->speed = io.DeltaTime;
				m_RenderInstance.m_Cam->mouseMovement(data->floatPairedData.x, data->floatPairedData.y);
				mousePosX = data->floatPairedData.x - m_Pos.x;
				mousePosY = data->floatPairedData.y - m_Pos.y;
			}
		break;

		case (Qubit::eventType::mouseButtonPress):

			if (isHovered) {
				data = e.getData();
				switch (data->mouseButton)
				{
				case (Qubit::Mouse::ButtonMiddle):
					
					m_RenderInstance.m_Cam->mouseButtonInput(mousePosX, mousePosY);
					m_RenderInstance.m_Cam->setMouseButton(Qubit::mouseButton::panButtonDown);
					break;

				case (Qubit::Mouse::ButtonRight):
					m_RenderInstance.m_Cam->mouseButtonInput(mousePosX, mousePosY);
					m_RenderInstance.m_Cam->setMouseButton(Qubit::mouseButton::panButtonDown);
					break;

				default:
					break;
				}
			}
		break;

		case (Qubit::eventType::mouseButtonRelease):

			if (isHovered) {
				m_RenderInstance.m_Cam->setMouseButton(Qubit::mouseButton::none);
			}
		break;

		case (Qubit::eventType::mouseScroll):


			if (isHovered) {
				data = e.getData();
				m_RenderInstance.m_Cam->processZoom(data->floatPairedData.x);
			}
		break;

		default:
			break;
		}
	}

}