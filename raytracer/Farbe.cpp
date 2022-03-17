module;

#include <algorithm>

export module Farbe;

export class Farbe
{
	public:

	double r,g,b,a;

	void operator = (const Farbe& f) {r=f.r;g=f.g;b=f.b;a=f.a;cap_negativ();}
	bool operator == (const Farbe& f) { return r==f.r&&g==f.g&&b==f.b&&a==f.a; }
	Farbe operator * (const Farbe& f) { return Farbe(r*f.r,g*f.g,b*f.b,a*f.a); }
	Farbe operator * (double d)		  {Farbe ergebnis(r*d,g*d,b*d,1);ergebnis.cap_negativ();return ergebnis;}
	Farbe operator + (const Farbe& f) {Farbe ergebnis(r+f.r,g+f.g,b+f.b,1);ergebnis.cap_negativ();return ergebnis; }

	Farbe()
	{
		r=1;
		g=1;
		b=1;
		a=1;
	}

	Farbe(double r,double g,double b)
	{
		this->r=r;
		this->g=g;
		this->b=b;
		a=1;
		cap_negativ();
	}

	Farbe(double r,double g,double b,double a)
	{
		this->r=r;
		this->g=g;
		this->b=b;
		this->a=a;
		cap_negativ();
	}

	~Farbe()
	{

	}

	std::string toString()
	{
		return std::string(" r: ")+std::to_string(r)+std::string("g: ")+std::to_string(g)+std::string(" b: ")+std::to_string(b)+std::string(" a: ")+std::to_string(a);
	}

	void set(double r,double g,double b)
	{
		this->r=r;
		this->g=g;
		this->b=b;
		a=1;
		cap_negativ();
	}

	void set(double r,double g,double b,double a)
	{
		this->r=r;
		this->g=g;
		this->b=b;
		this->a=a;
		cap_negativ();
	}

	// Sorgt dafür, dass kein Farbwert größer 1 oder kleiner 0 vorkommt
	void cap()
	{
		r = std::max(std::min(r,1.0),0.0);
		g = std::max(std::min(g,1.0),0.0);
		b = std::max(std::min(b,1.0),0.0);
		a = std::max(std::min(a,1.0),0.0);
	}

	// Sorgt dafür, dass kein Farbwert kleiner 0 vorkommt
	void cap_negativ()
	{
		r = std::max(r,0.0);
		g = std::max(g,0.0);
		b = std::max(b,0.0);
		a = std::max(a,0.0);
	}

};
