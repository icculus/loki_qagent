include ../host.def

.PHONY: all

all: qagent

CC=gcc
CPP=gcc

objects = main.o

LINKFLAGS=

qagent: $(objects)

	$(CPP) $(LINKFLAGS) -o $@ $(objects) -L/usr/X11R6/lib -lX11

%.o : %.cpp
	$(CPP) -c $< -o $@ $(CPPFLAGS)

clean:
	rm $(objects) qagent
