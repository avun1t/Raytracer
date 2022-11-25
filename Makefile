OBJ = main.o

raytracer: $(OBJ)
	g++ main.o -o raytracer
	rm -f main.o

$(OBJ):
	g++ -c -O3 main.cpp -Iinclude/

clean:
	rm -f $(OBJ) raytracer scene.bmp
