#pragma once

#include "Entity.hpp"

class Bullet : public Entity 
{
public:
	Bullet(glm::vec2 position);
protected:
	void Tick() override;
	void Frame() override;
};