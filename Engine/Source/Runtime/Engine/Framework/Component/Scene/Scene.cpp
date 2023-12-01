#include "Scene.h"

#include <glm/glm.hpp>

#include "../Component/Component.h"
#include "../Mesh/MeshComponent.h"
#include <Engine/Render/Render.h>

namespace BEngine
{
	static void DoMaths(const glm::mat4& trans)
	{

	}


	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
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

		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity": name;



		return entity;
	}

	void Scene::Tick(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<ModelComponent>);
		for (auto entity : group)
		{
			auto& [transfom, Mesh] = group.get<TransformComponent, ModelComponent>(entity);

			
			Mesh.m_Mesh->Draw(Mesh.m_Shader, transfom);
		}
	}

}