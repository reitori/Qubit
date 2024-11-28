#pragma once
#include "Qubit/Window/OpenGL/Implementation.h"

//MUST be initialized in Application
//SPLIT GUI AND WINDOW
namespace Qubit {
	class ApplicationWindow {
	public:
		static ApplicationWindow* GetInstance() {
			return s_AppWin;
		}

		static Qubit::OpenGLWindow* a_Window;
		~ApplicationWindow() {
			delete a_Window;
		}
	private:
		ApplicationWindow() {}
		static ApplicationWindow* s_AppWin;
	};
}