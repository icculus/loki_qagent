OBJECTS = detect.o

CC = gcc
CPP = gcc

VERSION = 0.0.1

WARNFLAG =

CFLAGS = -pipe -g
CPPFLAGS = -pipe -g

detect : detect.o
	gcc -pipe -g -L/usr/local/lib -static -o detect $(OBJECTS) /usr/local/lib/libdetect.a
	strip detect

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o : %.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

clean:
	rm $(OBJECTS) detect


  