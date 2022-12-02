#include "Player.hpp"

#include "Bullet.hpp"
#include "Input.hpp"
#include "Time.hpp"

Player::Player() :
	Entity(glm::vec2(0, 0), glm::vec2(50.0f, 50.0f)),
	m_speed(200),
	m_texture(Texture::Load("textures/uvtemplate.DDS"))
{
}

void Player::Tick()
{
	auto wishDir = glm::vec2(0);

	if (Input::Down('W'))
		wishDir.y += 1;
	if (Input::Down('S'))
		wishDir.y -= 1;
	if (Input::Down('A'))
		wishDir.x -= 1;
	if (Input::Down('D'))
		wishDir.x += 1;

	if (wishDir.x != 0 || wishDir.y != 0)
		m_position += glm::normalize(wishDir) * m_speed * Time::Delta();

	if (Input::Pressed(' '))
		new Bullet(m_position + glm::vec2(0, m_BBox.y / 2.0f));
}

void Player::Frame()
{
	Graphics::DrawQuad(m_position, m_BBox, glm::vec3(1, 0, 0));
}