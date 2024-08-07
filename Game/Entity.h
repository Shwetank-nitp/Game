#pragma once
#include "Tags.h"
#include "common.h"
#include "Component.h"

class Entity
{
	friend class EntityManager;

	const size_t m_id = 0;
	const Tags m_tag = Tags::NONE;
	bool m_active = true;

	Entity();
	Entity(const Tags& tag, const size_t id);
public:

	std::shared_ptr<CTransform> c_tansform;
	std::shared_ptr<CCollision> c_collision;
	std::shared_ptr<CLifeTime>	c_lifespan;
	std::shared_ptr<CShape> c_shape;
	std::shared_ptr<CInput> c_input;
	std::shared_ptr<CScore> c_sore;

	const Tags& tag() const;
	const bool isActive() const;
	const size_t get_id() const;
	void distroy();
};