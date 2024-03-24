#include "Vector2D.h"

Vector2D::Vector2D(float x, float y) : x(x), y(y)
{ }

float Vector2D::magnitude() const
{
	return sqrt(x * x + y * y);
}

float Vector2D::distance(const Vector2D& rhs)
{
	float dx = x - rhs.x;
	float dy = y - rhs.y;

	return sqrt(dx * dx + dy * dy);
}

float Vector2D::toroidalDistance(const Vector2D& rhs, float w, float h) const
{
	float dx = x - rhs.x;
	float dy = y - rhs.y;

	if (dx > w / 2)
		dx = w - dx;

	if (dy > h / 2)
		dy = h - dy;

	return dx * dx + dy * dy;
}

Vector2D& Vector2D::normalize()
{
	float m = magnitude();

	if (m != 0)
	{
		x /= m;
		y /= m;
	}

	return *this;
}

Vector2D& Vector2D::limit(float max)
{
	float m = magnitude();

	if (m > max)
	{
		x *= max / m;
		y *= max / m;
	}

	return *this;
}

Vector2D Vector2D::random()
{
	float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	return Vector2D(x, y);
}

bool Vector2D::operator==(const Vector2D& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool Vector2D::operator!=(const Vector2D& rhs) const
{
	return !(x == rhs.x && y == rhs.y);
}

Vector2D& Vector2D::operator=(float s)
{
	x = s;
	y = s;

	return *this;
}

Vector2D Vector2D::operator-() const
{
	return Vector2D(-x, -y);
}

Vector2D Vector2D::operator+(float s) const
{
	return Vector2D(x + s, y + s);
}

Vector2D Vector2D::operator-(float s) const
{
	return Vector2D(x - s, y - s);
}

Vector2D Vector2D::operator*(float s) const
{
	return Vector2D(x * s, y * s);
}

Vector2D Vector2D::operator/(float s) const
{
	return Vector2D(x / s, y / s);
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
	return Vector2D(x + rhs.x, y + rhs.y);
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
	return Vector2D(x - rhs.x, y - rhs.y);
}

Vector2D Vector2D::operator*(const Vector2D& rhs) const
{
	return Vector2D(x * rhs.x, y * rhs.y);
}

Vector2D Vector2D::operator/(const Vector2D& rhs) const
{
	return Vector2D(x / rhs.x, y / rhs.y);
}

Vector2D& Vector2D::operator+=(float s)
{
	x += s;
	y += s;

	return *this;
}

Vector2D& Vector2D::operator-=(float s)
{
	x -= s;
	y -= s;

	return *this;
}

Vector2D& Vector2D::operator*=(float s)
{
	x *= s;
	y *= s;

	return *this;
}

Vector2D& Vector2D::operator/=(float s)
{
	if (s != 0)
	{
		x /= s;
		y /= s;
	}

	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& rhs)
{
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& rhs)
{
	if (rhs.x != 0 && rhs.y != 0)
	{
		x /= rhs.x;
		y /= rhs.y;
	}

	return *this;
}

float Vector2D::vectorDistance(const std::vector<int>& lhs, const std::vector<int>& rhs)
{
	float dx = lhs[0] - rhs[0];
	float dy = lhs[1] - rhs[1];

	return sqrt(dx * dx + dy * dy);
}

float Vector2D::vectorToroidalDistance(const std::vector<int>& lhs, const std::vector<int>& rhs, float w, float h)
{
	float dx = lhs[0] - rhs[0];
	float dy = lhs[1] - rhs[1];

	if (dx > w / 2)
		dx = w - dx;

	if (dy > h / 2)
		dy = h - dy;

	return sqrt(dx * dx + dy * dy);
}