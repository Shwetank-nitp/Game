#pragma once

#include "Vec2.h";

class CTransform
{
public:
	Vec2 pos;					//default { 0.0, 0.0 }
	Vec2 velocity;
	double angle = 0.0;
	CTransform() {};
	CTransform(const Vec2& pos, const Vec2& velocity, const double angle)
		: pos(pos)
		, velocity(velocity)
		, angle(angle)
	{
	};
};

class CCollision
{
public:
	unsigned int radius = 0;
	CCollision(unsigned int r): radius(r) {};
};

class CLifeTime
{
public:
	size_t lifetime = 0;
	size_t lifetime_remaning = 0;
	CLifeTime() {};
	CLifeTime(size_t time)
		: lifetime(time)
		, lifetime_remaning(time)
	{
	};
};

class CShape
{
public:
	sf::CircleShape shape;
	float opacity = 0.0f;
	CShape(const size_t radious, const size_t thickenss, const size_t points, const sf::Color& fillColor, const sf::Color& outlineColor)
		: shape(radious, points)
		, opacity(fillColor.a)
	{
		shape.setOutlineColor(outlineColor);
		shape.setOutlineThickness(thickenss);
		shape.setOrigin(radious, radious);
		shape.setFillColor(fillColor);
	};
};

class CInput
{
public:
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	bool mouse_left = false;
	bool mouse_right = false;
	Vec2 direction;
	CInput() {};
};

class CScore
{
public:
	size_t score = 0;
	CScore() {};
	CScore(const size_t s)
		:score(s)
	{
	};
};