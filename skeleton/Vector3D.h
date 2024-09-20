#pragma once

#include <cmath> 

class Vector3D
{
protected:
	float x, y, z;
public:
	Vector3D(); 
	Vector3D(float x, float y, float z);
	float Modulo();
	void Normalizar();
	float operator*(const Vector3D oVector) const;
	Vector3D operator*(const float esc) const;
	Vector3D operator+(const Vector3D oVector) const;
	Vector3D operator-(const Vector3D oVector) const;
	void operator=(const Vector3D oVector);
};

