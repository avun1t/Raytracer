#ifndef __SOURCE_H_
#define __SOURCE_H_

class Source {
public:
	Source();
	
	// getter functions
	virtual Vect getLightPosition() {return Vect(0, 0, 0);}
	virtual Color getLightColor() {return Color(1, 1, 1, 0);}
};

Source::Source()
{}

#endif // __SOURCE_H_