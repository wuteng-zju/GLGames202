#include <GLCore.h>
#include "KullaContyBRDFLayer.h"

using namespace GLCore;

void Application::CreateApplication()
{
	m_spApplication = Ref<Application>(new Application("KullaContyBRDF", 1280, 720, 4));;

	m_spApplication->Init();

	auto shadowmap_layer = CreateRef<KullaContyBRDFLayer>();

	m_spApplication->PushLayer(shadowmap_layer);
}


int main()
{
	Application::CreateApplication();

	auto app = Application::GetApplication();

	app->Run();
}