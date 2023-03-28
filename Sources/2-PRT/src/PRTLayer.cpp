#include "PRTLayer.h"

#define GL_GLEXT_PROTOTYPES
#include "GL/gl3w.h"

PRTLayer::PRTLayer() :
	Layer("SandBox"),
	m_vec4Color(glm::vec4(0.2f, 0.3f, 0.8f, 1.0f))
{
}

PRTLayer::~PRTLayer()
{

}

void PRTLayer::OnAttach()
{
	Render::Init();

	m_spOrthoGraphicCameraController = CreateRef<OrthoGraphicCameraController>
		(Application::GetApplication()->GetWindowWidth(), Application::GetApplication()->GetWindowHeight());

	// Color
	m_spColorArray = VertexArray::Create();

	// VBO
	std::vector<float> veColorVertex{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};
	std::vector<VertexBufferElement> vecColorBufferElement
	{
		{ VertexDataType::Float3 },
	};
	auto spColorVertexBufferLayout = CreateRef<VertexBufferLayout>(vecColorBufferElement);
	auto spColorVertexBuffer = VertexBuffer::Create(veColorVertex, spColorVertexBufferLayout);
	m_spColorArray->AddVertexBuffer(spColorVertexBuffer);

	// EBO
	std::vector<unsigned int> vecIndex{
		0, 1, 2, 2, 3, 0
	};
	auto spIndexBuffer = IndexBuffer::Create(vecIndex);
	m_spColorArray->SetIndexBuffer(spIndexBuffer);

	// Shader
	std::vector<ShaderInfo> vecColorShaderInfo
	{
		{ShaderType::VETEX_SHADER,"assets/shaders/color.vs"},
		{ShaderType::FRAGMENT_SHADER,"assets/shaders/color.fs"}
	};
	m_spColorShader = Shader::Create(vecColorShaderInfo);
}

void PRTLayer::OnDetach()
{
}

void PRTLayer::OnUpdate(const TimeStep& ts)
{
	m_spOrthoGraphicCameraController->OnUpdate(ts);

	Render::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Render::Clear();

	m_spColorShader->Bind();
	m_spColorShader->SetFloat4("Color", m_vec4Color);
	glm::mat4 mat4Scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	glm::vec3 vec3Pos(0.11f, 0.11f, -0.1f);
	glm::mat4 mat4Transform = glm::translate(glm::mat4(1.0f), vec3Pos) * mat4Scale;

	m_spColorShader->Bind();
	// mvp¾ØÕó
	m_spColorShader->SetMat4("ViewProjection", m_spOrthoGraphicCameraController->GetCamera()->GetViewProjectionMatrix());
	m_spColorShader->SetMat4("Transform", mat4Transform);

	// °ó¶¨vertex array
	m_spColorArray->Bind();

	unsigned int uiIndexCount = m_spColorArray->GetIndexBuffer()->GetIndex().size();

	Render::DrawTriangles(uiIndexCount);
}

void PRTLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_vec4Color));
	ImGui::End();
}

void PRTLayer::OnEvent(Event& event)
{
	m_spOrthoGraphicCameraController->OnEvent(event);
}
