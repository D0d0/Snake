#include "Vector3D.h"

Vector3D::Vector3D(Vector3D& another){
	x = another.getX();
	y = another.getY();
	z = another.getZ();
};


Vector3D::Vector3D(const Vector3D from, const Vector3D& to){
	x = to.x - from.x;
	y = to.y - from.y;
	z = to.z - from.z;
};

string Vector3D::toString(){
	stringstream stream;
	stream << "(" << x << ", " << y << ", " << z << ")" << endl;
	return stream.str();
};
float Vector3D::getLength(){
	return sqrtf(x*x + y*y + z*z);
};

void Vector3D::setLength(float length){
	normalize();
	x *= length;
	y *= length;
	z *= length;
};

void Vector3D::normalize(){
	float length = getLength();
	if (length != 0){
		x /= length;
		y /= length;
		z /= length;
	}
};

void Vector3D::minus(Vector3D vec){
	x -= vec.getX();
	y -= vec.getY();
	z -= vec.getZ();
};


void Vector3D::plus(Vector3D vec){
	x += vec.getX();
	y += vec.getY();
	z += vec.getZ();
};

void Vector3D::packTo01(){
	normalize();
	setLength(0.5f);

	x += 0.5f;
	y += 0.5f;
	z += 0.5f;
};

float Vector3D::dotProduct(Vector3D another){
	return (x*another.getX() + y*another.getY() + z*another.getZ());
};