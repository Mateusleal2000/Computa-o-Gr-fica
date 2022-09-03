output: main.o display.o sphere.o utils.o
	g++ -o main main.o display.o sphere.o utils.o
	./main
	rm -rf *.o main

display.o: display.cpp display.h
	g++ -c display.cpp

sphere.o: sphere.cpp sphere.h
	g++ -c sphere.cpp

clean:
	rm -rf *.o main