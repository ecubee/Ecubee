CSRCS=$(wildcard *.cpp)

CFLAGS =  -c -O3 -D BART -D SIMULATION

INCLUDE = -I. -I/usr/include/ -I/usr/include/X11/ -I/usr/local/include/GL 
INCOSG = -I $(HOME)/OpenSceneGraph/include
LDLIBS = -lm -ldl -lGL -lGLU -lpthread -lXext -lX11

LDFLAGS =  -L. -L/usr/lib -L/usr/X11R6/lib -L/usr/local/lib
LDOSG = -L $(HOME)/OpenSceneGraph/lib -losg -losgViewer -losgSim -losgUtil
COBJS=$(patsubst %.cpp,build/%.o,$(CSRCS))

CC = g++

EXE=ecubee

all: $(EXE)

$(EXE): $(COBJS) 
	g++ -o$(EXE) $(COBJS) $(INCLUDE) $(INCOSG) $(LDFLAGS) $(LDLIBS) $(LDOSG)


build/%.o : %.cpp 
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	$(RM) $(COBJS) $(EXE)
