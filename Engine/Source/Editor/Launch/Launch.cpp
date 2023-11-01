#include "Launch/Application.h"
#include "Bear.h"
#include "imgui.h"
#include "glm/glm.hpp"
#include "Engine/Geo/Geo.h"
#include "Engine/Render/Camera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Platform/OpenGL/Graphics/OpenGLShader.h"
#include "Engine/Render/Texture.h"
#include "Engine/Render/Shader.h"


class ExampleLayer : public BEngine::Layer
{
public:

	ExampleLayer()
		:m_CameraPosition(0.f)
	{
		m_VertexArray = BEngine::VertexArray::Create();

		BEngine::Ref<BEngine::VertexBuffer> vertexBuffer;
		BEngine::Ref<BEngine::IndexBuffer> indexBuffer;

		
		vertexBuffer.reset(BEngine::VertexBuffer::Create(BEngine::boxVertex, sizeof(BEngine::boxVertex)));
		indexBuffer.reset(BEngine::IndexBuffer::Create(BEngine::boxIndex, sizeof(BEngine::boxIndex) / sizeof(uint32_t)));

		{
			BEngine::BufferLayout layout =
			{
				{BEngine::ShaderDataType::Float3, "a_Position"},
				{BEngine::ShaderDataType::Float4, "a_Color"},
				{BEngine::ShaderDataType::Float2, "a_UV"}
			};

			vertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string filepath = "D:\\Engine\\BeEngine\\Engine\\Assets\\Shader\\Texture.glsl";

		m_ShaderLibrary->Load(filepath);
		m_Texture2D = BEngine::Texture2D::Create("D:\\Engine\\BeEngine\\Engine\\Assets\\Textures\\floor_2k.png");
		auto Shader = m_ShaderLibrary->Get("Texture");
		std::dynamic_pointer_cast<BEngine::OpenGLShader>(Shader)->UploadUniformInt("u_Texture", 0);
		
		

	}

	void OnUpdate(BEngine::Timestep ts) override
	{
		//BR_CLIENT_TRACE("Delta time : {0}s ({1}ms)", ts.GetSeconds(),ts.GetMilliseconds());
		BEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		BEngine::RenderCommand::Clear();

		BEngine::Render::BeginScene(m_Camera);

		m_Camera->SetPosition({0,0,-5});
		m_Camera->Tick(ts);
		m_Texture2D->Bind();



		auto Shader = m_ShaderLibrary->Get("Texture");
		std::dynamic_pointer_cast<BEngine::OpenGLShader>(Shader)->UploadUniformFloat3("u_Color", m_color);

		BEngine::Render::Submit(m_VertexArray, Shader);
		BEngine::Render::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
		


        static bool p_open = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::Separator();

                if (ImGui::MenuItem("Exit")) BEngine::Application::Get().Close();

                ImGui::EndMenu();
            }


            ImGui::EndMenuBar();
        }

        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_color));
        ImGui::SliderFloat("Rotate Speed", &m_Camera->GetRotationSpeed(), 0.0f, 200.0f, "%.0f");
        ImGui::SliderFloat("Move Speed", &m_Camera->GetMovementSpeed(), 0.0f, 200.0f, "%.0f");
        ImGui::End();

        ImGui::Begin("Image");
        uint32_t textureID = m_Texture2D->GetRenderID();
        ImGui::Image((void*)textureID, ImVec2{ 512,512 });
        ImGui::End();


        ImGui::End();
	}

	void OnEvent(BEngine::Event& event) override
	{
		m_Camera->OnEvent(event);
	}

	bool OnKeyPressedEvent(BEngine::KeyPressedEvent& event)
	{
	}


private:


	
	BEngine::Ref<BEngine::ShaderLibrary> m_ShaderLibrary = std::make_shared<BEngine::ShaderLibrary>();
	BEngine::Ref<BEngine::VertexArray> m_VertexArray;
	BEngine::Ref<BEngine::Texture2D> m_Texture2D;


	BEngine::Ref<BEngine::Camera> m_Camera = BEngine::Camera::Create(BEngine::CameraType::PerspectiveCamera);
	glm::vec3 m_CameraPosition = glm::vec3(0.0,0.0,3.0);
	float m_CameraSpeed = 0.1;
	glm::vec3 m_color = glm::vec3(1.0, 1.0, 1.0);
};


class Launch : public BEngine::Application
{
public:
	Launch(){ 
		PushLayer(new ExampleLayer());
	}
	~Launch() { }

};


BEngine::Application* BEngine::CreateApplication()
{
	return new Launch();
}


/*
void ShowExampleAppDockSpace(bool* p_open)
{
    // READ THIS !!!
    // TL;DR; this demo is more complicated than what most users you would normally use.
    // If we remove all options we are showcasing, this demo would become:
    //     void ShowExampleAppDockSpace()
    //     {
    //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    //     }
    // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
    // In this specific demo, we are not using DockSpaceOverViewport() because:
    // - (1) we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
    // - (2) we allow the host window to have padding (when opt_padding == true)
    // - (3) we expose many flags and need a way to have them visible.
    // - (4) we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport()
    //      in your code, but we don't here because we allow the window to be floating)

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            ImGui::MenuItem("Padding", NULL, &opt_padding);
            ImGui::Separator();

            if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
            if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
            if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
            if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
            ImGui::Separator();

            if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
                *p_open = false;
            ImGui::EndMenu();
        }


        ImGui::EndMenuBar();
    }

    ImGui::End();
}
*/