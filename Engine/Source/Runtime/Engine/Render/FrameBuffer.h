#pragma once
#include <glm/glm.hpp>

namespace BEngine
{
	struct FramebufferSpecification
	{
		uint32_t width, height;
		uint32_t samples = 1;
		bool SwapChainTarget = false;
	};


	class Framebuffer
	{
	public:
		virtual ~Framebuffer(){}

		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;
		virtual uint32_t GetColorAttachmentRendererId() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);



	};










}