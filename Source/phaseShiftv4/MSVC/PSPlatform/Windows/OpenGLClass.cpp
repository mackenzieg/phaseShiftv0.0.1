#include "OpenGLClass.h"
#include <string>

// ReSharper disable once CppPossiblyUninitializedMember
OpenGLClass::OpenGLClass()
{
	m_deviceContext = nullptr;
	m_renderingContext = nullptr;
}

// ReSharper disable once CppPossiblyUninitializedMember
OpenGLClass::OpenGLClass(const OpenGLClass&) : OpenGLClass()
{
}

OpenGLClass::~OpenGLClass()
{
}

bool OpenGLClass::InitializeExtensions(HWND hwnd)
{
	HDC deviceContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error = 1;
	HGLRC renderContext;
	bool result;

	deviceContext = GetDC(hwnd);
	if (!deviceContext)
	{
		return false;
	}

	error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if (error != 1)
	{
		return false;
	}

	renderContext = wglCreateContext(deviceContext);
	if (!renderContext)
	{
		return false;
	}

	error = wglMakeCurrent(deviceContext, renderContext);
	if (error != 1)
	{
		return false;
	}

	result = LoadExtensionList();
	if (!result)
	{
		return false;
	}

	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(renderContext);
	// ReSharper disable once CppAssignedValueIsNeverUsed
	renderContext = nullptr;

	ReleaseDC(hwnd, deviceContext);
	// ReSharper disable once CppAssignedValueIsNeverUsed
	deviceContext = nullptr;

	return true;
}

bool OpenGLClass::InitializeOpenGL(HWND hwnd, __int16 screenWidth, __int16 screenHeight, float screenDepth, float screenNear, bool vsync)
{
	int attributeListInt[19];
	int pixelFormat[1];
	unsigned int formatCount;
	int result;
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	int attributeList[5];
	const char *versionString, *versionMajorString, *versionMinorString, *vendorString, *rendererString;

	m_deviceContext = GetDC(hwnd);
	if (!m_deviceContext)
	{
		return false;
	}

	attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;

	attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;

	attributeListInt[4] = WGL_ACCELERATION_ARB;
	attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;

	attributeListInt[6] = WGL_COLOR_BITS_ARB;
	attributeListInt[7] = 32;

	attributeListInt[8] = WGL_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;

	attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;

	attributeListInt[12] = WGL_SWAP_METHOD_ARB;
	attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;

	attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
	attributeListInt[15] = WGL_TYPE_RGBA_ARB;

	attributeListInt[16] = WGL_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;

	attributeListInt[18] = 0;

	result = wglChoosePixelFormatARB(m_deviceContext, attributeListInt, nullptr, 1, pixelFormat, &formatCount);
	if (result != 1)
	{
		return false;
	}

	result = SetPixelFormat(m_deviceContext, pixelFormat[0], &pixelFormatDescriptor);
	if (result != 1)
	{
		return false;
	}

	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = OPENGL_CONTEXT_MAJOR;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = OPENGL_CONTEXT_MINOR;

	attributeList[4] = 0;

	m_renderingContext = wglCreateContextAttribsARB(m_deviceContext, nullptr, attributeList);
	if (m_renderingContext == nullptr)
	{
		return false;
	}

	result = wglMakeCurrent(m_deviceContext, m_renderingContext);
	if (result != 1)
	{
		return false;
	}

	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	versionString = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	versionMajorString = std::to_string(OPENGL_CONTEXT_MAJOR).c_str();
	versionMinorString = std::to_string(OPENGL_CONTEXT_MINOR).c_str();
	vendorString = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	rendererString = reinterpret_cast<const char*>(glGetString(GL_RENDERER));

	strcpy_s(m_videoCardDescription, versionString);
	strcpy_s(m_videoCardDescription, " - ");
	strcpy_s(m_videoCardDescription, vendorString);
	strcat_s(m_videoCardDescription, " - ");
	strcat_s(m_videoCardDescription, rendererString);

	std::cerr << m_videoCardDescription << std::endl;

	if (vsync)
	{
		result = wglSwapIntervalEXT(1);
	}
	else
	{
		result = wglSwapIntervalEXT(0);
	}

	if (result != 1)
	{
		return false;
	}

	return true;
}

void OpenGLClass::Shutdown(HWND hwnd)
{
	if (m_renderingContext)
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(m_renderingContext);
		m_renderingContext = nullptr;
	}

	if (m_deviceContext)
	{
		ReleaseDC(hwnd, m_deviceContext);
		m_deviceContext = nullptr;
	}

	return;
}

bool OpenGLClass::IsExtensionSupported(const char* name) const
{
	GLint n = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	for (GLint i = 0; i < n; i++)
	{
		const char* extension = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));
		if (!strcmp(name, extension))
		{
			return true;
		}
	}
	return false;
}

void OpenGLClass::BeginScene(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLClass::EndScene() const
{
	SwapBuffers(m_deviceContext);
}

void OpenGLClass::GetVideoCardInfo(char* cardName) const
{
	strcpy_s(cardName, 128, m_videoCardDescription);
	std::cerr << m_videoCardDescription << std::endl;
}

bool OpenGLClass::LoadExtensionList()
{
	wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARB>(wglGetProcAddress("wglChoosePixelFormatARB"));
	if (!wglChoosePixelFormatARB)
	{
		GLEXTERROR();
		return false;
	}

	wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARB>(wglGetProcAddress("wglCreateContextAttribsARB"));
	if (!wglCreateContextAttribsARB)
	{
		GLEXTERROR();
		return false;
	}

	wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXT>(wglGetProcAddress("wglSwapIntervalEXT"));
	if (!wglSwapIntervalEXT)
	{
		GLEXTERROR();
		return false;
	}

	glAttachShader = reinterpret_cast<PFNGLATTACHSHADER>(wglGetProcAddress("glAttachShader"));
	if (!glAttachShader)
	{
		GLEXTERROR();
		return false;
	}

	glBindBuffer = reinterpret_cast<PFNGLBINDBUFFER>(wglGetProcAddress("glBindBuffer"));
	if (!glBindBuffer)
	{
		GLEXTERROR();
		return false;
	}

	glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAY>(wglGetProcAddress("glBindVertexArray"));
	if (!glBindVertexArray)
	{
		GLEXTERROR();
		return false;
	}

	glBufferData = reinterpret_cast<PFNGLBUFFERDATA>(wglGetProcAddress("glBufferData"));
	if (!glBufferData)
	{
		GLEXTERROR();
		return false;
	}

	glCompileShader = reinterpret_cast<PFNGLCOMPILESHADER>(wglGetProcAddress("glCompileShader"));
	if (!glCompileShader)
	{
		GLEXTERROR();
		return false;
	}

	glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAM>(wglGetProcAddress("glCreateProgram"));
	if (!glCreateProgram)
	{
		GLEXTERROR();
		return false;
	}

	glCreateShader = reinterpret_cast<PFNGLCREATESHADER>(wglGetProcAddress("glCreateShader"));
	if (!glCreateShader)
	{
		GLEXTERROR();
		return false;
	}

	glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERS>(wglGetProcAddress("glDeleteBuffers"));
	if (!glDeleteBuffers)
	{
		GLEXTERROR();
		return false;
	}

	glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAM>(wglGetProcAddress("glDeleteProgram"));
	if (!glDeleteProgram)
	{
		GLEXTERROR();
		return false;
	}

	glDeleteShader = reinterpret_cast<PFNGLDELETESHADER>(wglGetProcAddress("glDeleteShader"));
	if (!glDeleteShader)
	{
		GLEXTERROR();
		return false;
	}

	glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYS>(wglGetProcAddress("glDeleteVertexArrays"));
	if (!glDeleteVertexArrays)
	{
		GLEXTERROR();
		return false;
	}

	glDetachShader = reinterpret_cast<PFNGLDETACHSHADER>(wglGetProcAddress("glDetachShader"));
	if (!glDetachShader)
	{
		GLEXTERROR();
		return false;
	}

	glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAY>(wglGetProcAddress("glEnableVertexAttribArray"));
	if (!glEnableVertexAttribArray)
	{
		GLEXTERROR();
		return false;
	}

	glGenBuffers = reinterpret_cast<PFNGLGENBUFFERS>(wglGetProcAddress("glGenBuffers"));
	if (!glGenBuffers)
	{
		GLEXTERROR();
		return false;
	}

	glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYS>(wglGetProcAddress("glGenVertexArrays"));
	if (!glGenVertexArrays)
	{
		GLEXTERROR();
		return false;
	}

	glGetAttribLocation = reinterpret_cast<PFNGLGETATTRIBLOCATION>(wglGetProcAddress("glGetAttribLocation"));
	if (!glGetAttribLocation)
	{
		GLEXTERROR();
		return false;
	}

	glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOG>(wglGetProcAddress("glGetProgramInfoLog"));
	if (!glGetProgramInfoLog)
	{
		GLEXTERROR();
		return false;
	}

	glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIV>(wglGetProcAddress("glGetProgramiv"));
	if (!glGetProgramiv)
	{
		GLEXTERROR();
		return false;
	}

	glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOG>(wglGetProcAddress("glGetShaderInfoLog"));
	if (!glGetShaderInfoLog)
	{
		GLEXTERROR();
		return false;
	}

	glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIV>(wglGetProcAddress("glGetShaderiv"));
	if (!glGetShaderiv)
	{
		GLEXTERROR();
		return false;
	}

	glGetStringi = reinterpret_cast<PFNGLGETSTRINGI>(wglGetProcAddress("glGetStringi"));
	if (!glGetStringi)
	{
		GLEXTERROR();
		return false;
	}

	glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAM>(wglGetProcAddress("glLinkProgram"));
	if (!glLinkProgram)
	{
		GLEXTERROR();
		return false;
	}

	glShaderSource = reinterpret_cast<PFNGLSHADERSOURCE>(wglGetProcAddress("glShaderSource"));
	if (!glShaderSource)
	{
		GLEXTERROR();
		return false;
	}

	glUseProgram = reinterpret_cast<PFNGLUSEPROGRAM>(wglGetProcAddress("glUseProgram"));
	if (!glUseProgram)
	{
		GLEXTERROR();
		return false;
	}

	glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTER>(wglGetProcAddress("glVertexAttribPointer"));
	if (!glVertexAttribPointer)
	{
		GLEXTERROR();
		return false;
	}

	glBindAttribLocation = reinterpret_cast<PFNGLBINDATTRIBLOCATION>(wglGetProcAddress("glBindAttribLocation"));
	if (!glBindAttribLocation)
	{
		GLEXTERROR();
		return false;
	}

	glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATION>(wglGetProcAddress("glGetUniformLocation"));
	if (!glGetUniformLocation)
	{
		GLEXTERROR();
		return false;
	}

	glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTURE>(wglGetProcAddress("glActiveTexture"));
	if (!glActiveTexture)
	{
		GLEXTERROR();
		return false;
	}

	glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAP>(wglGetProcAddress("glGenerateMipmap"));
	if (!glGenerateMipmap)
	{
		GLEXTERROR();
		return false;
	}

	glDisableVertexAttribArray = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAY>(wglGetProcAddress("glDisableVertexAttribArray"));
	if (!glDisableVertexAttribArray)
	{
		GLEXTERROR();
		return false;
	}

	glUniform1i = reinterpret_cast<PFNGLUNIFORM1I>(wglGetProcAddress("glUniform1i"));
	if (!glUniform1i)
	{
		GLEXTERROR();
		return false;
	}

	glUniform1iv = reinterpret_cast<PFNGLUNIFORM1IV>(wglGetProcAddress("glUniform1iv"));
	if (!glUniform1iv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform1ui = reinterpret_cast<PFNGLUNIFORM1UI>(wglGetProcAddress("glUniform1ui"));
	if (!glUniform1ui)
	{
		GLEXTERROR();
		return false;
	}

	glUniform1uiv = reinterpret_cast<PFNGLUNIFORM1UIV>(wglGetProcAddress("glUniform1uiv"));
	if (!glUniform1uiv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform1f = reinterpret_cast<PFNGLUNIFORM1F>(wglGetProcAddress("glUniform1f"));
	if (!glUniform1f)
	{
		GLEXTERROR();
		return false;
	}

	glUniform1fv = reinterpret_cast<PFNGLUNIFORM1FV>(wglGetProcAddress("glUniform1fv"));
	if (!glUniform1fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform2i = reinterpret_cast<PFNGLUNIFORM2I>(wglGetProcAddress("glUniform2i"));
	if (!glUniform2i)
	{
		GLEXTERROR();
		return false;
	}

	glUniform2iv = reinterpret_cast<PFNGLUNIFORM2IV>(wglGetProcAddress("glUniform2iv"));
	if (!glUniform2iv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform2ui = reinterpret_cast<PFNGLUNIFORM2UI>(wglGetProcAddress("glUniform2ui"));
	if (!glUniform2ui)
	{
		GLEXTERROR();
		return false;
	}

	glUniform2uiv = reinterpret_cast<PFNGLUNIFORM2UIV>(wglGetProcAddress("glUniform2uiv"));
	if (!glUniform2uiv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform2f = reinterpret_cast<PFNGLUNIFORM2F>(wglGetProcAddress("glUniform2f"));
	if (!glUniform2f)
	{
		GLEXTERROR();
		return false;
	}

	glUniform2fv = reinterpret_cast<PFNGLUNIFORM2FV>(wglGetProcAddress("glUniform2fv"));
	if (!glUniform2fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform3i = reinterpret_cast<PFNGLUNIFORM3I>(wglGetProcAddress("glUniform3i"));
	if (!glUniform3i)
	{
		GLEXTERROR();
		return false;
	}

	glUniform3iv = reinterpret_cast<PFNGLUNIFORM3IV>(wglGetProcAddress("glUniform3iv"));
	if (!glUniform3iv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform3ui = reinterpret_cast<PFNGLUNIFORM3UI>(wglGetProcAddress("glUniform3ui"));
	if (!glUniform3ui)
	{
		GLEXTERROR();
		return false;
	}

	glUniform3uiv = reinterpret_cast<PFNGLUNIFORM3UIV>(wglGetProcAddress("glUniform3uiv"));
	if (!glUniform3uiv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform3f = reinterpret_cast<PFNGLUNIFORM3F>(wglGetProcAddress("glUniform3f"));
	if (!glUniform3f)
	{
		GLEXTERROR();
		return false;
	}

	glUniform3fv = reinterpret_cast<PFNGLUNIFORM3FV>(wglGetProcAddress("glUniform3fv"));
	if (!glUniform3fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform4i = reinterpret_cast<PFNGLUNIFORM4I>(wglGetProcAddress("glUniform4i"));
	if (!glUniform4i)
	{
		GLEXTERROR();
		return false;
	}

	glUniform4iv = reinterpret_cast<PFNGLUNIFORM4IV>(wglGetProcAddress("glUniform4iv"));
	if (!glUniform4iv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform4ui = reinterpret_cast<PFNGLUNIFORM4UI>(wglGetProcAddress("glUniform4ui"));
	if (!glUniform4ui)
	{
		GLEXTERROR();
		return false;
	}

	glUniform4uiv = reinterpret_cast<PFNGLUNIFORM4UIV>(wglGetProcAddress("glUniform4uiv"));
	if (!glUniform4uiv)
	{
		GLEXTERROR();
		return false;
	}

	glUniform4f = reinterpret_cast<PFNGLUNIFORM4F>(wglGetProcAddress("glUniform4f"));
	if (!glUniform4f)
	{
		GLEXTERROR();
		return false;
	}

	glUniform4fv = reinterpret_cast<PFNGLUNIFORM4FV>(wglGetProcAddress("glUniform4fv"));
	if (!glUniform4fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniformMatrix2fv = reinterpret_cast<PFNGLUNIFORMMATRIX2FV>(wglGetProcAddress("glUniformMatrix2fv"));
	if (!glUniformMatrix2fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniformMatrix3fv = reinterpret_cast<PFNGLUNIFORMMATRIX3FV>(wglGetProcAddress("glUniformMatrix3fv"));
	if (!glUniformMatrix3fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FV>(wglGetProcAddress("glUniformMatrix4fv"));
	if (!glUniformMatrix4fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniformMatrix2x3fv = reinterpret_cast<PFNGLUNIFORMMATRIX2X3FV>(wglGetProcAddress("glUniformMatrix2x3fv"));
	if (!glUniformMatrix2x3fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniformMatrix3x2fv = reinterpret_cast<PFNGLUNIFORMMATRIX3X2FV>(wglGetProcAddress("glUniformMatrix3x2fv"));
	if (!glUniformMatrix3x2fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniformMatrix2x4fv = reinterpret_cast<PFNGLUNIFORMMATRIX2X4FV>(wglGetProcAddress("glUniformMatrix2x4fv"));
	if (!glUniformMatrix2x4fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniformMatrix4x2fv = reinterpret_cast<PFNGLUNIFORMMATRIX4X2FV>(wglGetProcAddress("glUniformMatrix4x2fv"));
	if (!glUniformMatrix4x2fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniformMatrix3x4fv = reinterpret_cast<PFNGLUNIFORMMATRIX3X4FV>(wglGetProcAddress("glUniformMatrix3x4fv"));
	if (!glUniformMatrix3x4fv)
	{
		GLEXTERROR();
		return false;
	}

	glUniformMatrix4x3fv = reinterpret_cast<PFNGLUNIFORMMATRIX4X3FV>(wglGetProcAddress("glUniformMatrix4x3fv"));
	if (!glUniformMatrix4x3fv)
	{
		GLEXTERROR();
		return false;
	}

	GLint max = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &max);

	for (GLint i = 0; i < max; i++)
	{
		std::cout << glGetStringi(GL_EXTENSIONS, i) << std::endl;
	}

	return true;
}

