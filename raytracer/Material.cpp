module;

#include <string>

export module Material;

import Farbe;

export class Material {
public:
	std::string name;

	Farbe ambient;
	Farbe diffus;
	Farbe spiegelnd;

	double glanz;

	// friend double operator < (	const Dreieck& d1, const Dreieck& d2) { return
	// (d1.p1.x+d1.p2.x+d1.p3.x)<(d2.p1.x+d2.p2.x+d2.p3.x);}
	bool operator==(const Material &m2) {
		return ambient == m2.ambient && diffus == m2.diffus &&
					 spiegelnd == m2.spiegelnd && glanz == m2.glanz && name == m2.name;
	}

	/*friend bool operator ==	( const Material& m1, const Material& m2)
	{return
	m1.ambient==m2.ambient&&m1.diffus==m2.diffus&&m1.spiegelnd==m2.spiegelnd&&m1.glanz==m2.glanz&&m1.mattigkeit==m2.mattigkeit&&
	m1.undurchsichtigkeit==m2.undurchsichtigkeit&&m1.name==m2.name;}*/

	Material() {}

	Material(std::string name, Farbe ambient, Farbe diffus, Farbe spiegelnd,
					 double glanz) {
		this->name = name;
		this->ambient = ambient;
		this->diffus = diffus;
		this->spiegelnd = spiegelnd;
		this->glanz = glanz;
	}

	bool isSpiegelnd() const { return (spiegelnd.a != 1); }

	bool isTransparent() const { return (diffus.a != 1); }
};
