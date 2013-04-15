#CXX = g++
CFLAGS = -c -Wall -O3 
BBFLAGS = -march=armv7-a -mtune=cortex-a8 -mfpu=vfp -mfloat-abi=softfp
LDFLAGS = -losg -lOpenThreads -losgGA -losgDB -losgUtil -losgViewer

BART_CFLAGS = -DBART
GERTJAN_CFLAGS = -DGERTJAN
MARTIJN_CFLAGS = -DMARTIJN

APP := EcubeE
INC := osg comm math i2c eMPL
PATHS = $(addprefix -I$(CURDIR)/, $(INC))
SRCS := main.cpp $(foreach dir,$(INC),$(wildcard $(dir)/*.c*)) 
OBJS := $(notdir $(SRCS))
OBJS := $(OBJS:%.c=%.o)
OBJS := $(OBJS:%.cpp=%.o)

BART_OBJS = $(addprefix bart/, $(OBJS))
GERTJAN_OBJS = $(addprefix gertjan/, $(OBJS))
MARTIJN_OBJS = $(addprefix martijn/, $(OBJS))

FUSION_APP := fusion
FUSION_INC := eMPL i2c
FUSION_SRCS := fusion.cpp $(foreach dir,$(FUSION_INC),$(wildcard $(dir)/*.c*))
FUSION_OBJDIR := fusionobj

FUSION_OBJS := $(notdir $(FUSION_SRCS))
FUSION_OBJS := $(FUSION_OBJS:%.c=$(FUSION_OBJDIR)/%.o)
FUSION_OBJS := $(FUSION_OBJS:%.cpp=$(FUSION_OBJDIR)/%.o)
FUSION_CFLAGS = -DEMPL_TARGET_LINUX -DMPU9150 -DAK8975_SECONDARY
FUSION_PATHS = $(addprefix -I$(CURDIR)/, $(FUSION_INC))

VPATH := $(INC) 

.PHONY: clean all bart gertjan martijn $(FUSION_APP)

# Insert name target for which you want to compile
all: bart

bart: bartdir $(BART_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $(APP)
	
bart/%.o: %.cpp
	$(CXX) $(BART_CFLAGS) $(CFLAGS) $(BBFLAGS) $(PATHS) $< -o $@
	
bart/%.o: %.c
	$(CC) $(BART_CFLAGS) $(CFLAGS) $(BBFLAGS) $(PATHS) $< -o $@

gertjan: gertjandir $(GERTJAN_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $(APP)

gertjan/%.o: %.cpp
	$(CXX) $(GERTJAN_CFLAGS) $(CFLAGS) $(BBFLAGS) $(PATHS) $< -o $@

gertjan/%.o: %.c
	$(CC) $(GERTJAN_CFLAGS) $(CFLAGS) $(BBFLAGS) $(PATHS) $< -o $@

martijn: martijndir $(MARTIJN_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $(APP)
	
martijn/%.o: %.cpp
	$(CXX) $(MARTIJN_CFLAGS) $(CFLAGS) $(BBFLAGS) $(PATHS) $< -o $@

martijn/%.o: %.c
	$(CC) $(MARTIJN_CFLAGS) $(CFLAGS) $(BBFLAGS) $(PATHS) $< -o $@
    
fusion: fusiondir $(FUSION_OBJS)
	$(CXX) $(FUSION_OBJS) -o $(FUSION_APP)

fusionobj/%.o: %.cpp
	$(CXX) $(CFLAGS) $(FUSION_CFLAGS) $(FUSION_PATHS) $< -o $@

fusionobj/%.o: %.c
	$(CC) $(CFLAGS) $(FUSION_CFLAGS) $(FUSION_PATHS) $< -o $@

bartdir:
	mkdir -p bart

gertjandir:
	mkdir -p gertjan

martijndir:
	mkdir -p martijn

fusiondir:
	mkdir -p $(FUSION_OBJDIR)

clean:
	rm -rf $(APP) \
		  bart \
		  gertjan \
		  martijn \
		  $(FUSION_OBJDIR)
