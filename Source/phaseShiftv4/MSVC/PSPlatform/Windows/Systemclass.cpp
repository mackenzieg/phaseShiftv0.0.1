#include "Systemclass.h"

#define WindowWidth 800
#define WindowHeight 480

Systemclass::Systemclass()
{
	m_OpenGL = nullptr;
	m_Input = nullptr;
	m_Graphics = nullptr;
	m_applicationName = nullptr;
	m_hinstance = nullptr;
	m_hwnd = nullptr;
}

Systemclass::Systemclass(const Systemclass&) : Systemclass()
{
}

Systemclass::~Systemclass()
{
}

bool Systemclass::Initialize()
{
	__int16 screenWidth, screenHeight;
	bool result;

#ifdef _DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	m_OpenGL = new OpenGLClass();
	if (!m_OpenGL)
	{
		return false;
	}
	result = InitializeWindows(m_OpenGL, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(m_hwnd, "Could not Initialize the Window.", "Error", MB_OK);
		return false;
	}

	m_Input = new InputClass();
	if (!m_Input)
	{
		return false;
	}

	m_Input->Initialize();

	m_Graphics = new GraphicClass();
	if (!m_Graphics)
	{
		return false;
	}

	result = m_Graphics->Initialize(m_OpenGL, m_hwnd);
	if (!result)
	{
		return false;
	}
	return true;
}

void Systemclass::Shutdown()
{
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = nullptr;
	}
	if (m_Input)
	{
		delete m_Input;
		m_Input = nullptr;
	}
	if (m_OpenGL)
	{
		m_OpenGL->Shutdown(m_hwnd);
		delete m_OpenGL;
		m_OpenGL = nullptr;
	}
}

void Systemclass::Run() const
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	bool done = false;

	LARGE_INTEGER perfFreq;
	LARGE_INTEGER currentTime;
	LARGE_INTEGER prevTime;

	double fps;
	double difference;
	double timeDelta;

	QueryPerformanceFrequency(&perfFreq);

	float frequency = 1.0f / perfFreq.QuadPart;

	QueryPerformanceCounter(&prevTime);
	while (!done)
	{
		QueryPerformanceCounter(&currentTime);
		difference = currentTime.QuadPart - prevTime.QuadPart;
		timeDelta = difference * frequency;
		fps = 1 / static_cast<double>((difference / perfFreq.QuadPart));

		std::cerr << "fps: " << fps << "   " << "deltaTime: " << timeDelta << std::endl;

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		Update(timeDelta);
		if (Frame() == false)
		{
			done = true;
		}
		prevTime = currentTime;
	}
}

bool Systemclass::Frame() const
{
	bool result;

	if (m_Input->isKeyDown(VK_ESCAPE))
	{
		return false;
	}

	result = m_Graphics->Frame();
	if (!result)
	{
		return false;
	}
	return true;
}

bool Systemclass::Update(double dt) const
{
	return true;
}

LRESULT Systemclass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_KEYDOWN:
		{
			m_Input->KeyDown(static_cast<unsigned int>(wparam));
			return 0;
		}
	case WM_KEYUP:
		{
			m_Input->KeyUp(static_cast<unsigned int>(wparam));
			return 0;
		}
	default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

bool Systemclass::InitializeWindows(OpenGLClass* OpenGL, __int16& screenWidth, __int16& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	__int16 posX, posY;
	bool result;

	ApplicationHandle = this;
	m_hinstance = GetModuleHandle(nullptr);
	m_applicationName = "phaseShiftv3";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_POPUP, 0, 0, 640, 480, nullptr, nullptr, m_hinstance, nullptr);
	if (m_hwnd == nullptr)
	{
		return false;
	}

	ShowWindow(m_hwnd, SW_HIDE);

	result = OpenGL->InitializeExtensions(m_hwnd);
	if (!result)
	{
		MessageBox(m_hwnd, "Could not initialize the OpenGL extensions.", "Error", MB_OK);
		return false;
	}

	DestroyWindow(m_hwnd);
	m_hwnd = nullptr;

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN)
	// ReSharper disable CppUnreachableCode
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = static_cast<unsigned long>(screenWidth);
		dmScreenSettings.dmPelsHeight = static_cast<unsigned long>(screenHeight);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	}
	// ReSharper restore CppUnreachableCode
	else
	{
		screenWidth = WindowWidth;
		screenHeight = WindowHeight;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_POPUP, posX, posY, screenWidth, screenHeight, nullptr, nullptr, m_hinstance, nullptr);
	if (m_hwnd == nullptr)
	{
		return false;
	}

	result = m_OpenGL->InitializeOpenGL(m_hwnd, screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);
	if (!result)
	{
		MessageBox(m_hwnd, "Could not initialize OpenGL, check if video card supports OpenGL 4.0.", "Error", MB_OK);
		return false;
	}

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(false);

	return true;
}

void Systemclass::ShutdownWindows()
{
	ShowCursor(true);

	if (FULL_SCREEN)
	// ReSharper disable CppUnreachableCode
	{
		ChangeDisplaySettings(nullptr, 0);
	}
	// ReSharper restore CppUnreachableCode

	DestroyWindow(m_hwnd);
	m_hwnd = nullptr;

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = nullptr;

	ApplicationHandle = nullptr;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}

