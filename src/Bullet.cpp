#include "Bullet.hpp"

#include "SpaceShooter.hpp"
#include "Graphics/Graphics.hpp"

Bullet::Bullet(glm::vec2 position) : Entity(position, glm::vec2(10, 20)) {}

void Bullet::Tick()
{
	// this is shit
	if (std::abs(m_position.y) > 768 / 2)
		Delete();
	else if (std::abs(m_position.x) > 1024 / 2)
		Delete();

	m_position.y += 300 * Time::Delta();
}

void Bullet::Frame()
{
	Graphics::DrawQuad(m_position, m_BBox, glm::vec3(0, 1, 0));
}
