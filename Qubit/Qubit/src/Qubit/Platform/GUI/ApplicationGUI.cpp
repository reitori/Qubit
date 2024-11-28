#include <QubitPCH.h>
#include "Qubit/Platform/GUI/ApplicationGUI.h"

//Extremely Important:

//ImGUI CANNOT run on another thread
//All calls are made on the main thread and will not work if you start using any ImGUI functions or definitions on a different thread

//    If you want thread-safety to allow N threads to access N different contexts, you can:
//    - Change this variable to use thread local storage so each thread can refer to a different context, in imconfig.h:
//          struct ImGuiContext;
//          extern thread_local ImGuiContext* MyImGuiTLS;
//          #define GImGui MyImGuiTLS
//      And then define MyImGuiTLS in one of your cpp file. Note that thread_local is a C++11 keyword, earlier C++ uses compiler-specific keyword.

//You can do this if you want, future self. But you probably won't do so unless if you need to fully optimize this thing.

namespace Qubit {

	bool GUI::ApplicationStartUpAlreadyInit = false;
	GUI* GUI::s_GUIInstance = NULL;

	void GUI::Init(GLFWwindow* window, unsigned int width, unsigned int height) {
		if (!ApplicationStartUpAlreadyInit) {
			s_GUIInstance = new GUI(window, width, height);
			s_GUIInstance->EnableStartUp();
			ApplicationStartUpAlreadyInit = true;
		}

		else {
			Qubit::Log::printError("ImGUI is already initialized", Qubit::Log::getCoreLogger());
		}
	}

	GUI::GUI(GLFWwindow* window, unsigned int width, unsigned int height) : m_ApplicationWidth(width), m_ApplicationHeight(height){
		m_DockspaceID = 0;
		m_WindowFlags = 0;
		m_SceneView = std::shared_ptr<SceneView>(new SceneView("Scene View"));
		m_RenderInstance = std::shared_ptr<Renderer>(m_SceneView->GetRenderInstance());

			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
			io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			io.ConfigViewportsNoAutoMerge = true;
			io.ConfigViewportsNoTaskBarIcon = true;

			io.KeyMap[ImGuiKey_Tab] = Qubit::key::Tab;
			io.KeyMap[ImGuiKey_LeftArrow] = Qubit::key::Left;
			io.KeyMap[ImGuiKey_RightArrow] = Qubit::key::Right;
			io.KeyMap[ImGuiKey_UpArrow] = Qubit::key::Up;
			io.KeyMap[ImGuiKey_DownArrow] = Qubit::key::Down;
			io.KeyMap[ImGuiKey_PageUp] = Qubit::key::PageUp;
			io.KeyMap[ImGuiKey_PageDown] = Qubit::key::PageDown;
			io.KeyMap[ImGuiKey_Home] = Qubit::key::Home;
			io.KeyMap[ImGuiKey_End] = Qubit::key::End;
			io.KeyMap[ImGuiKey_Insert] = Qubit::key::Insert;
			io.KeyMap[ImGuiKey_Delete] = Qubit::key::Delete;
			io.KeyMap[ImGuiKey_Backspace] = Qubit::key::Backspace;
			io.KeyMap[ImGuiKey_Space] = Qubit::key::Space;
			io.KeyMap[ImGuiKey_Enter] = Qubit::key::Enter;
			io.KeyMap[ImGuiKey_Escape] = Qubit::key::Escape;
			io.KeyMap[ImGuiKey_A] = Qubit::key::A;
			io.KeyMap[ImGuiKey_C] = Qubit::key::C;
			io.KeyMap[ImGuiKey_V] = Qubit::key::V;
			io.KeyMap[ImGuiKey_X] = Qubit::key::X;
			io.KeyMap[ImGuiKey_Y] = Qubit::key::Y;
			io.KeyMap[ImGuiKey_Z] = Qubit::key::Z;

			ImGui::StyleColorsDark();

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus;
	}

	void GUI::EnableStartUp() {
		Begin();
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		m_DockspaceFlags = 0;
		m_DockspaceFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
		m_DockspaceFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		m_DockspaceFlags |= ImGuiWindowFlags_NoBackground;

		char label[32];
		ImFormatString(label, IM_ARRAYSIZE(label), "DockSpaceViewport_%08X", viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin(label, NULL, m_DockspaceFlags);
		ImGui::PopStyleVar(3);

		m_DockspaceID = ImGui::GetID("DockSpace");
		ImGui::DockSpace(m_DockspaceID, ImVec2(0.0f, 0.0f), (ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode));
		ImGui::End();
		//End of dockspace initialization

		//Start of preset window docks
		ImGui::DockBuilderRemoveNode(m_DockspaceID);
		ImGui::DockBuilderAddNode(m_DockspaceID, (ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode));
		ImGui::DockBuilderSetNodeSize(m_DockspaceID, ImGui::GetMainViewport()->WorkSize);

		ImGuiID mainDockspace_id = m_DockspaceID;
		ImGuiID dockLeftID = ImGui::DockBuilderSplitNode(mainDockspace_id, ImGuiDir_Left, 0.15f, NULL, &mainDockspace_id);
		ImGuiID dockRightID = ImGui::DockBuilderSplitNode(mainDockspace_id, ImGuiDir_Right, 0.20f, NULL, &mainDockspace_id);
		ImGuiID dockBottomID = ImGui::DockBuilderSplitNode(mainDockspace_id, ImGuiDir_Down, 0.15f, NULL, &mainDockspace_id);
		ImGuiID dockMiddleID = ImGui::DockBuilderSplitNode(mainDockspace_id, ImGuiDir_Right, 0.10f, NULL, &mainDockspace_id);

		ImGui::DockBuilderDockWindow("Hierarchy", dockLeftID);
		ImGui::DockBuilderDockWindow("Scene View", dockMiddleID);
		ImGui::DockBuilderDockWindow("Files", dockBottomID);
		ImGui::DockBuilderDockWindow("Functions", dockRightID);
		
		m_SceneView->InitializeDockSpace();
		End();
	}
	
	void GUI::OnAttatch() {
		
	}

	void GUI::Render() {

		bool p_selected = false;

		ImGuiIO& io = ImGui::GetIO();

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		s_GUIInstance->m_Time = time;
		
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		char label[32];
		ImFormatString(label, IM_ARRAYSIZE(label), "DockSpaceViewport_%08X", viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin(label, NULL, m_DockspaceFlags);
		ImGui::PopStyleVar(3);

		s_GUIInstance->m_DockspaceID = ImGui::GetID("DockSpace");
		ImGui::DockSpace(s_GUIInstance->m_DockspaceID, ImVec2(0.0f, 0.0f), (ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode));
		ImGui::End();

		ImGui::SetNextWindowViewport(viewport->ID);

		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::SetNextWindowBgAlpha(0.0f);
			
			m_SceneView->Render();

			ImGui::Begin("Hierarchy", NULL, m_WindowFlags);
			ImGui::End();

			
			ImGui::Begin("Files", NULL, m_WindowFlags);
			//Texture/Model loading
			/*
			*if(ImGui load model button == true){
			*	m_RenderInstance.loadTexture(imGuiPathSelected);
			*	[bool] stillLoad;
			*	for(int i = 0; i < list of callback functions.size(); i++){
			*		
			*	}
			* }
			*/

			ImGui::End();

			ImGui::Begin("Functions", NULL, m_WindowFlags);
			if (ImGui::ColorEdit3("Background Color", &m_RenderInstance->BackgroundColor[0]));
			ImGui::Button("Create New Scene View");

			ImGui::End();

		}

		{
			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("File")) {
					ImGui::MenuItem("Taco1", NULL, &p_selected);
					ImGui::MenuItem("Taco2", NULL, &p_selected);
					ImGui::MenuItem("Taco3", NULL, &p_selected);
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}
	
		}

	}


	void GUI::OnDetatch() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void GUI::OnUpdate() {

	}

	void GUI::OnEvent(event& e) {
		EventData* data;
		switch (e.getEventCat()) {
		case (Qubit::eventCategory::eventCatMouse):
			m_SceneView->OnMouseEvent(e);
			break;
				
		case (Qubit::eventCategory::eventCatKey):
			m_SceneView->OnKeyboardEvent(e);
			break;

		case (Qubit::eventCategory::eventCatApp):
			data = e.getData();
			if (e.getEventType() == Qubit::eventType::windowResize) {
				m_ApplicationWidth = data->uintPairedData.x;
				m_ApplicationHeight = data->uintPairedData.y;
				break;
			}
		default:
			break;
		}
	}

	void GUI::Begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GUI::End() {
		ImGui::EndFrame();
		ImGui::Render();
		int width, height;
		glfwGetFramebufferSize(ApplicationWindow::a_Window->GetPointerToWindow(), &width, &height);
		glViewport(0, 0, width, height);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(ApplicationWindow::a_Window->GetWidth(), ApplicationWindow::a_Window->GetHeight());
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	GUI::~GUI() {
		delete s_GUIInstance;
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

}
