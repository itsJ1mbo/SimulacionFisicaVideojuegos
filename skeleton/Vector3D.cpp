#include "Vector3D.h"
#include <math.h>

void Vector3D::normalize()
{
	const double m = module();

	x_ /= m;
	y_ /= m;
	z_ /= m;
}

double Vector3D::module() const
{
	return sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}

double Vector3D::dot(const Vector3D& v) const
{
	return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

Vector3D Vector3D::cross(const Vector3D& v) const
{
	//TODO
	return Vector3D();
}

Vector3D& Vector3D::operator=(const Vector3D& v)
{
	return Vector3D(v.x_, v.y_, v.z_);
}

Vector3D Vector3D::operator+(const Vector3D& v) const
{
	return Vector3D(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}

Vector3D Vector3D::operator-(const Vector3D& v) const
{
	return Vector3D(x_ - v.x_, y_ - v.y_, z_ - v.z_);
}

Vector3D Vector3D::operator*(const double d) const
{
	return Vector3D(x_ * d, y_ * d, z_ * d);
}