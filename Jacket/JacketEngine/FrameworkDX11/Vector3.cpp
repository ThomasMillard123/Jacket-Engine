#include "Vector3.h"

Vector3A::Vector3A()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3A::Vector3A(float x, float y, float z):x(x),y(y),z(z)
{
}

Vector3A::Vector3A(const Vector3A& Vec)
{
	x = Vec.x;
	y = Vec.y;
	z = Vec.z;
}

Vector3A Vector3A::operator+(const Vector3A& vec)
{
	return Vector3A(x+vec.x,y+vec.y,z+vec.z);
}

Vector3A& Vector3A::operator+=(const Vector3A& vec)
{

	//Returns ‘this’ pointer (i.e. self-reference summing the values for 
	//each component with the corresponding component in the added vector

	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;

}

Vector3A Vector3A::operator-(const Vector3A& vec)
{
	return Vector3A(x - vec.x, y - vec.y, z - vec.z);
}

Vector3A& Vector3A::operator-=(const Vector3A& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

Vector3A Vector3A::operator*(float value)
{
	return Vector3A(x * value, y * value, z * value);
}

Vector3A& Vector3A::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vector3A Vector3A::operator/(float value)
{
	assert(value != 0);
	return Vector3A(x / value, y / value, z / value);
}

Vector3A& Vector3A::operator/=(float value)
{
	assert(value != 0);
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

Vector3A& Vector3A::operator=(const Vector3A& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;

	return *this;
}


float Vector3A::dot_product(const Vector3A& vec)
{

	return x*vec.x+y*vec.y+z*vec.z;
}

Vector3A Vector3A::cross_product(const Vector3A& vec)
{
	float ni=y*vec.z-z*vec.y;
	float nj= z * vec.x - x * vec.z;
	float nk= x * vec.y - y * vec.x;

	return Vector3A(ni,nj,nk);
}

Vector3A Vector3A::normalization()
{
	Vector3A vecReturn;
	vecReturn.x = x / magnitude();
	vecReturn.y = y / magnitude();
	vecReturn.z = z / magnitude();

	if (x == 0) {
		vecReturn.x = 0;
	}
	if (y == 0) {
		vecReturn.y = 0;
	}
	if (z == 0) {
		vecReturn.z = 0;
	}
	return vecReturn;
}

float Vector3A::square()
{
	return x*x+y*y+z*z;
}

float Vector3A::distance(const Vector3A& vec)
{
	float X = x - vec.x;
	float Y = y - vec.y;
	float Z = z - vec.z;
	return sqrt(((X*X)+(Y*Y)+(Z*Z)));
}

float Vector3A::magnitude()
{
	return sqrt(x * x + y * y + z * z);
}

bool Vector3A::operator!=(const Vector3A& vec)
{
	if (x == vec.x && y == vec.y && z == vec.z) {
		return true;
	}
	return false;
}
