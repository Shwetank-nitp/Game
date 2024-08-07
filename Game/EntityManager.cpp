#include "EntityManger.h"

EntityManager::EntityManager()
	: m_total_entity(0)
{
};


void EntityManager::update()
{
	for (const auto& item : m_to_add)
	{
		m_all_entities.push_back(item);
		m_enities_by_map[item->tag()].push_back(item);
	}
	m_to_add.clear();
}

std::shared_ptr<Entity> EntityManager::add_entites(const Tags& tag)
{
	auto e = std::shared_ptr<Entity>(new Entity(tag, m_total_entity++)); // creating a new Entity in heap_mamory
	m_to_add.push_back(e);
	return e;
}

const entity_vector& EntityManager::get_entities() const
{
	return m_all_entities;
}

const entity_map& EntityManager::get_entities_map() const
{
	return m_enities_by_map;
}

void EntityManager::remove_dead_enitites()
{
	entity_vector new_vec;

	for (auto& item : m_all_entities)
	{
		if (item->isActive())
		{
			new_vec.push_back(item);
		}
		else
		{
			item.reset(); // delete the heap memeory of dead eneities
		}
	}

	m_all_entities = new_vec;
}
