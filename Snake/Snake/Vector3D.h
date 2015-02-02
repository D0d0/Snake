#pragma once
#include <sstream>
using namespace std;
class Vector3D{
	float x;
	float y;
	float z;
public:
	Vector3D() :x(0), y(0), z(0){};
	Vector3D(float nx, float ny, float nz) :x(nx), y(ny), z(nz){};
	Vector3D(Vector3D& another);
	Vector3D(const Vector3D from, const Vector3D& to);
	~Vector3D(){};
	string toString();
	float getX(){ return x; };
	float getY(){ return y; };
	float getZ(){ return z; };
	void setX(float nx){ x = nx; };
	void setY(float ny){ y = ny; };
	void setZ(float nz){ z = nz; };
	float getLength();
	void setLength(float length);
	void normalize();
	void minus(Vector3D vec);
	void plus(Vector3D vec);
	void packTo01();
	float dotProduct(Vector3D another);
};

