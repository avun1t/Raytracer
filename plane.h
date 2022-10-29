#ifndef __PLANE_H_
#define __PLANE_H_

#include <math.h>
#include "object.h"
#include "vect.h"
#include "color.h"

class Plane : public Object {
	Vect normal;
	double distance;
	Color color;
	
public:
	Plane();
	Plane(Vect, double, Color);
	
	// getter functions
	Vect getPlaneNormal () { return normal; }
	double getPlaneDistance () { return distance; }
	virtual Color getColor () { return color; }
	
	virtual Vect getNormalAt(Vect point)
	{
		return normal;
	}
	
	// helper functions
	virtual double findIntersection(Ray ray)
	{
		Vect ray_direction = ray.getRayDirection();
		
		double a = ray_direction.dotProduct(normal);
		
		if (a == 0) {
			// ray is parallel to the plane
			return -1;
		} else {
			double b = normal.dotProduct(ray.getRayOrigin().vectAdd(normal.vectMult(distance).negative()));
			return -1*b/a;
		}
	}
	
};

Plane::Plane()
{
	normal = Vect(1,0,0);
	distance = 0;
	color = Color(0.5,0.5,0.5, 0);
}

Plane::Plane(Vect normalValue, double distanceValue, Color colorValue)
{
	normal = normalValue;
	distance = distanceValue;
	color = colorValue;
}

#endif // __PLANE_H_