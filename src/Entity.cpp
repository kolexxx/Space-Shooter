#include "Entity.h"

const std::vector<std::shared_ptr<Entity>>& Entity::All()
{
	return s_all;
}

Entity::Entity() : m_position( glm::vec2( 0 ) ), m_bbox( glm::vec2( 0 ) )
{
	s_all.emplace_back( this );
}

Entity::~Entity()
{
	for ( auto it = s_all.begin(); it != s_all.end(); it++ )
	{
		if ( it->get() != this )
			continue;

		s_all.erase( it );
		break;
	}
}

std::vector<std::shared_ptr<Entity>> Entity::s_all{};