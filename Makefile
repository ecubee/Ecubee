SHELL = /bin/sh

HOST = $(shell hostname)
BBFLAGS = -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp -ftree-vectorize
CFLAGS = -c -Wall -O3 $(BBFLAGS) -DEMPL_TARGET_LINUX -DMPU9150 -DAK8975_SECONDARY -DMPU9150_TRACK -DSERIAL_TRACK
#Optional flags: -DMPU9150_TRACK -DI2C_DEBUG -DSERIAL_TRACK -DSERIAL_DEBUG -DMPU9150_DEBUG -DRASPBERRYPI $(BBFLAGS)
LDFLAGS = -losg -lOpenThreads -losgSim -losgGA -losgDB -losgUtil -losgViewer -lm -ldl -lGLESv2 -lXext -lX11
# -lGL

UPPER_HOST  = $(shell hostname | tr '[:lower:]' '[:upper:]')
CFLAGS += -D$(UPPER_HOST)

INC := osg comm math i2c eMPL
PATHS = $(addprefix -I$(CURDIR)/, $(INC))
SRCS := main.cpp $(foreach dir,$(INC),$(wildcard $(dir)/*.c*)) 
OBJS := $(notdir $(SRCS))
OBJS := $(OBJS:%.c=%.o)
OBJS := $(OBJS:%.cpp=%.o)
OBJS := $(addprefix $(HOST)obj/, $(OBJS))

CAL_APP := ecubeecal
CAL_INC := eMPL i2c math
CAL_SRCS := fusion.cpp $(foreach dir,$(CAL_INC),$(wildcard $(dir)/*.c*))
CAL_OBJS := $(notdir $(CAL_SRCS))
CAL_OBJS := $(CAL_OBJS:%.c=calobj/%.o)
CAL_OBJS := $(CAL_OBJS:%.cpp=calobj/%.o)

VPATH := $(INC) 

INSTALL ?= cp
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = ${INSTALL} -m 644
exec_prefix = /usr
bindir = $(exec_prefix)/bin
sysconfdir = $(prefix)/etc

.PHONY: clean veryclean all install install-cal

# Insert name target for which you want to compile
all: ecubee-$(HOST)

install: ecubee-$(HOST)
	-rm -f $(DESTDIR)$(bindir)/ecubee
	$(INSTALL_PROGRAM) ecubee-$(HOST) $(DESTDIR)$(bindir)
	ln -s $(DESTDIR)$(bindir)/ecubee-$(HOST) $(DESTDIR)$(bindir)/ecubee

ecubee-$(HOST): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(CAL_APP): $(CAL_OBJS)
	$(CXX) $^ -o $@

$(HOST)obj/%.o: %.cpp
	$(CXX) $(CFLAGS) $(BART_CFLAGS) $(PATHS) $< -o $@

$(HOST)obj/%.o: %.c
	$(CC) $(CFLAGS) $(BART_CFLAGS) $(PATHS) $< -o $@

calobj/%.o: %.cpp
	$(CXX) $(CFLAGS) $(CAL_CFLAGS) $(PATHS) $< -o $@

calobj/%.o: %.c
	$(CC) $(CFLAGS) $(CAL_CFLAGS) $(PATHS) $< -o $@


install-cal: $(CAL_APP)
	-mkdir $(DESTDIR)$(sysconfdir)/ecubee
	$(INSTALL_PROGRAM) $(CAL_APP) $(DESTDIR)$(bindir)

$(OBJS): | $(HOST)obj
$(CAL_OBJS): | calobj

%obj:
	-mkdir $@

clean:
	-rm -rf  bartobj \
		  gertjanobj \
		  martijnobj \
		  calobj

veryclean: clean
	-rm -f ecubee-* $(CAL_APP) $(DESTDIR)$(bindir)/ecubee-$(HOST) $(DESTDIR)$(bindir)/ecubee $(DESTDIR)$(bindir)/$(CAL_APP)
	-rm -f $(DESTDIR)$(sysconfdir)/ecubee/*cal.txt
