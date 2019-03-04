#
# Basic KallistiOS skeleton / test program
# Copyright (C)2001-2004 Dan Potter
#

CDI_RESULT = dream_sphere.cdi

# Put the filename of the output binary here
TARGET = dream_sphere.elf

# List all of your C files here, but change the extension to ".o"
# Include "romdisk.o" if you want a rom disk.
OBJS = dream_sphere.o romdisk.o vertex.o world_options.o world_va.o game_cxt.o vec_utils.o menu_cxt.o pause_cxt.o

# If you define this, the Makefile.rules will create a romdisk.o for you
# from the named dir.
KOS_ROMDISK_DIR = romdisk

# The rm-elf step is to remove the target before building, to force the
# re-creation of the rom disk.
all: rm-elf $(CDI_RESULT)

include $(KOS_BASE)/Makefile.rules

# temporarily building to parent folder. will use subdirs later
$(CDI_RESULT): $(TARGET) 1st_read.bin
	mkisofs -C 0,11702 -V DreamSphere -G IP.BIN -joliet -rock -l -o ../dream_sphere.iso .
	cdi4dc/cdi4dc.exe ../dream_sphere.iso ../dream_sphere.cdi

clean:
	-rm -f $(TARGET) $(OBJS) romdisk.* 1st_read.bin output.bin

rm-elf:
	-rm -f $(TARGET) romdisk.*

1st_read.bin: $(TARGET)
	bash ./ds_1st_read.sh $(TARGET)

$(TARGET): $(OBJS)
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) $(OBJEXTRA) -lparallax -lmp3 -lm $(KOS_LIBS)

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS) romdisk.o romdisk.img
	$(KOS_STRIP) $(TARGET)
