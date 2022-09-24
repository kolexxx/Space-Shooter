#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

class Entity
{
public:
	static const std::vector<std::shared_ptr<Entity>>& All();

	Entity();
	virtual ~Entity();

	friend int main( void );
protected:
	virtual void Tick() = 0;
	virtual void Frame() = 0;
	virtual void Touch( const Entity& other ) = 0;

	glm::vec2 m_position;
	glm::vec2 m_bbox;
private:
	static std::vector<std::shared_ptr<Entity>> s_all;
};