#CROSS           = arm-linux-gnueabihf-
CROSS            =
CC               = $(CROSS)gcc
CPPC		 = $(CROSS)g++
OBJS             = main.o
TARGET           = solarmonitor
UNZIP            = unzip
XIVELYLIBDIR     = ./libxively
XIVELYLIB        = $(XIVELYLIBDIR)/libxively.a
CFLAGS           = -I. -I$(XIVELYLIBDIR) -L$(XIVELYLIBDIR) -lxively
CFLAGS          += -Os -g

.PHONY: clean purge all

all: $(TARGET)

.cpp.o:
	@echo "========================================================"
	$(CPPC) $(CFLAGS) -c $<

.c.o:
	@echo "========================================================"
	$(CC) $(CFLAGS) -c $<

$(XIVELYLIB):
	make -C $(XIVELYLIBDIR)

$(TARGET): $(XIVELYLIB) $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	@echo "Clean project =========================================="
	make -C $(XIVELYLIBDIR) clean
	rm -fr $(TARGET) $(OBJS)

purge:
	rm -f *~ *bak

depend: $(OBJS:.o=.cpp)
	-@ makedepend -- $(CFLAGS) -- -Y $^ -f Makefile 2> /dev/null
# DO NOT DELETE
