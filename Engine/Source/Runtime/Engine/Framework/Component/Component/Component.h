#pragma once

namespace BEngine
{

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
	
	
	struct CubeTransformComponent
	{
		glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f };

		CubeTransformComponent() = default;
		CubeTransformComponent(const CubeTransformComponent&) = default;
		CubeTransformComponent(const glm::vec4 color)
			:Color(color) {}


	};




}