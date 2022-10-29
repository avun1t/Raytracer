#ifndef __RAY_H_
#define __RAY_H_

#include "vect.h"

class Ray {
	Vect origin, direction;

public:
	Ray();
	Ray(Vect, Vect);

	// getter functions
	Vect getRayOrigin() { return origin; }
	Vect getRayDirection() { return direction; }
};

Ray::Ray()
{
	origin = Vect(0,0,0);
	direction = Vect(1,0,0);
}

Ray::Ray(Vect o, Vect d)
{
	origin = o;
	direction = d;
}

#endif // __RAY_H_