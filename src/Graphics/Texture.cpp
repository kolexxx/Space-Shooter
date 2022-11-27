#define FOURCC(x) ( (unsigned int) (((x[3])<<24) | ((x[2])<<16) | ((x[1])<<8) | (x[0])) )

#include "Texture.hpp"

#include <fstream>

Texture::Texture() : m_slot(0), m_width(0), m_height(0) {}

Texture::Texture(int width, int height, const void* pixels) :
	m_slot(0),
	m_width(width),
	m_height(height)
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

Texture::~Texture()
{
	if (m_slot >= 0)
		s_activeTextures[m_slot] = nullptr;

	glDeleteTextures(1, &m_ID);
}

Texture& Texture::Load(const std::string& path)
{
	{
		auto it = s_collection.find(path);
		if (it != s_collection.end())
			return *it->second;
	}

	std::ifstream file(path, std::ios::in);

	if (!file.is_open())
	{
		printf("Couldn't open %s!", path.c_str());
		return *(Texture*)nullptr;
	}

	auto filecode = 0u;
	file.read((char*)&filecode, 4);

	if (filecode != FOURCC("DDS "))
	{
		file.close();
		return *(Texture*)nullptr;
	}

	auto header = std::array<unsigned int, 31>();
	file.read((char*)header.data(), sizeof(header));

	auto height = header[2];
	auto width = header[3];
	auto linearSize = header[4];
	auto mipMapCount = header[6];
	auto fourCC = header[20];

	auto bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	auto* buffer = (char*)alloca(bufferSize * sizeof(char));

	file.read(buffer, bufferSize);

	auto components = (fourCC == FOURCC("DXT1")) ? 3u : 4u;
	unsigned int format;

	switch (fourCC)
	{
	case FOURCC("DXT1"):
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC("DXT3"):
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC("DXT5"):
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		return *(Texture*)nullptr;
	}

	// Create one OpenGL texture
	auto* texture = new Texture();
	glGenTextures(1, &texture->m_ID);
	glBindTexture(GL_TEXTURE_2D, texture->m_ID);
	texture->m_width = width;
	texture->m_height = height;

	auto blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8u : 16u;
	auto offset = 0u;

	for (auto level = 0u; level < mipMapCount && (width || height); level++)
	{
		auto size = ((width + 3u) / 4u) * ((height + 3u) / 4u) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

		offset += size;
		width >>= 1;
		height >>= 1;
	}

	s_collection.emplace(path, texture);

	return *texture;
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::MakeActive() const
{
	int i;

	for (i = 1; i < 32; i++)
	{
		if (s_activeTextures[i] == this)
			return;

		if (s_activeTextures[i] == nullptr)
			break;
	}

	if (i == 32)
	{
		i = 1;

		for (auto*& texture : s_activeTextures)
		{
			texture->m_slot = -1;
			texture = nullptr;
		}
	}

	m_slot = i;
	s_activeTextures[i] = this;

	glActiveTexture(GL_TEXTURE0 + i);
	Bind();	
}

unsigned char Texture::Slot() const
{
	return m_slot;
}

unsigned int Texture::Width() const
{
	return m_width;
}

unsigned int Texture::Height() const
{
	return m_height;
}

std::array<const Texture*, 32> Texture::s_activeTextures = {};
std::unordered_map<std::string, std::unique_ptr<Texture>> Texture::s_collection = {};