#include <GLCore.h>
#include "PRTLayer.h"

using namespace GLCore;

void Application::CreateApplication()
{
	m_spApplication = Ref<Application>(new Application("PRT", 1280, 720, 4));;

	m_spApplication->Init();

	auto shadowmap_layer = CreateRef<PRTLayer>();

	m_spApplication->PushLayer(shadowmap_layer);
}


int main()
{
	Application::CreateApplication();

	auto app = Application::GetApplication();

	app->Run();
}