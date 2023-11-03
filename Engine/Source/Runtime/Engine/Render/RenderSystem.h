#pragma once


namespace BEngine
{

	class RHI;
	class RenderScene;
	class RenderSource;

	class RenderSystem
	{

	public:
		RenderSystem() = default;
		~RenderSystem();


		void initialize();
		void tick(float delta_time);
		void clear();








	private:

		Ref<RHI>			m_rhi;
		Ref<RenderScene>	m_sceneSystem;
		Ref<RenderSource>	m_renderSource



	};






}