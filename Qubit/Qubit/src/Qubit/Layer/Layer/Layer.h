#pragma once
#include "Qubit/Core/Core.h"
#include "Qubit/Events/Event.h"

namespace Qubit {
	class QBT_API layer {
	public:
		layer();
		layer(const char* n);

		virtual void OnAttatch();
		virtual void OnDetatch();
		virtual void OnUpdate();
		virtual void OnEvent(event& e);
		virtual ~layer();

		bool operator==(const layer& otherL);
		bool operator==(const char* i_name);
	private:
		const char* name;
	};
}