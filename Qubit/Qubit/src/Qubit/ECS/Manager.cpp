#include <QubitPCH.h>
#include "Manager.h"

namespace Qubit {

	//Although probably not the best solution, typeid is used to create "pure" ECS, rather than creating virtual signature getters in each Component.


	//----------------------------------------------------------------------------------------------------------------------------------------------//
	//			                                                   ComponentManager                                                                 //
	//----------------------------------------------------------------------------------------------------------------------------------------------//

	void Manager::AddComponent(const Entity& entity, const Component& component) {
		std::lock_guard<std::mutex> lock(s_Lock);
		m_VecEntities[entity.ID].emplace(s_Signatures.at(typeid(component).name()), component);
	}

	void Manager::DeleteComponent(const Entity& entity, const Component& component) {
		std::lock_guard<std::mutex> lock(s_Lock);
		m_VecEntities[entity.ID].erase(s_Signatures.at(typeid(component).name()));
	}

	void Manager::DeleteComponentType(const Component& component) {
		std::lock_guard<std::mutex> lock(s_Lock);
		std::bitset<QBT_MAX_COMPONENTS> ComponentType = s_Signatures.at(typeid(component).name());
		for (int i = 0; i < m_Entities.size(); i++) {
			std::unordered_map<std::bitset<QBT_MAX_COMPONENTS>, Component>& map = m_VecEntities[i];
			if (map.find(ComponentType) != map.end()) {
				map.erase(ComponentType);
			}
		}
	}

	void Manager::CreateNewComponentType(Component& component) {
		std::lock_guard<std::mutex> lock(s_Lock);
		if (Component* comp = dynamic_cast<Component*>(&component)) {
			s_Signatures.emplace(typeid(component).name(), m_AvailSignatures.front());
			m_AvailSignatures.pop();
		}
		else {
			std::string str{ "Component Type: " };
			str.append(typeid(component).name());
			Qubit::Log::printWarning(str.c_str(), Qubit::Log::getCoreLogger());
		}
	}

	//----------------------------------------------------------------------------------------------------------------------------------------------//
	//																EntityManager                                                                   //
	//----------------------------------------------------------------------------------------------------------------------------------------------//
	Manager::Manager() {
		for (int i = 1; i <= QBT_MAX_ENTITIES; i++) {
			m_AvailIDs.push((uint32_t)i);
		}
	}

	Entity Manager::CreateEntity() {
		std::lock_guard<std::mutex> lock(s_Lock);
		Entity entity { m_AvailIDs.front() };
		m_AvailIDs.pop();
		return entity;
	}

	void Manager::DeleteEntity(Entity& entity) {
		std::lock_guard<std::mutex> lock(s_Lock);
		m_AvailIDs.push(entity.ID);
		entity.ID = 0;
	}

	//----------------------------------------------------------------------------------------------------------------------------------------------//
	//															       	 End                                                                        //
	//----------------------------------------------------------------------------------------------------------------------------------------------//
}