all: main.o
	g++ -o beaverfever main.o

main.o: main.cpp
	g++ -c -o main.o main.cpp

clean:
	rm beaverfever.exe *.o
