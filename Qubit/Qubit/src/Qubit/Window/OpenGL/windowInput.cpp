#include <QubitPCH.h>
#include "Qubit/Window/windowInput.h"
#include "Qubit/Application/Base/ApplicationWindow.h"

namespace Qubit {

	class windowInput : public input {

		bool IsKeyPressedImpl(unsigned int keycode) override { if (glfwGetKey(ApplicationWindow::a_Window->GetPointerToWindow(), keycode) == GLFW_PRESS) return true; return false; }
		bool IsMousePressedImpl(unsigned int mouseCode) override { if (glfwGetMouseButton(ApplicationWindow::a_Window->GetPointerToWindow(), mouseCode) == GLFW_PRESS) return true; return false; }
		bool IsMouseMovedImpl(Qubit::pair<float, float>& mousePos) override { 
			double x, y;
			glfwGetCursorPos(ApplicationWindow::a_Window->GetPointerToWindow(), &x, &y);
			if (mousePos.x == x && mousePos.y == y)
				return true;
			return false;
		}

		Qubit::pair<float, float> MousePosImpl() override { 
			double x, y;
			glfwGetCursorPos(ApplicationWindow::a_Window->GetPointerToWindow(), &x, &y);
			Qubit::pair<float, float> pos(x, y);
			return pos;
		}
	};

	input* input::s_Instance = new windowInput;
}