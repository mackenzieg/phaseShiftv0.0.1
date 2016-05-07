#pragma once

#ifndef _SHADER_H_
#define _SHADER_H_

#include <stdlib.h>
#include <stdio.h>

#include "../PSPlatform/Windows/OpenGLClass.h"

class Shader
{
public:
	GLuint m_shaderProgram;
	GLuint m_vertexShader;
	GLuint m_fragmentShader;

public:
	Shader();
	Shader(const Shader&);
	~Shader();

	void CreateShader(OpenGLClass*, char*, char*);
	void BindShader(OpenGLClass*) const;
	void UnbindShader(OpenGLClass*) const;
	void DeleteShader(OpenGLClass*) const;

private:
	static char* filetobuf(char* file);

	static void OutputShaderErrorMessage(OpenGLClass*, unsigned int, char*);
	static void OutputLinkerErrorMessage(OpenGLClass*, unsigned int);
};

#endif