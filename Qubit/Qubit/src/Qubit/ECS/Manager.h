#pragma once
#include <bitset>
#include <queue>
#include <typeinfo>
#include "Qubit/ECS/Component.h"
#include "Qubit/ECS/Entity.h"




namespace Qubit {

	static void AddComponent(const Entity& entity, const Component& component);
	static Entity CreateEntity();
	static void CreateNewComponentType(Component& component);

	static void DeleteEntity(Entity& entity);
	static void DeleteComponent(const Entity& entity, const Component& component);
	static void DeleteComponentType(const Component& component);



}





namespace Qubit {

	//Manager class is made to be multi-threaded safe
	class QBT_API Manager {
	public:
		Manager();

		static void AddComponent(const Entity& entity, const Component& component);
		static Entity CreateEntity();
		static void CreateNewComponentType(Component& component);

		static void DeleteEntity(Entity& entity);
		static void DeleteComponent(const Entity& entity, const Component& component);
		static void DeleteComponentType(const Component& component);
	private:
		static std::vector<std::unordered_map<std::bitset<QBT_MAX_COMPONENTS>, Component>> m_VecEntities;
		static std::unordered_map<uint32_t, Entity> m_Entities;
		static std::queue<uint32_t> m_AvailIDs;

		static std::queue<std::bitset<QBT_MAX_COMPONENTS>> m_AvailSignatures;
		static std::unordered_map<std::string, std::bitset<QBT_MAX_COMPONENTS>> s_Signatures;

		static std::mutex s_Lock;
	};
}