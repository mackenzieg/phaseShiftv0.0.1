#include "Texture.h"

Texture::Texture() : m_textureID(0)
{
	loaded = false;
}

Texture::Texture(const Texture& ext) : m_textureID(ext.m_textureID), loaded(ext.loaded)
{
}

Texture::~Texture()
{
}

bool Texture::Initialzize(OpenGLClass* OpenGL, char* filename, unsigned int textureUnit, bool wrap)
{
	bool result;

	result = LoadTGA(OpenGL, filename, textureUnit, wrap);
	if (!result)
	{
		return false;
	}
	return true;
}

void Texture::Shutdown()
{
	if (loaded)
	{
		glDeleteTextures(1, &m_textureID);
		loaded = false;
	}
}

bool Texture::LoadTGA(OpenGLClass* OpenGL, char* filename, unsigned int textureUnit, bool wrap)
{
	int error, width, height, bpp, imageSize;
	FILE* filePtr;
	unsigned int count;
	TGAHEADER tgaHeader;
	unsigned char* tgaImage;

	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	count = fread(&tgaHeader, sizeof(TGAHEADER), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	width = static_cast<int>(tgaHeader.Width);
	height = static_cast<int>(tgaHeader.Height);
	bpp = static_cast<int>(tgaHeader.BPP);

	if (bpp != 32)
	{
		return false;
	}

	imageSize = width * height * 4;

	tgaImage = new unsigned char[imageSize];
	if (!tgaImage)
	{
		return false;
	}

	count = fread(tgaImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		return false;
	}

	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	OpenGL->glActiveTexture(GL_TEXTURE0 + textureUnit);

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, tgaImage);

	if (wrap)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	OpenGL->glGenerateMipmap(GL_TEXTURE_2D);

	delete filePtr;
	filePtr = nullptr;

	delete[] tgaImage;
	tgaImage = nullptr;

	loaded = true;

	return true;
}