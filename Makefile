PROGRAM = main
CC = g++
CFLAGS  = -std=c++1z -g -Wall -Wextra
LDLIBS = -lGL -lGLU -lglut -lm

main: main.o pso.o
	$(CC) $(CFLAGS)  -o main *.o $(LDLIBS)
main.o: main.cpp  
	$(CC) $(CFLAGS) -c main.cpp $(LDLIBS)
pso.o: sources/pso.cpp headers/pso.hpp
	$(CC) $(CFLAGS) -c sources/pso.cpp $(LDLIBS)

clean:
	@rm -f *.o main
