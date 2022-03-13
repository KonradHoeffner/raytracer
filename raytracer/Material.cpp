// Material.cpp: Implementierung der Klasse Material.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Material.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Material::Material()
{

}

Material::Material(string name, Farbe ambient, Farbe diffus, Farbe spiegelnd, double glanz)
{
	this->name = name;
	this->ambient = ambient;
	this->diffus = diffus;
	this->spiegelnd = spiegelnd;
	this->glanz = glanz;
}

Material::~Material()
{

}

bool Material::isSpiegelnd() const 
{
	return (spiegelnd.a!=1);
}

bool Material::isTransparent() const
{
	return (diffus.a!=1);
}
