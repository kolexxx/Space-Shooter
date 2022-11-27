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

	friend int main(void);
protected:
	virtual void Tick() {};
	virtual void Frame() {};
	virtual void Touch(const Entity& other) {};

	glm::vec2 m_Position;
	glm::vec2 m_BBox;
private:
	static std::vector<std::shared_ptr<Entity>> s_All;
};