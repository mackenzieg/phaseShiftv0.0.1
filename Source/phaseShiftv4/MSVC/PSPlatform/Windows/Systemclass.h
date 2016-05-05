#pragma once

#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>
#include <cstdio>
#include <iostream>

#include "OpenGLClass.h"
#include "InputClass.h"
#include "GraphicClass.h"

class Systemclass
{
public:
	Systemclass();
	Systemclass(const Systemclass&);
	~Systemclass();

	bool Initialize();
	void Shutdown();
	void Run() const;

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame() const;
	bool Update(double) const;
	bool InitializeWindows(OpenGLClass*, __int16&, __int16&);
	void ShutdownWindows();

private:
	LPCSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	OpenGLClass* m_OpenGL;
	InputClass* m_Input;
	GraphicClass* m_Graphics;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static Systemclass* ApplicationHandle = nullptr;

#endif

