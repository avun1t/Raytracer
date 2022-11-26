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
	void setColorRgbs(double redValue, double greenValue, double blueValue, double specialValue = 0) { red = redValue; green = greenValue; blue = blueValue; special = specialValue; }

	// helper functions
	double brightness()
	{
		return (red + green + blue)/3;
	}
	
	Color colorScalar(double scalar)
	{
		return Color(red*scalar, green*scalar, blue*scalar, special);
	}
	
	Color colorAdd(Color color)
	{
		return Color(red + color.getColorRed(), green + color.getColorGreen(), blue + color.getColorBlue(), special);
	}
	
	Color colorMultiply(Color color)
	{
		return Color(red*color.getColorRed(), green*color.getColorGreen(), blue*color.getColorBlue(), special);
	}
	
	Color colorAverage(Color color)
	{
		return Color((red + color.getColorRed())/2, (green + color.getColorGreen())/2, (blue + color.getColorBlue())/2, special);
	}

	double clamp(double d, double min, double max)
	{
		const double t = d < min ? min : d;
		return t > max ? max : t;
	}
	
	Color clip()
	{
		double alllight = red + green + blue;
		double excesslight = alllight - 3;

		if (excesslight > 0) {
			red = red + excesslight*(red/alllight);
			green = green + excesslight*(green/alllight);
			blue = blue + excesslight*(blue/alllight);
		}

		// i will archive this piece of art
		// so everyone sees how not to write code
		//if (red > 1) {red = 1;}
		//if (green > 1) {green = 1;}
		//if (blue > 1) {blue = 1;}
		//if (red < 0) {red = 0;}
		//if (green < 0) {green = 0;}
		//if (blue < 0) {blue = 0;}

		red = clamp(red, 0, 1);
		green = clamp(green, 0, 1);
		blue = clamp(blue, 0, 1);
		
		return Color(red, green, blue, special);
	}
};

Color::Color()
{
	setColorRgbs(0.5, 0.5, 0.5, 0);
}

Color::Color(double r, double g, double b, double s)
{
	setColorRgbs(r, g, b, s);
}

#endif // __COLOR_H_