#include "Vector3D.h"
#include <cmath>

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
	return {
		y_ * v.z_ - z_ * v.y_,  
		z_ * v.x_ - x_ * v.z_,  
		x_ * v.y_ - y_ * v.x_
	};

}

Vector3D& Vector3D::operator=(const Vector3D& v)
{
	x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;

	return *this;
}

Vector3D Vector3D::operator+(const Vector3D& v)
{
	x_ += v.x_;
	y_ += v.y_;
	z_ += v.z_;

	return *this;
}

Vector3D Vector3D::operator-(const Vector3D& v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	z_ -= v.z_;

	return *this;
}

Vector3D Vector3D::operator*(const double d)
{
	x_ *= d;
	y_ *= d;
	z_ *= d;

	return *this;
}