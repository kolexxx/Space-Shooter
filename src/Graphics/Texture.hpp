#pragma once

#include "GLObject.hpp"

#include <array>
#include <memory>
#include <string>
#include <unordered_map>

class Texture : public GLObject
{
public:
	Texture(int width, int height, const void* pixels);
	~Texture();

	static Texture& Load(const std::string& path);

	void Bind() const;
	void Unbind() const;
	void MakeActive() const;

	[[nodiscard]] unsigned char Slot() const;
	[[nodiscard]] unsigned int Width() const;
	[[nodiscard]] unsigned int Height() const;
private:
	Texture();

	mutable char m_slot;
	unsigned int m_width, m_height;

	static std::array<const Texture*, 32> s_activeTextures;
	static std::unordered_map<std::string, std::unique_ptr<Texture>> s_collection;
};