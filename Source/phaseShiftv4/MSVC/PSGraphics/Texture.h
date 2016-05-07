#pragma once

#include "PSPlatform/Windows/OpenGLClass.h"

class Texture
{
private:
	struct TGAHEADER
	{
		unsigned char Data1[12];
		unsigned char Width;
		unsigned char Height;
		unsigned char BPP;
		unsigned char Data2;
	};

public:
	Texture();
	Texture(const Texture&);
	~Texture();

	bool Initialzize(OpenGLClass*, char*, unsigned int, bool);
	void Shutdown();

private:
	bool LoadTGA(OpenGLClass*, char*, unsigned int, bool);

	bool loaded;
	GLuint m_textureID;
};
