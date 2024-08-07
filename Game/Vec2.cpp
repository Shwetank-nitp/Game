#include "Vec2.h"
#include "common.h"

Vec2::Vec2(float xin, float yin)
	: x(xin)
	, y(yin)
{
}

Vec2::Vec2() {}


Vec2 Vec2::operator+ (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}
Vec2 Vec2::operator- (const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

void Vec2::operator+= (const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

Vec2& Vec2::add(const Vec2& v)
{
	x += v.x;
	y += v.y;

	return *this;
}

void Vec2::operator>>(const bool o)
{
	if (o)
	{
		x = -x;
	}
	else
	{
		y = -y;
	}
}

Vec2& Vec2::subtract(const Vec2& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

float Vec2::lenght() const
{
	return sqrt(x * x + y * y);
}

Vec2& Vec2::unit()
{
	float len = this->lenght();
	if (len != 0) {
		x /= len;
		y /= len;
	}
	return *this;
}

Vec2& Vec2::scale(float s)
{
	x *= s;
	y *= s;
	return *this;
}

