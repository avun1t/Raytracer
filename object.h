#ifndef __OBJECT_H_
#define __OBJECT_H_

#include "ray.h"
#include "vect.h"
#include "color.h"

class Object {
public:
	Object();

	// getter functions
	Color getObjectColor() { return Color(0.0, 0.0, 0.0, 0); }

	double findIntersection(Ray ray)
	{
		return 0;
	}
};

Object::Object()
{}

#endif // __OBJECT_H_