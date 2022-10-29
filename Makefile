OBJ = main.o

raytracer: $(OBJ)
	g++ main.o -o raytracer
	rm -f main.o

$(OBJ):
	g++ -c main.cpp -Iinclude/

deps:
	chmod +x deps.sh
	./deps.sh

clean:
	rm -f $(OBJ) raytracer scene.bmp