#include "Vector3D.h"
#include <cmath>

void Vector3D::normalize()
{
	const double m = module();

	_x /= m;
	_y /= m;
	_z /= m;
}

double Vector3D::module() const
{
	return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
}

double Vector3D::dot(const Vector3D& v) const
{
	return _x * v._x + _y * v._y + _z * v._z;
}

Vector3D Vector3D::cross(const Vector3D& v) const
{
	return {
		_y * v._z - _z * v._y,  
		_z * v._x - _x * v._z,  
		_x * v._y - _y * v._x
	};

}

Vector3D& Vector3D::operator=(const Vector3D& v)
{
	_x = v._x;
	_y = v._y;
	_z = v._z;

	return *this;
}

Vector3D Vector3D::operator+(const Vector3D& v)
{
	_x += v._x;
	_y += v._y;
	_z += v._z;

	return *this;
}

Vector3D Vector3D::operator-(const Vector3D& v)
{
	_x -= v._x;
	_y -= v._y;
	_z -= v._z;

	return *this;
}

Vector3D Vector3D::operator*(const double d)
{
	_x *= d;
	_y *= d;
	_z *= d;

	return *this;
}