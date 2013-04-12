CXX = g++
CFLAGS = -c -Wall -O3 -march=armv7-a -mtune=cortex-a8 -mfpu=vfp -mfloat-abi=softfp
LDFLAGS = -losg -lOpenThreads -losgGA -losgDB -losgUtil -losgViewer

BART_CFLAGS = -DBART
GERTJAN_CFLAGS = -DGERTJAN
MARTIJN_CFLAGS = -DMARTIJN

APP = EcubeE
INC = osg comm math i2c eMPL
SRCS = main.cpp $(wildcard $(INC)/*.cpp) $(wildcard $(INC)/*.c) 
OBJS = $(SRCS:.cpp=.o)

FUSION_APP = fusion
FUSION_INC = eMPL i2c
FUSION_SRCS = fusion.cpp $(wildcard $(FUSION_INC)/*.cpp) $(wildcard $(FUSION_INC)/*.c)
FUSION_OBJDIR = fusionobj

FUSION_OBJS := $(patsubst %.cpp, $(FUSION_OBJDIR)/%.o, $(notdir $(FUSION_SRCS)))

FUSION_CFLAGS = -DEMPL_TARGET_LINUX -DMPU9150 -DAK8975_SECONDARY
FUSION_PATHS = $(addprefix -I$(CURDIR)/, $(FUSION_INC))

VPATH := $(sort  $(dir $(FUSION_SRCS)))

BART_OBJS = $(addprefix bart/, $(OBJS))
GERTJAN_OBJS = $(addprefix gertjan/, $(OBJS))
MARTIJN_OBJS = $(addprefix martijn/, $(OBJS))

.PHONY: clean all bart gertjan martijn $(FUSION_APP)

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
    
fusion: fusiondir $(FUSION_OBJS)
	$(CXX) $^ -o $(FUSION_APP)

fusionobj/%.o: %.cpp
	$(CXX) $(FUSION_CFLAGS) $(CXXFLAGS) $(FUSION_PATHS) $< -o $@

fusionobj/%.o: %.c
	$(CC) $(FUSION_CFLAGS) $(CCFLAGS) $(FUSION_PATHS) $< -o $@

fusiondir:
	mkdir -p $(FUSION_OBJDIR)

clean:
	rm -rf $(APP) \
		  bart/*.o \
		  gertjan/*.o \
		  martijn/*.o \
		  $(FUSION_OBJDIR)
