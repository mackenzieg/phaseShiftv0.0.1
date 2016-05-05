#pragma once

#ifndef _OPENGLCLASS_H_
#define _OPENGLCLASS_H_

#pragma comment(lib, "opengl32.lib")

#include <windows.h>
#include <iostream>
#include "../Lib/GL.h"
#include "../Lib/glext.h"

#define OPENGL_CONTEXT_MAJOR 4
#define OPENGL_CONTEXT_MINOR 0

#define GLEXTERROR() \
{	\
	std::cerr << "Error Initializing OpenGL Procedure at : " << __FILE__ << " function : " << __FUNCTIONW__ << " line : " << __LINE__ <<  std::endl; \
} \

#define WGL_DRAW_TO_WINDOW_ARB		   0x2001
#define WGL_ACCELERATION_ARB		   0x2003
#define WGL_SWAP_METHOD_ARB			   0x2007
#define WGL_SUPPORT_OPENGL_ARB         0x2010
#define WGL_DOUBLE_BUFFER_ARB          0x2011
#define WGL_PIXEL_TYPE_ARB             0x2013
#define WGL_COLOR_BITS_ARB             0x2014
#define WGL_DEPTH_BITS_ARB             0x2022
#define WGL_STENCIL_BITS_ARB           0x2023
#define WGL_FULL_ACCELERATION_ARB      0x2027
#define WGL_SWAP_EXCHANGE_ARB          0x2028
#define WGL_TYPE_RGBA_ARB              0x202B
#define WGL_CONTEXT_MAJOR_VERSION_ARB  0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB  0x2092
#define GL_ARRAY_BUFFER                0x8892
#define GL_STATIC_DRAW                 0x88E4
#define GL_FRAGMENT_SHADER             0x8B30
#define GL_VERTEX_SHADER               0x8B31
#define GL_GEOMETRY_SHADER			   0x8DD9
#define GL_COMPILE_STATUS              0x8B81
#define GL_LINK_STATUS                 0x8B82
#define GL_INFO_LOG_LENGTH             0x8B84
#define GL_TEXTURE0                    0x84C0
#define GL_BGRA                        0x80E1
#define GL_ELEMENT_ARRAY_BUFFER        0x8893

#define TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARB)(HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);
typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARB)(HDC hDC, HGLRC hShareContext, const int* attribList);
typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXT)(int interval);
typedef void (APIENTRY * PFNGLATTACHSHADER)(GLuint program, GLuint shader);
typedef void (APIENTRY * PFNGLBINDBUFFER)(GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLBINDVERTEXARRAY)(GLuint array);
typedef void (APIENTRY * PFNGLBUFFERDATA)(GLenum target, ptrdiff_t size, const GLvoid* data, GLenum usage);
typedef void (APIENTRY * PFNGLCOMPILESHADER)(GLuint shader);
typedef GLuint (APIENTRY * PFNGLCREATEPROGRAM)(void);
typedef GLuint (APIENTRY * PFNGLCREATESHADER)(GLenum type);
typedef void (APIENTRY * PFNGLDELETEBUFFERS)(GLsizei n, const GLuint* buffers);
typedef void (APIENTRY * PFNGLDELETEPROGRAM)(GLuint program);
typedef void (APIENTRY * PFNGLDELETESHADER)(GLuint shader);
typedef void (APIENTRY * PFNGLDELETEVERTEXARRAYS)(GLsizei n, const GLuint* arrays);
typedef void (APIENTRY * PFNGLDETACHSHADER)(GLuint program, GLuint shader);
typedef void (APIENTRY * PFNGLENABLEVERTEXATTRIBARRAY)(GLuint index);
typedef void (APIENTRY * PFNGLGENBUFFERS)(GLsizei n, GLuint* buffers);
typedef void (APIENTRY * PFNGLGENVERTEXARRAYS)(GLsizei n, GLuint* arrays);
typedef GLint (APIENTRY * PFNGLGETATTRIBLOCATION)(GLuint program, const char* name);
typedef void (APIENTRY * PFNGLGETINTEGERV)(GLenum pname, GLint* params);
typedef void (APIENTRY * PFNGLGETPROGRAMINFOLOG)(GLuint program, GLsizei bufSize, GLsizei* length, char* infoLog);
typedef void (APIENTRY * PFNGLGETPROGRAMIV)(GLuint program, GLenum pname, GLint* params);
typedef void (APIENTRY * PFNGLGETSHADERINFOLOG)(GLuint shader, GLsizei bufSize, GLsizei* length, char* infoLog);
typedef void (APIENTRY * PFNGLGETSHADERIV)(GLuint shader, GLenum pname, GLint* params);
typedef const GLubyte*(APIENTRY * PFNGLGETSTRINGI)(GLenum name, GLuint index);
typedef void (APIENTRY * PFNGLLINKPROGRAM)(GLuint program);
typedef void (APIENTRY * PFNGLSHADERSOURCE)(GLuint shader, GLsizei count, const char* * string, const GLint* length);
typedef void (APIENTRY * PFNGLUSEPROGRAM)(GLuint program);
typedef void (APIENTRY * PFNGLVERTEXATTRIBPOINTER)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
typedef void (APIENTRY * PFNGLBINDATTRIBLOCATION)(GLuint program, GLuint index, const char* name);
typedef GLint (APIENTRY * PFNGLGETUNIFORMLOCATION)(GLuint program, const char* name);
typedef void (APIENTRY * PFNGLACTIVETEXTURE)(GLenum texture);
typedef void (APIENTRY * PFNGLGENERATEMIPMAP)(GLenum target);
typedef void (APIENTRY * PFNGLDISABLEVERTEXATTRIBARRAY)(GLuint index);

typedef void (APIENTRY * PFNGLUNIFORM1I)(GLint location, GLint v0);
typedef void (APIENTRY * PFNGLUNIFORM1IV)(GLint location, GLsizei count, const GLint* value);
typedef void (APIENTRY * PFNGLUNIFORM1UI)(GLint location, GLuint v0);
typedef void (APIENTRY * PFNGLUNIFORM1UIV)(GLint location, GLsizei count, const GLuint* value);
typedef void (APIENTRY * PFNGLUNIFORM1F)(GLint location, GLfloat v0);
typedef void (APIENTRY * PFNGLUNIFORM1FV)(GLint location, GLsizei count, const GLfloat* value);

typedef void (APIENTRY * PFNGLUNIFORM2I)(GLint location, GLint v0, GLint v1);
typedef void (APIENTRY * PFNGLUNIFORM2IV)(GLint location, GLsizei count, const GLint* value);
typedef void (APIENTRY * PFNGLUNIFORM2UI)(GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRY * PFNGLUNIFORM2UIV)(GLint location, GLsizei count, const GLuint* value);
typedef void (APIENTRY * PFNGLUNIFORM2F)(GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRY * PFNGLUNIFORM2FV)(GLint location, GLsizei count, const GLfloat* value);

typedef void (APIENTRY * PFNGLUNIFORM3I)(GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRY * PFNGLUNIFORM3IV)(GLint location, GLsizei count, const GLint* value);
typedef void (APIENTRY * PFNGLUNIFORM3UI)(GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRY * PFNGLUNIFORM3UIV)(GLint location, GLsizei count, const GLuint* value);
typedef void (APIENTRY * PFNGLUNIFORM3F)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRY * PFNGLUNIFORM3FV)(GLint location, GLsizei count, const GLfloat* value);

typedef void (APIENTRY * PFNGLUNIFORM4I)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRY * PFNGLUNIFORM4IV)(GLint location, GLsizei count, const GLint* value);
typedef void (APIENTRY * PFNGLUNIFORM4UI)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRY * PFNGLUNIFORM4UIV)(GLint location, GLsizei count, const GLuint* value);
typedef void (APIENTRY * PFNGLUNIFORM4F)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRY * PFNGLUNIFORM4FV)(GLint location, GLsizei count, const GLfloat* value);

typedef void (APIENTRY * PFNGLUNIFORMMATRIX2FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX3FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX4FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX2X3FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX3X2FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX2X4FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX4X2FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX3X4FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX4X3FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

class OpenGLClass
{
public:
	OpenGLClass();
	OpenGLClass(const OpenGLClass&);
	~OpenGLClass();

	bool InitializeExtensions(HWND);
	bool InitializeOpenGL(HWND, __int16, __int16, float, float, bool);
	void Shutdown(HWND);

	bool IsExtensionSupported(const char* name) const;

	static void BeginScene(float, float, float, float);
	void EndScene() const;

	void GetVideoCardInfo(char*) const;

private:
	bool LoadExtensionList();

private:
	HDC m_deviceContext;
	HGLRC m_renderingContext;

	PFNWGLCHOOSEPIXELFORMATARB wglChoosePixelFormatARB;
	PFNWGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB;
	PFNWGLSWAPINTERVALEXT wglSwapIntervalEXT;

	char m_videoCardDescription[512];

public:
	PFNGLATTACHSHADER glAttachShader;
	PFNGLCOMPILESHADER glCompileShader;
	PFNGLCREATEPROGRAM glCreateProgram;
	PFNGLCREATESHADER glCreateShader;
	PFNGLDELETEPROGRAM glDeleteProgram;
	PFNGLDELETESHADER glDeleteShader;
	PFNGLDETACHSHADER glDetachShader;
	PFNGLGETPROGRAMINFOLOG glGetProgramInfoLog;
	PFNGLGETPROGRAMIV glGetProgramiv;
	PFNGLGETSHADERINFOLOG glGetShaderInfoLog;
	PFNGLGETSHADERIV glGetShaderiv;
	PFNGLLINKPROGRAM glLinkProgram;
	PFNGLSHADERSOURCE glShaderSource;
	PFNGLUSEPROGRAM glUseProgram;
	PFNGLGETUNIFORMLOCATION glGetUniformLocation;

	PFNGLBINDBUFFER glBindBuffer;
	PFNGLBINDVERTEXARRAY glBindVertexArray;
	PFNGLBUFFERDATA glBufferData;
	PFNGLDELETEBUFFERS glDeleteBuffers;
	PFNGLDELETEVERTEXARRAYS glDeleteVertexArrays;
	PFNGLENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray;
	PFNGLGENBUFFERS glGenBuffers;
	PFNGLGENVERTEXARRAYS glGenVertexArrays;
	PFNGLGETATTRIBLOCATION glGetAttribLocation;
	PFNGLGETSTRINGI glGetStringi;

	PFNGLVERTEXATTRIBPOINTER glVertexAttribPointer;
	PFNGLBINDATTRIBLOCATION glBindAttribLocation;
	PFNGLACTIVETEXTURE glActiveTexture;
	PFNGLGENERATEMIPMAP glGenerateMipmap;
	PFNGLDISABLEVERTEXATTRIBARRAY glDisableVertexAttribArray;

	PFNGLUNIFORM1I glUniform1i;
	PFNGLUNIFORM1IV glUniform1iv;
	PFNGLUNIFORM1UI glUniform1ui;
	PFNGLUNIFORM1UIV glUniform1uiv;
	PFNGLUNIFORM1F glUniform1f;
	PFNGLUNIFORM1FV glUniform1fv;

	PFNGLUNIFORM2I glUniform2i;
	PFNGLUNIFORM2IV glUniform2iv;
	PFNGLUNIFORM2UI glUniform2ui;
	PFNGLUNIFORM2UIV glUniform2uiv;
	PFNGLUNIFORM2F glUniform2f;
	PFNGLUNIFORM2FV glUniform2fv;

	PFNGLUNIFORM3I glUniform3i;
	PFNGLUNIFORM3IV glUniform3iv;
	PFNGLUNIFORM3UI glUniform3ui;
	PFNGLUNIFORM3UIV glUniform3uiv;
	PFNGLUNIFORM3F glUniform3f;
	PFNGLUNIFORM3FV glUniform3fv;

	PFNGLUNIFORM4I glUniform4i;
	PFNGLUNIFORM4IV glUniform4iv;
	PFNGLUNIFORM4UI glUniform4ui;
	PFNGLUNIFORM4UIV glUniform4uiv;
	PFNGLUNIFORM4F glUniform4f;
	PFNGLUNIFORM4FV glUniform4fv;

	PFNGLUNIFORMMATRIX2FV glUniformMatrix2fv;
	PFNGLUNIFORMMATRIX3FV glUniformMatrix3fv;
	PFNGLUNIFORMMATRIX4FV glUniformMatrix4fv;
	PFNGLUNIFORMMATRIX2X3FV glUniformMatrix2x3fv;
	PFNGLUNIFORMMATRIX3X2FV glUniformMatrix3x2fv;
	PFNGLUNIFORMMATRIX2X4FV glUniformMatrix2x4fv;
	PFNGLUNIFORMMATRIX4X2FV glUniformMatrix4x2fv;
	PFNGLUNIFORMMATRIX3X4FV glUniformMatrix3x4fv;
	PFNGLUNIFORMMATRIX4X3FV glUniformMatrix4x3fv;
};

#endif

