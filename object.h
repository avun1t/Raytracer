#ifndef __OBJECT_H_
#define __OBJECT_H_

#include "ray.h"
#include "vect.h"
#include "color.h"

class Object {	
public:
	Object();
	
	// getter functions
	virtual Color getColor() { return Color (0.0, 0.0, 0.0, 0); }
	
	virtual Vect getNormalAt(Vect intersection_position)
	{
		return Vect (0, 0, 0);
	}

	// helper functions
	virtual double findIntersection(Ray ray)
	{
		return 0;
	}
};

Object::Object()
{}

#endif // __OBJECT_H_