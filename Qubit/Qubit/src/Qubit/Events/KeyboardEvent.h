
#pragma once
#include "Event.h"
#include "Base/KeyCodes.h"

namespace Qubit {
	class keyEvent : public event{
	public:
		void setKeyPressed(const key::keyCodes& key) {
			keyPressed->keyButton = key;
		}
		
		key::keyCodes getKeyPressed() const {
			return keyPressed->keyButton;
		}

		virtual eventType getEventType() const = 0;
		EventData* getData() const override { return keyPressed; }

		eventCategory getEventCat() const override {
			return eventCategory::eventCatKey;
		}

		virtual ~keyEvent() {
			delete keyPressed;
		};

	protected:
		keyEvent(const key::keyCodes& key) { keyPressed = new EventData; keyPressed->keyButton = key;  }
		keyEvent(const key::keyCodes&& key) { keyPressed = new EventData; keyPressed->keyButton = key; }
		keyEvent() = default;
	private:
		EventData* keyPressed;
	};
	

	class keyEventPressed : public keyEvent {
	public:
		keyEventPressed(const Qubit::key::keyCodes& key) {
			setKeyPressed(key);
		}

		static eventType GetStaticType() { return eventType::keyPress; }
		eventType getEventType() const override { return eventType::keyPress; }

		std::string toString() const {
			std::stringstream ss;
			ss << "keyEventPressed: " << getKeyPressed();
			return ss.str();
		}
	};

	class keyEventReleased : public keyEvent {
	public:
		keyEventReleased(const key::keyCodes& key) {
			setKeyPressed(key);
		}

		static eventType GetStaticType() { return eventType::keyRelease; }
		eventType getEventType() const override {return eventType::keyRelease;}

		std::string toString() const {
			std::stringstream ss;
			ss << "keyEventReleased: " << getKeyPressed();
			return ss.str();
		}
	};
}
