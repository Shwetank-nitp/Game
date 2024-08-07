#pragma once
#include "Common.h"
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> entity_vector;
typedef std::unordered_map<Tags, entity_vector> entity_map;

class EntityManager
{
	size_t m_total_entity = 0;
	entity_vector m_all_entities;
	entity_map m_enities_by_map;
	entity_vector m_to_add;

public:
	EntityManager();

	std::shared_ptr<Entity> add_entites(const Tags& tag);
	void update();
	const entity_vector& get_entities() const;
	const entity_map& get_entities_map() const;
	void remove_dead_enitites();
};