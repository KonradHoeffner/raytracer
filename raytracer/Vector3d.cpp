#include "StdAfx.h"
#include "Vector3d.h"

using namespace std;

// Konstruktor ( erzeugt Nullvektor )
Vector3d::Vector3d()
{
	x = 0;
	y = 0;
	z = 0;
}

// Kontruktor, erzeugt einen Vektor mit vorgegebenen Werten
Vector3d::Vector3d(double X, double Y, double Z)
{
	x = X;
	y = Y;
	z = Z;
}

// Destruktor
Vector3d::~Vector3d()
{
}

void Vector3d::print()
{
	cout << "x= " << x << " y= " << y << " z= " << z << endl;
}

string Vector3d::toString()
{
	char c_str[50];
	sprintf(c_str," x: %lf y: %lf z: %lf",x,y,z);
	string s(c_str);
	return s;
}

// Gibt den Winkel zwischen dem Vector und einem übergebenen Anderen in Bogenmaß zurück.
double Vector3d::winkel(const Vector3d cVect ) const
{
	Vector3d a(x,y,z);
	a.normalize();
	return acos(a.dot(cVect.normalized()));
}

// Setzt die Komponenten auf neue Werte
void Vector3d::set( double X, double Y, double Z )
{
	x = X;
	y = Y;
	z = Z;
}

// normalisiert den Vektor
void Vector3d::normalize()
{
	double fLength = 1.0f / length(); 
	x *= fLength; 
	y *= fLength; 
	z *= fLength;
}

Vector3d Vector3d::normalized()  const
{
	Vector3d normiert(x,y,z);
	normiert.normalize();
	return normiert;
}

// Liefert die Länge des Vektors zurück
double Vector3d::length() const
{
	return (double)sqrt( x * x + y * y + z * z );
}

// Liefert das Quadrat der Länge des Vektors zurück
double	Vector3d::sqrLength()
{
	return x * x + y * y + z * z;
}

// Berechnet das Skalarprodukt mit cVect
double Vector3d::dot(const Vector3d cVect ) const
{
	return x * cVect.x + y * cVect.y + z * cVect.z;
}

// Berechnet das Kreuzprodukt mit cVect
Vector3d Vector3d::cross(const Vector3d cVect ) const
{
	return Vector3d( y * cVect.z - z * cVect.y, 
									z * cVect.x - x * cVect.z, 
									x * cVect.y - y * cVect.x );
}

Vector3d Vector3d::rotate(const Vector3d& vec, double w) const {
	Vector3d ergebnis;
	double tx,ty,tz;
	tx = x;
	ty = y;
	tz = z;
	double s = sin(w);
	double c = cos(w);
	
	ergebnis.x = (c+vec.x*vec.x*(1-c))*tx + ( vec.x*vec.y*(-c)-vec.z*s )*ty + (vec.x*vec.z*(1-c)+vec.y*s)*tz;
	ergebnis.y = (vec.y*vec.x*(1-c)+vec.z*s)*tx + (c+vec.y*vec.y*(1-c))*ty + (vec.y*vec.z*(1-c)-vec.x*s)*tz;
	ergebnis.z = (vec.z*vec.x*(1-c)-vec.y*s)*tx + (vec.z*vec.y*(1-c)+vec.x*s)*ty + (c+vec.z*vec.z*(1-c))*tz;
	return ergebnis;
}