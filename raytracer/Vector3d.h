#ifndef CVECTOR_H
#define CVECTOR_H

//#include "common/definitions.h"

#include "StdAfx.h"


class Vector3d {
public:

	double x, y, z;

	// Konstruktor ( erzeugt Nullvektor )
	Vector3d();

	// Kontruktor, erzeugt einen Vektor mit vorgegebenen Werten
	Vector3d(double X, double Y, double Z);

	// Destruktor
	~Vector3d();
	
	// Setzt die Komponenten auf neue Werte
	void set( double X, double Y, double Z );

	// Ausgabe über cout
	void print();

	// Ausgabe als String
	std::string toString();

// Vektoroperationen

	// normalisiert den Vektor
	void normalize();

	// gibt den normierten Vektor zurück
	Vector3d normalized() const;

	// Liefert die Länge des Vektors zurück
	double length() const;

	// Liefert das Quadrat der Länge des Vektors zurück
	double	sqrLength();

	// Berechnet das Skalarprodukt mit cVect
	double dot(const Vector3d cVect) const;

	// Berechnet das Kreuzprodukt mit cVect
	Vector3d cross(const Vector3d cVect) const;

	// Berechnet den Winkel zwischen dem Vektor und cVect
	double winkel(const Vector3d cVect ) const;
	
	// Rotiert den Vektor um einen anderen um einen angegebenen Winkel in Bogenmaß
	Vector3d Vector3d::rotate(const Vector3d& vec, double w) const;

// arithmetische Operationen
//	Vector3d& operator += ( Vector3d& cVect ) { x += cVect.x; y += cVect.y; z += cVect.z; }
//	Vector3d& operator += ( Vector3d* cVect ) { x += cVect->x; y += cVect->y; z += cVect->z; }
	void operator += ( Vector3d& cVect ) { x += cVect.x; y += cVect.y; z += cVect.z; }
	void operator += ( Vector3d* cVect ) { x += cVect->x; y += cVect->y; z += cVect->z; }

//	Vector3d& operator -= ( Vector3d& cVect ) { x -= cVect.x; y -= cVect.y; z -= cVect.z; }
//	Vector3d& operator -= ( Vector3d* cVect ) { x -= cVect->x; y -= cVect->y; z -= cVect->z; }
	void operator -= ( Vector3d& cVect ) { x -= cVect.x; y -= cVect.y; z -= cVect.z; }
	void operator -= ( Vector3d* cVect ) { x -= cVect->x; y -= cVect->y; z -= cVect->z; }

	void operator *= ( double f ) { x *= f; y *= f; z *= f; }
//	Vector3d& operator *= ( Vector3d& cVect ) { x *= cVect.x; y *= cVect.y; z *= cVect.z; }
//	Vector3d& operator *= ( Vector3d* cVect ) { x *= cVect->x; y *= cVect->y; z *= cVect->z; }
	void operator *= ( Vector3d& cVect ) { x *= cVect.x; y *= cVect.y; z *= cVect.z; }
	void operator *= ( Vector3d* cVect ) { x *= cVect->x; y *= cVect->y; z *= cVect->z; }

	Vector3d operator- () const { return Vector3d( -x, -y, -z ); }
	
	friend Vector3d operator + ( const Vector3d& cVect1, const Vector3d& cVect2 ) { return Vector3d( cVect1.x + cVect2.x, cVect1.y + cVect2.y, cVect1.z + cVect2.z ); }
	friend Vector3d operator + ( const Vector3d& cVect1, Vector3d* cVect2 ) { return Vector3d( cVect1.x + cVect2->x, cVect1.y + cVect2->y, cVect1.z + cVect2->z ); }

	friend Vector3d operator - ( const Vector3d& cVect1, const Vector3d& cVect2 ) { return Vector3d( cVect1.x - cVect2.x, cVect1.y - cVect2.y, cVect1.z - cVect2.z ); }
	friend Vector3d operator - ( const Vector3d& cVect1, Vector3d* cVect2 ) { return Vector3d( cVect1.x - cVect2->x, cVect1.y - cVect2->y, cVect1.z - cVect2->z ); }

	friend Vector3d operator * ( const Vector3d& cVect, double f ) { return Vector3d( cVect.x * f, cVect.y * f, cVect.z * f ); }
	friend Vector3d operator * ( double f, const Vector3d& v ) { return Vector3d( v.x * f, v.y * f, v.z * f ); }
	//friend Vector3d operator * ( const Vector3d& cVect1, Vector3d& cVect2 ) { return Vector3d( cVect1.x * cVect2.x, cVect1.y * cVect2.y, cVect1.z * cVect2.z ); }
	
	// Skalarprodukt
	friend double operator * ( const Vector3d& cVect1, Vector3d& cVect2 ) { return cVect1.x * cVect2.x+cVect1.y * cVect2.y+cVect1.z * cVect2.z; }

		// Kreuzprodukt
	friend Vector3d operator % ( const Vector3d& cVect1, const Vector3d& cVect2) { return cVect1.cross(cVect2);}

	// Längenvergleich
	friend double operator < ( const Vector3d& cVect1, const Vector3d& cVect2) { return cVect1.length()<cVect2.length();}

	friend bool operator ==    ( const Vector3d& cVect1, const Vector3d& cVect2) { return cVect1.x==cVect2.x&&cVect1.y==cVect2.y&&cVect1.z==cVect2.z; }
	friend bool operator !=    ( const Vector3d& cVect1, const Vector3d& cVect2) { return !(cVect1.x==cVect2.x&&cVect1.y==cVect2.y&&cVect1.z==cVect2.z); }
	
};

#endif // CVECTOR_H
