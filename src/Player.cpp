#include "Player.hpp"

#include "Input.hpp"
#include "Time.hpp"

Player::Player() : m_Speed(200), m_Texture(Texture::Load("textures/uvtemplate.DDS"))
{
	m_Position = { 0, 0 };
	m_BBox = { 300.0f, 300.0f };
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

	if (wishDir.x == 0 && wishDir.y == 0)
		return;

	m_Position += glm::normalize(wishDir) * m_Speed * Time::Delta();
}

void Player::Frame()
{
	Graphics::DrawQuad(m_Position, m_BBox, m_Texture);
}