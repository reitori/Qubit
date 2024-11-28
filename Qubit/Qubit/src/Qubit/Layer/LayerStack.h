#pragma once
#include "Qubit/Core/Core.h"
#include "Qubit/Layer/Layer/Layer.h"

namespace Qubit {
	
	class QBT_API layerStack {
	public:
		layerStack();
		void PushBackLayer(layer* layer);
		void PushBackOverlay(layer* overlay);

		void PopLayer(layer* layer);

		std::vector<layer*>::iterator begin();
		std::vector<layer*>::iterator end();
	private:
		std::vector<layer*> m_layerStack;
		unsigned int layerItPos;
	};
}