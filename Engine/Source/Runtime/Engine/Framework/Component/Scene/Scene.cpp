#include "Scene.h"

#include <glm/glm.hpp>

#include "../Component/Component.h"
#include <Engine/Render/Render.h>

namespace BEngine
{
	static void DoMaths(const glm::mat4& trans)
	{

	}

	

	Scene::Scene()
	{
		struct MeshComponent
		{
			bool Data;
			MeshComponent() = default;
		};

		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

	}

	Scene::~Scene()
	{
	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::Tick(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<CubeTransformComponent>);
		for (auto entity : group)
		{
			auto& [transfom, cube] = group.get<TransformComponent, CubeTransformComponent>(entity);

			//Render::Submit()
		}
	}

}