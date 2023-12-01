#pragma once

namespace BEngine
{

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {}

		operator std::string() { return Tag; }
		operator const std::string() const { return Tag; }


	};

	struct TransformComponent
	{
		glm::mat4 Transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& trans)
			:Transform(trans) {}

		operator glm::mat4() { return Transform; }
		operator const glm::mat4() const { return Transform; }


	};	
	
	
	struct MeshTransformComponent
	{
		glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f };

		MeshTransformComponent() = default;
		MeshTransformComponent(const MeshTransformComponent&) = default;
		MeshTransformComponent(const glm::vec4 color)
			:Color(color) {}


	};




}