SHELL = /bin/sh

BBFLAGS = -march=armv7-a -mtune=cortex-a8 -mfpu=vfp -mfloat-abi=softfp
CFLAGS = -c -Wall -O3 $(BBFLAGS) -DEMPL_TARGET_LINUX -DMPU9150 -DAK8975_SECONDARY -DMPU9150_DEBUG -DI2C_DEBUG
#Optional flags: -DI2C_DEBUG -DMPU9150_DEBUG -DRASPBERRYPI $(BBFLAGS)
LDFLAGS = -losg -lOpenThreads -losgSim -losgGA -losgDB -losgUtil -losgViewer -lm -ldl -lGLESv2 -lXext -lX11
# -lGL

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

BART_OBJS = $(addprefix bartobj/, $(OBJS))
GERTJAN_OBJS = $(addprefix gertjanobj/, $(OBJS))
MARTIJN_OBJS = $(addprefix martijnobj/, $(OBJS))

CAL_APP := ecubeecal
CAL_INC := eMPL i2c math
CAL_SRCS := imucal.c $(foreach dir,$(CAL_INC),$(wildcard $(dir)/*.c*))
CAL_OBJS := $(notdir $(CAL_SRCS))
CAL_OBJS := $(CAL_OBJS:%.c=calobj/%.o)
CAL_OBJS := $(CAL_OBJS:%.cpp=calobj/%.o)

VPATH := $(INC) 

INSTALL = cp
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = ${INSTALL} -m 644
exec_prefix = /usr
bindir = $(exec_prefix)/bin
sysconfdir = $(prefix)/etc

.PHONY: clean veryclean all bart gertjan martijn install install-ecubee install-bart install-martijn install-gertjan install-cal

# Insert name target for which you want to compile
all: bart
install: install-bart


bart: $(BART_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $(APP)

gertjan: $(GERTJAN_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $(APP)

martijn: $(MARTIJN_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $(APP)

$(CAL_APP): $(CAL_OBJS)
	$(CXX) $^ -o $(CAL_APP)


bartobj/%.o: %.cpp
	$(CXX) $(BART_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@

bartobj/%.o: %.c
	$(CC) $(BART_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@

gertjanobj/%.o: %.cpp
	$(CXX) $(GERTJAN_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@

gertjanobj/%.o: %.c
	$(CC) $(GERTJAN_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@

martijnobj/%.o: %.cpp
	$(CXX) $(MARTIJN_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@

martijnobj/%.o: %.c
	$(CC) $(MARTIJN_CFLAGS) $(CFLAGS) $(PATHS) $< -o $@

calobj/%.o: %.cpp
	$(CXX) $(CFLAGS) $(CAL_CFLAGS) $(PATHS) $< -o $@

calobj/%.o: %.c
	$(CC) $(CFLAGS) $(CAL_CFLAGS) $(PATHS) $< -o $@


install-ecubee:
	$(INSTALL_PROGRAM) $(APP) $(DESTDIR)$(bindir)

install-bart: bart install-ecubee install-cal
install-gertjan: gertjan install-ecubee
install-martijn: martijn install-ecubee

install-cal: $(CAL_APP)
	-mkdir $(DESTDIR)$(sysconfdir)/ecubee
	$(INSTALL_PROGRAM) $(CAL_APP) $(DESTDIR)$(bindir)

$(BART_OBJS): | bartobj
$(GERTJAN_OBJS): | gertjanobj
$(MARTIJN_OBJS): | martijnobj
$(CAL_OBJS): | calobj

%obj:
	-mkdir $@

clean:
	-rm -rf  bartobj \
		  gertjanobj \
		  martijnobj \
		  calobj

veryclean: clean
	-rm -f $(APP) $(CAL_APP) $(DESTDIR)$(bindir)/$(APP) $(DESTDIR)$(bindir)/$(CAL_APP)
	-rm -rf $(DESTDIR)$(sysconfdir)/ecubee
