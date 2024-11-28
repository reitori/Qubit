#pragma once
#include "Base/KeyCodes.h"
#include "Base/MouseCodes.h"

namespace Qubit {
	enum eventType {
		noEvent = 0,
		windowClose, windowResize,
		appUpdate, appRender,
		keyPress, keyRelease,
		mouseButtonPress, mouseButtonRelease, mouseMove, mouseScroll
	};

	enum eventCategory {
		noEventCat = 0,
		eventCatWindow,
		eventCatApp,
		eventCatKey,
		eventCatMouse,
	};

	union EventData {
		Qubit::pair<float, float> floatPairedData;
		Qubit::pair<unsigned int, unsigned int> uintPairedData;
		Qubit::key::keyCodes keyButton;
		Qubit::Mouse::mouseCodes mouseButton;
	};

	class event{
	public:
		bool handled = false;

		virtual eventType getEventType() const = 0;
		virtual eventCategory getEventCat() const = 0;
		virtual EventData* getData()const  = 0;

		virtual std::string toString() const = 0;

		virtual ~event() = default;
		event() = default;
	};

	class eventSender {
		template<typename T>
		using fn = std::function<bool(T&)>;

	public:
		eventSender(event& e) : m_Event(e) {}

		template<typename T>
		void Send(fn<T> fun) {
			if (m_Event.getEventType() == T::GetStaticType()) {
				m_Event.handled = fun(*(T*)&m_Event);
			}
		}

		std::string toString() const { return "eventSender"; }
	private:
		event& m_Event;
	};
}