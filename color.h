#ifndef __COLOR_H_
#define __COLOR_H_

class Color {
	double red, green, blue, special;

public:
	Color();
	Color(double, double, double, double);

	// getter functions
	double getColorRed() { return red; }
	double getColorGreen() { return green; }
	double getColorBlue() { return blue; }
	double getColorSpecial() { return special; }

	// setter functions
	void setColorRed(double redValue) { red = redValue; }
	void setColorGreen(double greenValue) { green = greenValue; }
	void setColorBlue(double blueValue) { blue = blueValue; }
	void setColorSpecial(double specialValue) { special = specialValue; }
};

Color::Color()
{
	red = 0.5;
	green = 0.5;
	blue = 0.5;
}

Color::Color(double r, double g, double b, double s)
{
	red = r;
	green = g;
	blue = b;
	special = s;
}

#endif // __COLOR_H_