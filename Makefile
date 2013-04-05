CXX = g++
CFLAGS = -c -Wall -O3 -march=armv7-a -mtune=cortex-a8 -mfpu=vfp -mfloat-abi=softfp
LDFLAGS = -losg -lOpenThreads -losgGA -losgDB -losgUtil -losgViewer

BART_CFLAGS = -DBART
GERTJAN_CFLAGS = -DGERTJAN
MARTIJN_CFLAGS = -DMARTIJN

APP = EcubeE
SRCS = $(wildcard *.cpp) $(wildcard i2c/*.cpp)
OBJS = $(SRCS:.cpp=.o)

BART_OBJS = $(addprefix bart/, $(OBJS))
GERTJAN_OBJS = $(addprefix gertjan/, $(OBJS))
MARTIJN_OBJS = $(addprefix martijn/, $(OBJS))

.PHONY: clean all bart gertjan martijn

# Insert name target for which you want to compile
all: bart

bart: $(BART_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $(APP)
	
bart/%.o: %.cpp
	$(CXX) $(BART_CFLAGS) $(CFLAGS) $< -o $@
	
gertjan: $(GERTJAN_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $(APP)

gertjan/%.o: %.cpp
	$(CXX) $(GERTJAN_CFLAGS) $(CFLAGS) $< -o $@

martijn: $(MARTIJN_OBJS)
	mkdir -p martijn
	$(CXX) $(LDFLAGS) $^ -o $(APP)
	
martijn/%.o: %.cpp
	$(CXX) $(MARTIJN_CFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -f $(APP) \
		  bart/*.o \
		  gertjan/*.o \
		  martijn/*.o
