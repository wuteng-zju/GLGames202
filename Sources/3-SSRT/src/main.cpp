#include <GLCore.h>
#include "SSRTLayer.h"

using namespace GLCore;

void Application::CreateApplication()
{
	m_spApplication = Ref<Application>(new Application("SSRT", 1280, 720, 4));;

	m_spApplication->Init();

	auto shadowmap_layer = CreateRef<SSRTLayer>();

	m_spApplication->PushLayer(shadowmap_layer);
}


int main()
{
	Application::CreateApplication();

	auto app = Application::GetApplication();

	app->Run();
}