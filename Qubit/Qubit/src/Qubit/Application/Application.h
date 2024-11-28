#pragma once
#include "Qubit/Core/Core.h"
#include "Qubit/Events/Event.h"

#include "Base/ApplicationWindow.h"
#include "Qubit/Layer/LayerStack.h"
#include "Qubit/Platform/GUI/ApplicationGUI.h"
#include "Qubit/ECS/Component.h"

namespace Qubit {

	class QBT_API Application {
	public:
		virtual ~Application();

		static void Init();
		static Application* GetInstance();

		void Run();
		void PushLayer(layer* i_layer);
		void PushOverlay(layer* i_layer);
		void PopLayer(layer* i_layer);
		void OnEvent(Qubit::event& event);
		inline window* PointerToWindow();
	private:
		Application();

		bool handleEvent(Qubit::event& event);
		layerStack m_layerStack;

		static Application* app_Instance;
	};
}