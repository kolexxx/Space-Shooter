#include "Entity.hpp"

const std::vector<std::shared_ptr<Entity>>& Entity::All()
{
	return s_All;
}

Entity::Entity() : m_Position( glm::vec2( 0 ) ), m_BBox( glm::vec2( 0 ) )
{
	s_All.emplace_back( this );
}

Entity::~Entity()
{
	for ( auto it = s_All.begin(); it != s_All.end(); it++ )
	{
		if ( it->get() != this )
			continue;

		s_All.erase( it );
		break;
	}
}

std::vector<std::shared_ptr<Entity>> Entity::s_All{};