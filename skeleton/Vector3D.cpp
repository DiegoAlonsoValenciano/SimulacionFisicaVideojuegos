#include "Vector3D.h"

Vector3D::Vector3D()
	:x(0.0f), y(0.0f), z(0.0f)
{}

Vector3D::Vector3D(float x, float y, float z)
	:x(x), y(y), z(z)
{}

float Vector3D::Modulo() {
	float m = x * x + y * y + z * z;
	m = sqrt(m);
	return m;
}

void Vector3D::Normalizar() {
	float m = Modulo();
	x = x / m;
	y = y / m;
	z = z / m;
}

float Vector3D::operator*(const Vector3D oVector) const {
	float e = x * oVector.x + y * oVector.y + z + oVector.z;
	return e;
}

Vector3D Vector3D::operator*(const float esc) const {
	Vector3D e = Vector3D(x * esc, y * esc, z * esc);
	return e;
}

Vector3D Vector3D::operator+(const Vector3D oVector) const {
	Vector3D s = Vector3D(x + oVector.x, y + oVector.y, z + oVector.z);
	return s;
}

Vector3D Vector3D::operator-(const Vector3D oVector) const {
	Vector3D r = Vector3D(x - oVector.x, y - oVector.y, z - oVector.z);
	return r;
}

void Vector3D::operator=(const Vector3D oVector) {
	x = oVector.x;
	y = oVector.y;
	z = oVector.z;
}