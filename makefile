all: main

main: main.o display.o sphere.o object.o utils.o 
	g++ -o main main.o display.o sphere.o object.o utils.o
	./main
	rm -rf *.o main

display.o: display.cpp display.h
	g++ -c display.cpp

sphere.o: sphere.cpp sphere.h
	g++ -c sphere.cpp

object.o: object.cpp object.h
	g++ -c object.cpp

utils.o: utils.cpp utils.h
	g++ -c utils.cpp

clean:
	rm -rf *.o main