PROGRAM = main
CC = g++
CFLAGS  = -std=c++1z -g -Wall -Wextra
LDLIBS = -lGL -lGLU -lglut -lm

main: main.o pso.o image.o textures.o write.o
	$(CC) $(CFLAGS)  -o main *.o $(LDLIBS)
main.o: sources/main.cpp  
	$(CC) $(CFLAGS) -c sources/main.cpp $(LDLIBS)
pso.o: sources/pso.cpp headers/pso.hpp
	$(CC) $(CFLAGS) -c sources/pso.cpp $(LDLIBS)
image.o: sources/image.cpp headers/image.h
	$(CC) $(CFLAGS) -c sources/image.cpp $(LDLIBS)
textures.o: sources/textures.cpp headers/textures.hpp
	$(CC) $(CFLAGS) -c sources/textures.cpp $(LDLIBS)
write.o: sources/write.cpp headers/write.hpp
	$(CC) $(CFLAGS) -c sources/write.cpp $(LDLIBS)

clean:
	@rm -f *.o main

.PHONY: run
run:
	@./main
