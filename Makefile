CC = g++

GCCFLAGS = -std=c++11 -fpcc-struct-return
CFLAGS = -g
INCLUDE = -I/usr/include
LDFLAGS = -L/usr/lib/
LDLIBS =  -lGLU -lGL -lglut -lm

project: askisi.o triangulate.o functions.o
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) $(LDFLAGS) -o project askisi.o triangulate.o functions.o $(LDLIBS)
