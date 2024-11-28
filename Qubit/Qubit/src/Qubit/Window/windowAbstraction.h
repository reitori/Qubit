#pragma once
#include "Qubit/Events/Event.h"
#include "Qubit/Events/ApplicationEvent.h"
#include "Qubit/Events/KeyboardEvent.h"
#include "Qubit/Events/MouseEvent.h"

namespace Qubit {
	class window {
	public:
		using eventCallbackFn = std::function<void(event& e)>;

		//virtual bool Render() = 0;
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;
		virtual inline void SetEventCallback(const eventCallbackFn& callback) = 0;

		virtual inline Qubit::pair<float, float> GetMousePos() = 0;
		virtual void* GetWindow() const = 0;

		virtual void Terminate() = 0;

	protected:
		window() = default;
		virtual ~window() = default;
	};
}