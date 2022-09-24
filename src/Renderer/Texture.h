#pragma once

#include "GLObject.h"

#include <array>
#include <memory>
#include <string>
#include <unordered_map>

class Texture : public GLObject
{
public:
	// static std::array<Texture, 32> s_Slots;
	~Texture();

	static Texture& Load( const std::string& path );

	void Bind( unsigned int slot = 0 );
	void Unbind();

	unsigned int Slot() const;
	unsigned int Width() const;
	unsigned int Height() const;
private:
	Texture();
	
	unsigned int m_slot, m_width, m_height;
	static std::unordered_map<std::string, std::unique_ptr<Texture>> s_Collection;
};