#pragma once
class Vector3D
{
private:
	double x_, y_, z_;

public:
	Vector3D() noexcept : x_(0), y_(0), z_(0) {}
	Vector3D(double x, double y, double z) noexcept : x_(x), y_(y), z_(z) {}

	void normalize();
	double module() const;
	double dot(const Vector3D& v) const;
	Vector3D cross(const Vector3D& v) const;
	Vector3D& operator=(const Vector3D& v);
	Vector3D operator+(const Vector3D& v) const;
	Vector3D operator-(const Vector3D& v) const;
	Vector3D operator*(const double d) const;
};

