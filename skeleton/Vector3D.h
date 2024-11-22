#pragma once
class Vector3D
{
private:
	double _x, _y, _z;

public:
	Vector3D() noexcept : _x(0), _y(0), _z(0) {}
	Vector3D(double x, double y, double z) noexcept : _x(x), _y(y), _z(z) {}

	void normalize();
	double module() const;
	double dot(const Vector3D& v) const;
	Vector3D cross(const Vector3D& v) const;
	Vector3D& operator=(const Vector3D& v);
	Vector3D operator+(const Vector3D& v);
	Vector3D operator-(const Vector3D& v);
	Vector3D operator*(const double d);
};

