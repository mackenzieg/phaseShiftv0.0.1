#include "Shader.h"

Shader::Shader() : m_shaderProgram(0), m_vertexShader(0), m_fragmentShader(0)
{
}

Shader::Shader(const Shader& a) : m_shaderProgram(a.m_shaderProgram), m_vertexShader(a.m_vertexShader), m_fragmentShader(a.m_fragmentShader)
{
}

Shader::~Shader()
{
}

void Shader::CreateShader(OpenGLClass* OpenGL, char* vertFile, char* fragFile)
{
	const char* vertShaderBuffer = nullptr;
	const char* fragShaderBuffer = nullptr;
	GLint status = 0;

	vertShaderBuffer = filetobuf(vertFile);
	fragShaderBuffer = filetobuf(fragFile);

	GLint vertShader = 0, fragShader = 0;
	vertShader = OpenGL->glCreateShader(GL_VERTEX_SHADER);
	fragShader = OpenGL->glCreateShader(GL_FRAGMENT_SHADER);

	OpenGL->glShaderSource(m_vertexShader, 1, &vertShaderBuffer, nullptr);
	OpenGL->glShaderSource(m_fragmentShader, 1, &fragShaderBuffer, nullptr);

	delete[] vertShaderBuffer;
	vertShaderBuffer = nullptr;

	delete[] fragShaderBuffer;
	fragShaderBuffer = nullptr;

	OpenGL->glCompileShader(m_vertexShader);
	OpenGL->glCompileShader(m_fragmentShader);

	OpenGL->glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		OutputShaderErrorMessage(OpenGL, m_vertexShader, vertFile);
		DeleteShader(OpenGL);

		return;
	}

	OpenGL->glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		OutputShaderErrorMessage(OpenGL, m_fragmentShader, fragFile);
		DeleteShader(OpenGL);

		return;
	}

	m_shaderProgram = OpenGL->glCreateProgram();

	OpenGL->glAttachShader(m_shaderProgram, m_vertexShader);
	OpenGL->glAttachShader(m_shaderProgram, m_fragmentShader);

	OpenGL->glLinkProgram(m_shaderProgram);

	OpenGL->glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
	if (status != 1)
	{
		OutputLinkerErrorMessage(OpenGL, m_shaderProgram);
	}
}

void Shader::BindShader(OpenGLClass* OpenGL) const
{
	OpenGL->glUseProgram(m_shaderProgram);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Shader::UnbindShader(OpenGLClass* OpenGL) const
{
	OpenGL->glUseProgram(0);
}

void Shader::DeleteShader(OpenGLClass* OpenGL) const
{
	OpenGL->glDetachShader(m_shaderProgram, m_vertexShader);
	OpenGL->glDetachShader(m_shaderProgram, m_fragmentShader);

	OpenGL->glDeleteShader(m_vertexShader);
	OpenGL->glDeleteShader(m_fragmentShader);

	OpenGL->glDeleteProgram(m_shaderProgram);
}

char* Shader::filetobuf(char* file)
{
	FILE* fptr = nullptr;
	long length = 0;
	char* buf = nullptr;

	fptr = fopen(file, "rb");
	if (!fptr)
	{
		return nullptr;
	}
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = static_cast<char*>(malloc(length + 1));
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	delete fptr;
	buf[length] = 0;

	return buf;
}

void Shader::OutputShaderErrorMessage(OpenGLClass* OpenGL, unsigned int shaderID, char* shaderFileName)
{
	GLint logSize = 0;
	char* infoLog = nullptr;

	OpenGL->glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize);

	logSize++;

	infoLog = new char[logSize];
	if (!infoLog)
	{
		std::cerr << "Error Creating Shader Error Info Log!" << __FILE__ << " " << __FUNCTIONW__ << " " << __LINE__ << std::endl;
		return;
	}

	OpenGL->glGetShaderInfoLog(shaderID, logSize, nullptr, infoLog);
	std::cerr << "Error Compiling Shader: " << infoLog << std::endl << __FILE__ << " " << __FUNCTIONW__ << " " << __LINE__ << std::endl;

	delete[] infoLog;
	infoLog = nullptr;

	return;
}

void Shader::OutputLinkerErrorMessage(OpenGLClass* OpenGL, unsigned int programID)
{
	GLint logSize = 0;
	char* infoLog = nullptr;

	OpenGL->glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logSize);

	logSize++;

	infoLog = new char[logSize];
	if (!infoLog)
	{
		std::cerr << "Error Creating Program Error Info Log! " << __FILE__ << " " << __FUNCTIONW__ << " " << __LINE__ << std::endl;
		return;
	}

	OpenGL->glGetProgramInfoLog(programID, logSize, nullptr, infoLog);
	std::cerr << "Error Compiling Program: " << infoLog << std::endl << __FILE__ << " " << __FUNCTIONW__ << " " << __LINE__ << std::endl;

	delete[] infoLog;
	infoLog = nullptr;

	return;
}