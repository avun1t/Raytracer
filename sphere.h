#ifndef __SPHERE_H_
#define __SPHERE_H_

#include <math.h>
#include "object.h"
#include "vect.h"
#include "color.h"

class Sphere : public Object {
	Vect center;
	double radius;
	Color color;

public:
	Sphere();
	Sphere(Vect, double, Color);

	// getter functions
	Vect getSphereCenter() { return center; }
	double getSphereRadius() { return radius; }
	Color getSphereColor() { return color; }
};

Sphere::Sphere()
{
	center = Vect(0,0,0);
	radius = 1.0;
	color = Color(0.5,0.5,0.5,0);
}

Sphere::Sphere(Vect centerValue, double radiusValue, Color colorValue)
{
	center = centerValue;
	radius = radiusValue;
	color = colorValue;
}

#endif // __SPHERE_H_