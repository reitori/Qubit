#pragma once

#include "Qubit/Core/Core.h"
#include "Qubit/OtherUtility/pair.h"

namespace Qubit {

	class QBT_API input {
	public:
		static input* GetInput() { return s_Instance; }

		inline static bool IsKeyPressed(unsigned int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMousePressed(unsigned int mouseCode) { return s_Instance->IsMousePressed(mouseCode); }
		inline static bool IsMouseMoved(Qubit::pair<float, float>& mousePos) { return s_Instance->IsMouseMoved(mousePos);  }
		inline static Qubit::pair<float, float> MousePos(){ return s_Instance->MousePosImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(unsigned int keycode) = 0;
		virtual bool IsMousePressedImpl(unsigned int mouseCode) = 0;
		virtual bool IsMouseMovedImpl(Qubit::pair<float, float>& mousePos) = 0;

		virtual Qubit::pair<float, float> MousePosImpl() = 0;

	private:
		static input* s_Instance;
	};
}