#include <GLCore.h>
#include "ShadowMapLayer.h"

using namespace GLCore;

void Application::CreateApplication()
{
	m_spApplication = Ref<Application>(new Application("ShadowMap", 1280, 720, 4));;

	m_spApplication->Init();

	auto shadowmap_layer = CreateRef<ShadowMapLayer>();

	m_spApplication->PushLayer(shadowmap_layer);
}


int main()
{
	Application::CreateApplication();

	auto app = Application::GetApplication();

	app->Run();
}