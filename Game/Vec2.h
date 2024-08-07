#pragma once

class Vec2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	Vec2();
	Vec2(float, float);

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	void operator += (const Vec2& rhs);
	void operator -= (const Vec2& rhs);
	void operator >> (const bool i);

	Vec2& add(const Vec2& v);
	Vec2& subtract(const Vec2& v);
	Vec2& unit();
	Vec2& scale(float s);

	float lenght() const;
};