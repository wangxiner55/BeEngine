#pragma once



#include "Engine/Render/FrameBuffer.h"



namespace BEngine
{

	class OpenGLFramebuffer : public Framebuffer
	{

	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual const FramebufferSpecification& GetSpecification() const override { return m_specification; }

		virtual uint32_t GetColorAttachmentRendererId() const override { return m_ColorAttachment; }
	private:
		unsigned int  m_RendererID = 0;
		unsigned int  m_ColorAttachment = 0;
		unsigned int  m_DepthAttachment = 0;
		FramebufferSpecification m_specification;
	};










}