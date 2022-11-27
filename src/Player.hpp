#pragma once

#include "Entity.hpp"
#include "Graphics/Graphics.hpp"

class Player : public Entity
{
public:
	Player();

	void Tick() override;
	void Frame() override;
private:
	float m_Speed;
	Texture& m_Texture;
};