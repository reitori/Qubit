#pragma once
#include "Qubit/Core/Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Qubit/Window/windowAbstraction.h"

namespace Qubit {
	class OpenGLWindow : public window{
	public:
		bool windowShouldClose;
		std::vector<event*> events;

		OpenGLWindow(const unsigned int width, const unsigned int height, const char* title);
		OpenGLWindow();

		inline void OnUpdate();
		inline void ClearColor(float redNormalized, float greenNormalized, float blueNormalized, float alphaNormalized) {
			glClearColor(redNormalized, greenNormalized, blueNormalized, alphaNormalized);
			glClear(GL_COLOR_BUFFER_BIT);
		}
		inline bool WindowShouldClose() { return glfwWindowShouldClose(glwindow); }
		inline void PollEvents() { glfwPollEvents(); }
		inline void SwapBuffers() { glfwSwapBuffers(glwindow); }


		inline unsigned int GetWidth() { return windowWidth; }
		inline unsigned int GetHeight() { return windowHeight; }
		inline void SetEventCallback(const eventCallbackFn& callback) override;

		//Not entirely sure what to do for now. Either do getLargeEvent (which is a list of all events found) or just get a single event
		inline GLFWwindow* GetPointerToWindow() { return glwindow;  }
		inline Qubit::pair<float, float> GetMousePos() { Qubit::pair<float, float> reVal; glfwGetCursorPos(glwindow, (double*)&reVal.x, (double*)&reVal.y); return reVal;  }

		void* GetWindow() const override;

		void Terminate();
		~OpenGLWindow() = default;
	private:
		eventCallbackFn eventCallback;

		unsigned int windowWidth;
		unsigned int windowHeight;

		static bool alreadyInit;

		event* e = NULL;

		GLFWwindow* glwindow;











		//	CALLBACKS || THIS IS A BREAKPOINT SO YOU DON'T GO PAST THE STUFF YOU ARE ACTUALLY TRYING TO CHANGE

		inline static auto key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
			OpenGLWindow* windowManager = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
			switch (action) {
				case GLFW_PRESS:
				{
					Qubit::keyEventPressed keyEvent((Qubit::key::keyCodes)key);
					windowManager->eventCallback(keyEvent);
					break;
				}
				case GLFW_RELEASE: {
					Qubit::keyEventReleased keyEvent((Qubit::key::keyCodes)key);
					windowManager->eventCallback(keyEvent);
					break;
				}
				case GLFW_REPEAT: {
					//You still need to create the repeat sender here
					//Do it later
					//Whenever you finish this, make sure to switch the GLFW_REPEAT case with the GLFW_RELEASE case to make sure it gets checked in the correct order
					break;
				}
			}
		}

		inline static auto mouse_button_callback(GLFWwindow* window, int button, int action, int mods) -> void {
			OpenGLWindow* windowManager = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
			switch (action) {
				case GLFW_PRESS: {
					Qubit::mouseEventPressed mouseEvent((Qubit::Mouse::mouseCodes)button);
					windowManager->eventCallback(mouseEvent);
					break;
				}
				case GLFW_RELEASE: {
					Qubit::mouseEventReleased mouseEvent((Qubit::Mouse::mouseCodes)button);
					windowManager->eventCallback(mouseEvent);
					break;
				}
			}
		}

		inline static auto scroll_callback(GLFWwindow* window, double xoffset, double yoffset) -> void {
			OpenGLWindow* windowManager = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
			Qubit::mouseEventScrolled m_event((const float)xoffset, (const float)yoffset);
			windowManager->eventCallback(m_event);
		}

		inline static auto mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) -> void {
			OpenGLWindow* windowManager = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
			Qubit::mouseEventMoved m_event((const float)xpos, (const float)ypos);
			windowManager->eventCallback(m_event);
		}

		//Maybe later static void window_maximize_callback
		inline static auto window_resize_callback(GLFWwindow* window, int i_width, int i_height) -> void {
			OpenGLWindow* windowManager = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));

			

			Qubit::windowEventResize wr_event(i_width, i_height);
			windowManager->eventCallback(wr_event);
		}

		inline static auto window_close_callback(GLFWwindow* window) -> void {
			OpenGLWindow* windowManager = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
			glfwDestroyWindow(window);
			glfwTerminate();

			Qubit::windowEventClose wc_event;
			windowManager->eventCallback(wc_event);
		}
	};
}

/*
namespace Qubit {
	class QBT_API Graphics {
	private:
		static GLFWwindow* window;
	public:
		static void Init();
		static void Run();
		static void Render();
		static void Terminate();
		static GLFWwindow* GetPointerToWindow();
	};
}
*/