#include "PSPlatform/Windows/Systemclass.h"
#include "PSMath/PSMath.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	std::cout << std::powf(2.0, 10.0) << std::endl;
	std::cout << PSMath::fastPow(2.0, 10.0) << std::endl;
	std::cout << PSMath::fastPrecisePow(2.0, 10.0) << std::endl;

#if 0
	std::unique_ptr<Systemclass> System(new Systemclass());
	bool result = false;

	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	System->Shutdown();
#endif

#ifdef _DEBUG
#ifdef _WIN64
	system("PAUSE");
#endif
#endif
	return 0;
}