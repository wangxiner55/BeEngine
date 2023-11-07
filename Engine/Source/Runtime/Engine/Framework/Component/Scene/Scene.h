#pragma once
#include "../../../ThirdParty/Entt/include/Entt.hpp"

namespace BEngine
{
	class Scene
	{
	public:
		Scene();
		~Scene();



		entt::entity CreateEntity();

		entt::registry& Reg() { return m_Registry; }

		void Tick(Timestep ts);
	private:

		entt::registry m_Registry;


	};


}