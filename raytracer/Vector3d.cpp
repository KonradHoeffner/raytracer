module;

#include <iostream>
#include <math.h>

export module Vector3d;

using namespace std;

export class Vector3d
{
	public:

	double x, y, z;

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

	// Konstruktor ( erzeugt Nullvektor )
	Vector3d()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	// Kontruktor, erzeugt einen Vektor mit vorgegebenen Werten
	Vector3d(double X, double Y, double Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	// Destruktor
	~Vector3d()
	{
	}

	void print()
	{
		cout << "x= " << x << " y= " << y << " z= " << z << endl;
	}

	string toString()
	{
		char c_str[50];
		sprintf(c_str," x: %lf y: %lf z: %lf",x,y,z);
		string s(c_str);
		return s;
	}

	// Gibt den Winkel zwischen dem Vector und einem übergebenen Anderen in Bogenmaß zurück.
	double winkel(const Vector3d cVect ) const
	{
		Vector3d a(x,y,z);
		a.normalize();
		return acos(a.dot(cVect.normalized()));
	}

	// Setzt die Komponenten auf neue Werte
	void set( double X, double Y, double Z )
	{
		x = X;
		y = Y;
		z = Z;
	}

	// normalisiert den Vektor
	void normalize()
	{
		double fLength = 1.0f / length();
		x *= fLength;
		y *= fLength;
		z *= fLength;
	}

	// gibt den normierten Vektor zurück
	Vector3d normalized()  const
	{
		Vector3d normiert(x,y,z);
		normiert.normalize();
		return normiert;
	}

	// Liefert die Länge des Vektors zurück
	double length() const
	{
		return (double)sqrt( x * x + y * y + z * z );
	}

	// Liefert das Quadrat der Länge des Vektors zurück
	double	sqrLength()
	{
		return x * x + y * y + z * z;
	}

	// Berechnet das Skalarprodukt mit cVect
	double dot(const Vector3d cVect ) const
	{
		return x * cVect.x + y * cVect.y + z * cVect.z;
	}

	// Berechnet das Kreuzprodukt mit cVect
	Vector3d cross(const Vector3d cVect ) const
	{
		return Vector3d( y * cVect.z - z * cVect.y,
										z * cVect.x - x * cVect.z,
										x * cVect.y - y * cVect.x );
	}

	// Rotiert den Vektor um einen anderen um einen angegebenen Winkel in Bogenmaß
	Vector3d rotate(const Vector3d& vec, double w) const {
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

};
