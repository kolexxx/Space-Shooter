#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

class Entity
{
public:
	/// <returns>The active entity list for this current tick.</returns>
	static const std::vector<Entity*>& All();

	Entity();
	Entity(glm::vec2 position, glm::vec2 BBox);
	virtual ~Entity() = default;

	/// <summary>
	/// Deletes this entity in the next tick.
	/// </summary>
	void Delete();

	friend int main(void);
protected:
	virtual void Tick() {};
	virtual void Frame() {};
	virtual void Touch(const Entity& other) {};

	glm::vec2 m_position;
	glm::vec2 m_BBox;
private:
	static void UpdateList();

	/// <summary>
	/// The global entity list. This contains every valid 
	/// entity during a single tick.
	/// </summary>
	static std::vector<Entity*> s_all;
	/// <summary>
	/// Entities inside this list will be deleted and removed from
	/// the global entity list in the next tick.
	/// </summary>
	static std::vector<Entity*> s_invalidEntites;
	/// <summary>
	/// Entities inside this list will be added
	/// to the global entity list in the next tick.
	/// </summary>
	static std::vector<Entity*> s_newEntites;
};