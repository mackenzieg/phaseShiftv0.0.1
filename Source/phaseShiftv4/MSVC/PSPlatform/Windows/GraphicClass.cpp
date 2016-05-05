#include "GraphicClass.h"

GraphicClass::GraphicClass()
{
	m_OpenGL = nullptr;
}

GraphicClass::GraphicClass(const GraphicClass&) : GraphicClass()
{
}

GraphicClass::~GraphicClass()
{
}

bool GraphicClass::Initialize(OpenGLClass* OpenGL, HWND hwnd)
{
	m_OpenGL = OpenGL;
	return true;
}

void GraphicClass::Shutdown()
{
	m_OpenGL = nullptr;
}

bool GraphicClass::Frame() const
{
	bool result;

	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicClass::Render() const
{
	m_OpenGL->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);

	m_OpenGL->EndScene();
	return true;
}

