#include "Entity.h"

Entity::Entity() : m_active(true) {}

Entity::Entity(const Tags& tag, const size_t id) : m_tag(tag), m_id(id), m_active(true) {};

void Entity::distroy()
{
	m_active = false;
}

const Tags& Entity::tag() const
{
	return m_tag;
}

const size_t Entity::get_id() const
{
	return m_id;
}

const bool Entity::isActive() const
{
	return m_active;
}