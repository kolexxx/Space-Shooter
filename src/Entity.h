#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

class Entity
{
public:
	static std::vector<std::shared_ptr<Entity>> All;

	Entity();
	virtual ~Entity();

	friend int main( void );
protected:
	void Tick();
	void Frame();

	void Touch( const Entity& other );

	glm::vec3 m_position;
	glm::vec2 m_bbox;
};