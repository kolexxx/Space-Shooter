#include "Entity.hpp"

const std::vector<Entity*>& Entity::All()
{
	return s_all;
}

Entity::Entity() : Entity(glm::vec2(0), glm::vec2(0)) {}

Entity::Entity(glm::vec2 position, glm::vec2 BBox) :
	m_position(position),
	m_BBox(BBox)
{
	s_newEntites.push_back(this);
}

void Entity::Delete()
{
	s_invalidEntites.push_back(this);
}

void Entity::UpdateList()
{
	auto invalidEntity = s_invalidEntites.begin();
	auto it = s_all.begin();
	while (it != s_all.end())
	{
		if (invalidEntity == s_invalidEntites.end())
			break;

		if (*it != *invalidEntity)
		{
			it++;
			continue;
		}

		delete* it;
		it = s_all.erase(it);
		invalidEntity++;
	}

	s_all.insert(s_all.end(), s_newEntites.begin(), s_newEntites.end());

	s_invalidEntites.clear();
	s_newEntites.clear();
}

std::vector<Entity*> Entity::s_all{};
std::vector<Entity*> Entity::s_invalidEntites{};
std::vector<Entity*> Entity::s_newEntites{};