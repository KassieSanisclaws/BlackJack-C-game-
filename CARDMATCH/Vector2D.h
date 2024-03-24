#pragma once

#include <cmath>
#include <cstdlib>
#include <vector>

class Vector2D
{
public:
	Vector2D() = default;
	Vector2D(float = 0.0f, float = 0.0f);
	Vector2D(const Vector2D&) = default;

	~Vector2D() = default;

	float magnitude() const;
	Vector2D& normalize();
	Vector2D& limit(float max);

	float distance(const Vector2D&);
	float toroidalDistance(const Vector2D&, float, float) const;

	bool operator==(const Vector2D&) const;
	bool operator!=(const Vector2D&) const;

	Vector2D& operator=(const Vector2D&) = default;
	Vector2D& operator=(float);

	Vector2D operator-() const;

	Vector2D operator+(float) const;
	Vector2D operator-(float) const;
	Vector2D operator*(float) const;
	Vector2D operator/(float) const;

	Vector2D operator+(const Vector2D&) const;
	Vector2D operator-(const Vector2D&) const;
	Vector2D operator*(const Vector2D&) const;
	Vector2D operator/(const Vector2D&) const;

	Vector2D& operator+=(float);
	Vector2D& operator-=(float);
	Vector2D& operator*=(float);
	Vector2D& operator/=(float);

	Vector2D& operator+=(const Vector2D&);
	Vector2D& operator-=(const Vector2D&);
	Vector2D& operator*=(const Vector2D&);
	Vector2D& operator/=(const Vector2D&);

	static Vector2D random();
	static float vectorDistance(const std::vector<int>&, const std::vector<int>&);
	static float vectorToroidalDistance(const std::vector<int>&, const std::vector<int>&, float, float);

	float x;
	float y;
};
