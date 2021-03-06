export module Vector3d;

import <string>;
import <cmath>;

export class Vector3d
{
	public:

	double x, y, z;

// arithmetische Operationen
	void operator += ( Vector3d& cVect ) { x += cVect.x; y += cVect.y; z += cVect.z; }
	void operator += ( Vector3d* cVect ) { x += cVect->x; y += cVect->y; z += cVect->z; }

	void operator -= ( Vector3d& cVect ) { x -= cVect.x; y -= cVect.y; z -= cVect.z; }
	void operator -= ( Vector3d* cVect ) { x -= cVect->x; y -= cVect->y; z -= cVect->z; }

	void operator *= ( double f ) { x *= f; y *= f; z *= f; }
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

	// L??ngenvergleich
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

	std::string toString()
	{
		return std::string(" x: ")+std::to_string(x)+std::string("y: ")+std::to_string(y)+std::string(" z: ")+std::to_string(z);
	}

	// Gibt den Winkel zwischen dem Vector und einem ??bergebenen Anderen in Bogenma?? zur??ck.
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
	// gibt den normierten Vektor zur??ck
	Vector3d normalized()  const
	{
		Vector3d normiert(x,y,z);
		normiert.normalize();
		return normiert;
	}

	// Liefert die L??nge des Vektors zur??ck
	double length() const
	{
		return (double)sqrt( x * x + y * y + z * z );
	}

	// Liefert das Quadrat der L??nge des Vektors zur??ck
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

	// Rotiert den Vektor um einen anderen um einen angegebenen Winkel in Bogenma??
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
