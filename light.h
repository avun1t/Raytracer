#ifndef __LIGHT_H_
#define __LIGHT_H_

#include "vect.h"
#include "color.h"

class Light {
	Vect position;
	Color color;

public:
	Light();
	Light(Vect, Color);

	// getter functions
	Vect getLightPosition() { return position; }
	Color getLightColor() { return color; }
};

Light::Light()
{
	position = Vect(0,0,0);
	color = Color(1,1,1,0);
}

Light::Light(Vect p, Color c)
{
	position = p;
	color = c;
}

#endif // __LIGHT_H_