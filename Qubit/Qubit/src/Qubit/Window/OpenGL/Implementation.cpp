#include <QubitPCH.h>
#include "Implementation.h"

namespace Qubit {

	bool OpenGLWindow::alreadyInit = false;

	

	//Maybe craete imGUI in a different class?
	OpenGLWindow::OpenGLWindow(const unsigned int width, const unsigned int height, const char* title) : windowWidth(width), windowHeight(height){
		windowShouldClose = false;
		if (!alreadyInit) {
			if (!glfwInit()) {
				Log::printError("GLFW FAILED TO INITIALIZE", Qubit::Log::getCoreLogger());
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			glwindow = glfwCreateWindow(width, height, title, NULL, NULL);
			if (glwindow == NULL) {
				Log::printError("WINDOW WAS NOT CREATED", Qubit::Log::getCoreLogger());
				glfwTerminate();
			}

			glfwMakeContextCurrent(glwindow);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				Log::printError("GLAD FAILED TO INITIALIZE", Qubit::Log::getCoreLogger());
			}

			glfwSetKeyCallback(glwindow, &key_callback);
			glfwSetCursorPosCallback(glwindow, &mouse_pos_callback);
			glfwSetScrollCallback(glwindow, &scroll_callback);
			glfwSetMouseButtonCallback(glwindow, mouse_button_callback);
			// Maybe Later glfwSetWindowMaximizeCallback(window, window_maximize_callback);
			glfwSetWindowSizeCallback(glwindow, &window_resize_callback);
			glfwSetWindowCloseCallback(glwindow, &window_close_callback);

			alreadyInit = true;
		}

		else {
			glwindow = glfwCreateWindow(width, height, title, NULL, NULL);

			glfwSetKeyCallback(glwindow, &key_callback);
			glfwSetCursorPosCallback(glwindow, &mouse_pos_callback);
			glfwSetScrollCallback(glwindow, &scroll_callback);
			glfwSetMouseButtonCallback(glwindow, mouse_button_callback);
			// Maybe Later glfwSetWindowMaximizeCallback(window, window_maximize_callback);
			glfwSetWindowSizeCallback(glwindow, &window_resize_callback);
			glfwSetWindowCloseCallback(glwindow, &window_close_callback);
		}

		glfwSetWindowUserPointer(glwindow, this);
	}

	OpenGLWindow::OpenGLWindow() {
		windowShouldClose = false;

		windowWidth = 1920;
		windowHeight = 1080;

		if (!alreadyInit) {
			if (!glfwInit()) {
				Log::printError("GLFW FAILED TO INITIALIZE", Qubit::Log::getCoreLogger());
			}

			/*windowWidth = mode->width;
			windowHeight = mode->height;

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate); */

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			glwindow = glfwCreateWindow(windowWidth, windowHeight, "Qubit", NULL, NULL);
			if (glwindow == NULL) {
				Log::printError("WINDOW WAS NOT CREATED", Qubit::Log::getCoreLogger());
				glfwTerminate();
			}

			glfwMakeContextCurrent(glwindow);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				Log::printError("GLAD FAILED TO INITIALIZE", Qubit::Log::getCoreLogger());
			}

			glfwSetKeyCallback(glwindow, &key_callback);
			glfwSetCursorPosCallback(glwindow, &mouse_pos_callback);
			glfwSetScrollCallback(glwindow, &scroll_callback);
			glfwSetMouseButtonCallback(glwindow, mouse_button_callback);
			// Maybe Later glfwSetWindowMaximizeCallback(window, window_maximize_callback);
			glfwSetWindowSizeCallback(glwindow, &window_resize_callback);
			glfwSetWindowCloseCallback(glwindow, &window_close_callback);

			alreadyInit = true;
		}

		else {
			glwindow = glfwCreateWindow(windowWidth, windowHeight, "Qubit", NULL, NULL);

			glfwSetKeyCallback(glwindow, &key_callback);
			glfwSetCursorPosCallback(glwindow, &mouse_pos_callback);
			glfwSetScrollCallback(glwindow, &scroll_callback);
			glfwSetMouseButtonCallback(glwindow, mouse_button_callback);
			// Maybe Later glfwSetWindowMaximizeCallback(window, window_maximize_callback);
			glfwSetWindowSizeCallback(glwindow, &window_resize_callback);
			glfwSetWindowCloseCallback(glwindow, &window_close_callback);
		}
		glfwSetWindowUserPointer(glwindow, this);
	}

	inline void OpenGLWindow::OnUpdate() {



		glfwSwapBuffers(glwindow);
		glfwPollEvents();
	}

	inline void OpenGLWindow::SetEventCallback(const eventCallbackFn& callback){ 
		eventCallback = callback; 
	}

	void OpenGLWindow::Terminate() {
		glfwDestroyWindow(glwindow);
		glfwTerminate();
	}

	void* OpenGLWindow::GetWindow() const {
		return glwindow;
	}
}

//Create a mouse, key, button, and windowresize callback possibly? In each of those callbacks test for input and then create an event class to send out?

/*

	GLFWwindow*
namespace Qubit { Graphics::window = NULL;

	void Graphics::Init() {
		if (!glfwInit()) {
			
		}

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		Graphics::window = glfwCreateWindow(mode->width, mode->height, "Qubit", NULL, NULL);
		if (Graphics::window == NULL) {
			glfwTerminate();
		}

		glfwMakeContextCurrent(Graphics::window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			
		}

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(Graphics::window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

	}	

	void Graphics::Run() {

		bool testBool = false;
		float color[3] = { 1.0f, 1.0f, 1.0f };

		while (!glfwWindowShouldClose(window)) {
			//Poll Events, still don't know what to do here
			glClear(GL_COLOR_BUFFER_BIT);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			
			{
				ImGui::Begin("3D-View Editor");

				ImGui::Text("You can click on objects and by using this interface, you can access and change their properties.");
				ImGui::Checkbox("Test", &testBool);

				ImGui::ColorEdit3("Color Picker Test", color);
				ImGui::End();
			}

			ImGui::Render();


			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(color[0], color[1], color[2], 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
	}
	void Graphics::Render() {

	}

	void Graphics::Terminate() {

	}

	GLFWwindow* Graphics::GetPointerToWindow() {
		return Graphics::window;
	}
}

*/