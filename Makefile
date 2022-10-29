OBJ = main.o

raytracer: $(OBJ)
	g++ main.o -o raytracer
	rm -f main.o

$(OBJ):
	g++ -c main.cpp -I.

clean:
	rm -f $(OBJ) raytracer scene.bmp