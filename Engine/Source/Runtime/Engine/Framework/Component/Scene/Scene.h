#pragma once
#include "../../../ThirdParty/Entt/include/Entt.hpp"
#include "../Component/Entity.h"

namespace BEngine
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();



		Entity CreateEntity(const std::string& name = std::string());

		entt::registry& Reg() { return m_Registry; }

		void Tick(Timestep ts);
	private:

		entt::registry m_Registry;

		friend class Entity;

	};


}