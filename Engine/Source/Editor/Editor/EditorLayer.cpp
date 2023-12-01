#include "EditorLayer.h"



#include <Engine/Render/RenderCommand.h>
#include <Engine/Render/Render.h>
#include <Platform/OpenGL/Graphics/OpenGLShader.h>

#include <imgui.h>

#include <Engine/Framework/Component/Component/Component.h>
#include <Engine/Framework/Component/Mesh/MeshComponent.h>
#include <Engine/Geo/Geo.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include <Engine/Function/LoadModel/TLoad.h>
#include <Engine/Function/LoadModel/AssimpLoad.h>
#include <Engine/Render/Shader.h>

namespace BEngine
{

	EditorLayer::EditorLayer()
		:Layer("Editor")
	{

        m_Camera = Camera::Create(CameraType::PerspectiveCamera);


        ShaderLibrary::GetInstance();


	}

	void EditorLayer::OnAttach()
	{


        std::string Checkloadpath = "D:/Engine/Geo/Example/Check.obj";

        Checkmodel = CRef<Model>(Checkloadpath);


		FramebufferSpecification spec;
		spec.width = 1280;
		spec.height = 720;
		m_Framebuffer = Framebuffer::Create(spec);


        m_ActiveScene = CRef<Scene>();

        auto Mesh = m_ActiveScene->CreateEntity("Lion");

        Mesh.AddComponent<MeshTransformComponent> (glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});
        Mesh.AddComponent<ModelComponent>("D:/Engine/Geo/Example/nanosuit.obj");

        m_Entity = Mesh;
        
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(Timestep ts)
	{

        //update scene
        
        
        m_Framebuffer->Bind();
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();
        

        m_ActiveScene->Tick(ts);


        Render::BeginScene(m_Camera);

        
        m_Camera->Tick(ts);


        auto Shader = ShaderLibrary::GetInstance().Get("Checker");
        Checkmodel->Draw(Shader);

        std::dynamic_pointer_cast<OpenGLShader>(Shader)->UploadUniformFloat3("u_Color", m_color);

        Render::EndScene();
        m_Framebuffer->UnBind();



	}

	void EditorLayer::OnImGuiRender()
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
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::Separator();

                if (ImGui::MenuItem("Exit")) Application::Get().Close();

                ImGui::EndMenu();
            }


            ImGui::EndMenuBar();
        }

        ImGui::Begin("Settings");
        ImGui::Separator();
        ImGui::Text("ms: %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Separator();
        ImGui::SliderFloat("Rotate Speed", &m_Camera->GetRotationSpeed(), 0.0f, 200.0f, "%.0f");
        ImGui::SliderFloat("Move Speed", &m_Camera->GetMovementSpeed(), 0.0f, 800.0f, "%.0f");
        ImGui::Text("pos: %.3f,%.3f,%.3f",m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
        ImGui::Text("front: %.3f,%.3f,%.3f",m_Camera->GetCameraFront().x, m_Camera->GetCameraFront().y, m_Camera->GetCameraFront().z);
        ImGui::Text("up: %.3f,%.3f,%.3f",m_Camera->GetCameraUp().x, m_Camera->GetCameraUp().y, m_Camera->GetCameraUp().z);
        ImGui::Text("right: %.3f,%.3f,%.3f",m_Camera->GetCameraRight().x, m_Camera->GetCameraRight().y, m_Camera->GetCameraRight().z);
        ImGui::Text("yaw_pitch: %.3f,%.3f,%.3f",m_Camera->GetCameraYawPitch().x, m_Camera->GetCameraYawPitch().y, m_Camera->GetCameraYawPitch().z);
        ImGui::Separator();
        auto& tag = m_Entity.GetComponent<TagComponent>().Tag;
        ImGui::Text("%s", tag.c_str());
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
        ImGui::Begin("Render");
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        if(m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
        {
            m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
            m_ViewportSize = { viewportPanelSize.x,viewportPanelSize.y };

            m_Camera->ResetProjection((uint32_t)viewportPanelSize.x / (uint32_t)viewportPanelSize.y);
            //m_Camera
        }
        //uint32_t textureID = m_Texture2D->GetRenderID();
        uint32_t RenderID = m_Framebuffer->GetColorAttachmentRendererId();
        ImGui::Image((void*)RenderID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();
        ImGui::PopStyleVar();


        ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
        m_Camera->OnEvent(event);
	}

}