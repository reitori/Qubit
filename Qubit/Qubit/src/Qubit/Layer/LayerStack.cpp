#include <QubitPCH.h>
#include "LayerStack.h"

namespace Qubit {

	layerStack::layerStack() {
		layerItPos = 0;
	}

	void layerStack::PushBackLayer(layer* layer) {
		m_layerStack.emplace(m_layerStack.begin() + layerItPos, layer);
		layerItPos += 1;
	}

	void layerStack::PushBackOverlay(layer* overlay) {
		m_layerStack.emplace_back(overlay);
	}

	void layerStack::PopLayer(layer* otherLayer) {
		std::vector<layer*>::iterator it = find(m_layerStack.begin(), m_layerStack.end(), otherLayer);
		if (it != m_layerStack.end()) {
			m_layerStack.erase(it);
			layerItPos--;
		}
	}


	std::vector<layer*>::iterator layerStack::begin() {
		return m_layerStack.begin();
	}

	std::vector<layer*>::iterator layerStack::end() {
		return m_layerStack.end();
	}
}