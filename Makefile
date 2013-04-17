BBFLAGS = -march=armv7-a -mtune=cortex-a8 -mfpu=vfp -mfloat-abi=softfp
CFLAGS = -c -Wall -O3 $(BBFLAGS) -DEMPL_TARGET_LINUX -DMPU9150 -DAK8975_SECONDARY -DMPU9150_DEBUG
#Optional flags: -DI2C_DEBUG -DMPU9150_DEBUG -DRASPBERRYPI $(BBFLAGS)
LDFLAGS = -losg -lOpenThreads -losgGA -losgDB -losgUtil -losgViewer

BART_CFLAGS = -DBART
GERTJAN_CFLAGS = -DGERTJAN
MARTIJN_CFLAGS = -DMARTIJN

APP := ecubee
INC := osg comm math i2c eMPL
PATHS = $(addprefix -I$(CURDIR)/, $(INC))
SRCS := main.cpp $(foreach dir,$(INC),$(wildcard $(dir)/*.c*)) 
OBJS := $(notdir $(SRCS))
OBJS := $(OBJS:%.c=%.o)
OBJS := $(OBJS:%.cpp=%.o)

BART_OBJS = $(addprefix bart/, $(OBJS))
GERTJAN_OBJS = $(addprefix gertjan/, $(OBJS))
MARTIJN_OBJS = $(addprefix martijn/, $(OBJS))

CAL_APP := ecubeecal
CAL_INC := eMPL i2c math
CAL_SRCS := fusion.cpp $(foreach dir,$(CAL_INC),$(wildcard $(dir)/*.c*))
CAL_OBJS := $(notdir $(CAL_SRCS))
CAL_OBJS := $(CAL_OBJS:%.c=cal/%.o)
CAL_OBJS := $(CAL_OBJS:%.cpp=cal/%.o)

VPATH := $(INC) 

.PHONY: clean veryclean all bart gertjan martijn install-ecubee install-bart install-martijn install-gertjan install-cal

# Insert name target for which you want to compile
all: bart
install: install-bart

bart: bartdir $(BART_OBJS)
	$(CXX) $(LDFLAGS) $(BART_OBJS) -o $(APP)
	
bart/%.o: %.cpp
	$(CXX) $(BART_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@
	
bart/%.o: %.c
	$(CC) $(BART_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@

gertjan: gertjandir $(GERTJAN_OBJS)
	$(CXX) $(LDFLAGS) $(GERTJAN_OBJS) -o $(APP)

gertjan/%.o: %.cpp
	$(CXX) $(GERTJAN_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@

gertjan/%.o: %.c
	$(CC) $(GERTJAN_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@

martijn: martijndir $(MARTIJN_OBJS)
	$(CXX) $(LDFLAGS) $(MARTIJN_OBJS) -o $(APP)
	
martijn/%.o: %.cpp
	$(CXX) $(MARTIJN_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@

martijn/%.o: %.c
	$(CC) $(MARTIJN_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@
    
$(CAL_APP): caldir $(CAL_OBJS)
	$(CXX) $(CAL_OBJS) -o $(CAL_APP)

cal/%.o: %.cpp
	$(CXX) $(CFLAGS) $(CAL_CFLAGS) $(PATHS) $< -o $@

cal/%.o: %.c
	$(CC) $(CFLAGS) $(CAL_CFLAGS) $(PATHS) $< -o $@

install-ecubee:
	mv $(APP) /usr/bin

install-bart: bart install-ecubee install-cal
install-gertjan: gertjan install-ecubee
install-martijn: martijn install-ecubee

install-cal: $(CAL_APP)
	mkdir -p /etc/ecubee
	mv $(CAL_APP) /usr/bin

bartdir:
	mkdir -p bart

gertjandir:
	mkdir -p gertjan

martijndir:
	mkdir -p martijn

caldir:
	mkdir -p cal

clean:
	rm -rf  bart \
		  gertjan \
		  martijn \
		  cal

veryclean: clean
	rm -f $(APP) $(CAL_APP) /usr/bin/$(APP) /usr/bin/$(CAL_APP)
	rm -rf /etc/ecubee
