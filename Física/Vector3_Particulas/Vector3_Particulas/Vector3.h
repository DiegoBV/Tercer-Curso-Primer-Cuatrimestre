#pragma once
#include <math.h>
class Vector3
{
private:
	//padding
	float pad;

public:
	//componente x del vector
	float x;
	//componente y del vector
	float y;
	//componente z del vector
	float z;

	//constructor por defecto, inicializa valores a 0
	Vector3() : x(0), y(0), z(0) {};
	//constructor explícito
	Vector3(float x,  float y,  float z) : x(x), y(y), z(z) {};
	//destructora por defecto de la clase
	virtual ~Vector3() {};
	//metodo de inversion de todos los componentes del vector
	void invert();
	//obtencion de la magnitud del vector al cuadrado
	float squareMagnitude() const;
	//obtencion de la magnitud del vector
	float magnitude() const;
	//Multiplica todos los elementos de un vector por un escalar
	void operator*=(const float k);
	//Devuelve una copia de un vector multiplicado por un escalar
	Vector3 operator*(const float k);
	//normaliza el vector (modulo = 1)
	void normalize();
	//Operator +
	Vector3 operator+(const Vector3& other);
	//Operator +=
	void operator+=(const Vector3& other);
	//Operator -
	Vector3 operator-(const Vector3& other);
	//Operator -=
	void operator-=(const Vector3& other);
	//Producto escalar
	float operator*(const Vector3& v) const;
	//Producto escalar
	float dot(const Vector3& v);
	//Operator %, producto vectorial
	Vector3 operator%(const Vector3& v);
	//Producto Vectorial
	Vector3 vectorProduct(const Vector3& v);
	// Definición del constructor copia
	Vector3(const Vector3 &p): x(p.x), y(p.y), z(p.z) {}
};

