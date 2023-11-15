#include "EditorLayer.h"



#include <Engine/Render/RenderCommand.h>
#include <Engine/Render/Render.h>
#include <Platform/OpenGL/Graphics/OpenGLShader.h>

#include <imgui.h>

#include <Engine/Framework/Component/Component/Component.h>
#include <Engine/Geo/Geo.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include <Engine/Function/LoadModel/TLoad.h>
namespace BEngine
{

	EditorLayer::EditorLayer()
		:Layer("Editor")
	{
        m_VertexArray = VertexArray::Create();

        Ref<VertexBuffer> vertexBuffer;
        Ref<IndexBuffer> indexBuffer;


        vertexBuffer = (VertexBuffer::Create(boxVertex, boxVertex.size()*sizeof(Vertex)));
        indexBuffer = (IndexBuffer::Create(boxIndex, boxIndex.size()));

        {
            BufferLayout layout =
            {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float3, "a_Normal"},
                {ShaderDataType::Float2, "a_UV"},
                {ShaderDataType::Float3, "a_Tangent"},
                {ShaderDataType::Float3, "a_Bitangent"},
                {ShaderDataType::Int4,   "a_BoneID"},
                {ShaderDataType::Float4, "a_Weight"}
            };

            vertexBuffer->SetLayout(layout);
        }

        m_VertexArray->AddVertexBuffer(vertexBuffer);
        m_VertexArray->SetIndexBuffer(indexBuffer);

        std::string filepath = "D:\\Engine\\BeEngine\\Engine\\Assets\\Shader\\Texture.glsl";

        m_Camera = Camera::Create(CameraType::PerspectiveCamera);

        m_ShaderLibrary = CRef<ShaderLibrary>();
        m_ShaderLibrary->Load(filepath);
        m_Texture2D = Texture2D::Create("D:\\Engine\\BeEngine\\Engine\\Assets\\Textures\\floor_2k.png");
        auto Shader = m_ShaderLibrary->Get("Texture");
        std::dynamic_pointer_cast<OpenGLShader>(Shader)->UploadUniformInt("u_Texture", 0);
	}

	void EditorLayer::OnAttach()
	{

        TLoad("D:/Engine/Geo/Box.obj");
		FramebufferSpecification spec;
		spec.width = 1280;
		spec.height = 720;
		m_Framebuffer = Framebuffer::Create(spec);
        m_Camera->SetPosition({ 0,0,-5 });
;
        m_ActiveScene = CRef<Scene>();
        auto cube = m_ActiveScene->CreateEntity();
        m_ActiveScene->Reg().emplace<TransformComponent>(cube);
        m_ActiveScene->Reg().emplace<CubeTransformComponent>(cube, glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});
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

        //
        m_Camera->Tick(ts);

        m_Texture2D->Bind();
        auto Shader = m_ShaderLibrary->Get("Texture");
        std::dynamic_pointer_cast<OpenGLShader>(Shader)->UploadUniformFloat3("u_Color", m_color);

        Render::Submit(m_VertexArray, Shader);
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
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_color));
        ImGui::SliderFloat("Rotate Speed", &m_Camera->GetRotationSpeed(), 0.0f, 200.0f, "%.0f");
        ImGui::SliderFloat("Move Speed", &m_Camera->GetMovementSpeed(), 0.0f, 200.0f, "%.0f");
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
        ImGui::Begin("Render");
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        if(m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
        {
            m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
            m_ViewportSize = { viewportPanelSize.x,viewportPanelSize.y };

            //m_Camera->
            //m_Camera
        }
        uint32_t textureID = m_Texture2D->GetRenderID();
        uint32_t RenderID = m_Framebuffer->GetColorAttachmentRendererId();
        ImGui::Image((void*)RenderID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 1, 0 }, ImVec2{ 0, 1 });
        ImGui::End();
        ImGui::PopStyleVar();


        ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
        m_Camera->OnEvent(event);
	}

}