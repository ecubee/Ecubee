CXX = g++
CFLAGS = -c -Wall -O3 -march=armv7-a -mtune=cortex-a8 -mfpu=vfp -mfloat-abi=softfp
LDFLAGS = -losg -lOpenThreads -losgGA -losgDB -losgUtil -losgViewer

BART_CFLAGS = -DBART
GERTJAN_CFLAGS = -DGERTJAN
MARTIJN_CFLAGS = -DMARTIJN

APP = EcubeE
INC = osg comm math mpu9150 eMPL
SRCS = main.cpp $(wildcard $(INC)/*.cpp) $(wildcard $(INC)/*.c) 
OBJS = $(SRCS:.cpp=.o)

FUSION_APP = fusion
FUSION_INC = glue mpu9150 eMPL
FUSION_SRCS = fusion.cpp $(wildcard $(FUSION_INC)/*.cpp) $(wildcard $(FUSION_INC)/*.c)
FUSION_OBJS = $(addprefix fusion/, $(FUSION_SRCS:.cpp=.o))
FUSION_CFLAGS = -DEMPL_TARGET_LINUX -DMPU9150 -DAK8975_SECONDARY
FUSION_PATHS = $(addprefix -I , $(FUSION_INC))

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
    
fusion: $(FUSION_OBJS)
	$(CXX) $^ -o $(FUSION_APP)

fusion/%.o: %.cpp
	mkdir -p fusion
	$(CXX) $(FUSION_CFLAGS) $(CFLAGS) $(FUSION_PATHS) $< -o $@

fusion/%.o: %.c
	mkdir -p fusion
	$(CXX) $(FUSION_CFLAGS) $(CFLAGS) $(FUSION_PATHS) $< -o $@

clean:
	rm -f $(APP) \
		  bart/*.o \
		  gertjan/*.o \
		  martijn/*.o \
		  fusion/*.o
