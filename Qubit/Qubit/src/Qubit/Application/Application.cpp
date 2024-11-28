#include <QubitPCH.h>
#include "Application.h"
//#include "Base/ApplicationGUI.h"

namespace Qubit {

	Application* Application::app_Instance = NULL;
	

	void Application::Init() {
		app_Instance = new Application;
	}

	Application* Application::GetInstance() {
		return app_Instance;
	}

	Application::Application() {
		Qubit::Log::Init();
		ApplicationWindow::a_Window = new Qubit::OpenGLWindow;
		ApplicationWindow::a_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		Qubit::GUI::Init(ApplicationWindow::a_Window->GetPointerToWindow(), ApplicationWindow::a_Window->GetWidth(), ApplicationWindow::a_Window->GetHeight());
		m_layerStack.PushBackLayer(Qubit::GUI::s_GUIInstance);
	}

	/* Runs the entire application
		-Rendering
		-Physics	
		-Callback updates         */
	void Application::Run() {
		while (!ApplicationWindow::a_Window->WindowShouldClose()) {

			ApplicationWindow::a_Window->PollEvents();
			ApplicationWindow::a_Window->ClearColor(1.0f, 0.5f, 0.75f, 1.0f);

			for (layer* layerPointer : m_layerStack) {
				layerPointer->OnUpdate();
			}

			GUI::s_GUIInstance->Begin();
			GUI::s_GUIInstance->Render();
			GUI::s_GUIInstance->End();

			ApplicationWindow::a_Window->SwapBuffers();
		}
		delete GUI::s_GUIInstance;
		delete ApplicationWindow::a_Window;
		delete app_Instance;
	}

	void Application::PushLayer(layer* i_layer){
		i_layer->OnAttatch();
		m_layerStack.PushBackLayer(i_layer);
	}
	void Application::PushOverlay(layer* i_layer){
		i_layer->OnDetatch();
		m_layerStack.PushBackOverlay(i_layer);
	}
	void Application::PopLayer(layer* i_layer) {
		m_layerStack.PopLayer(i_layer);
	}

	void Application::OnEvent(Qubit::event& e) {
		std::string str = e.toString();
		std::cout << str << std::endl;
		for (auto i = m_layerStack.end(); i != m_layerStack.begin(); ) {
			(*--i)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	bool Application::handleEvent(Qubit::event& event) {
		return true;
	}

	inline window* Application::PointerToWindow() {
		return ApplicationWindow::a_Window;
	}

	Application::~Application() {
		for (auto i = m_layerStack.end(); i != m_layerStack.begin();) {
			delete *i;
		}

		delete ApplicationWindow::a_Window;
	}
}