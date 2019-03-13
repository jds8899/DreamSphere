#
# Basic KallistiOS skeleton / test program
# Copyright (C)2001-2004 Dan Potter
#

# file directories for code and build output. 
# NOTE: only works for flat directories.
# Do not use subdirectories for code folders
OBJDIR = obj
SRCDIR = src
INCLUDEDIR = include
BINDIR = bin
BUILDDIR = build
ROMDISK_FOLDER = romdisk

# name of output CDI and ELF files
CDI_NAME = dream_sphere.cdi
ELF_NAME = dream_sphere.elf

#
# Generated variables for Make, to use proper subdirectories
#

# use gnu make wildcard to find all sources
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# ugly way of converting srcs to object names. In order: 
# trim directory name from srcs with notdir,
# get file base names without .cpp using basename,
# add .o suffix with addsuffix,
# then add build folder prefix to files with addprefix
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(notdir $(SRCS)))))
OBJS += $(OBJDIR)/romdisk.o

# Include and lib parameters
CXXFLAGS += -I$(INCLUDEDIR)
LIBS_USED = -lparallax -lpng -lz -lm $(KOS_LIBS)

# output targets
ELF_TARGET = $(addprefix $(BUILDDIR)/, $(ELF_NAME))
CDI_TARGET = $(addprefix $(BINDIR)/, $(CDI_NAME))

#
# End generated make variables
#

# debug, target to print out a make variable
print-%  : ; @echo $* = $($*)

# The rm-elf step is to remove the target before building, to force the
# re-creation of the rom disk.
all: rm-elf $(CDI_TARGET)

include $(KOS_BASE)/Makefile.rules

# temporarily building to parent folder. will use subdirs later
$(CDI_TARGET): $(ELF_TARGET) $(BUILDDIR)/1st_read.bin
	cp IP.BIN $(BUILDDIR)/IP.BIN
	mkisofs -C 0,11702 -V DreamSphere -G IP.BIN -joliet -rock -l -o $(BINDIR)/dream_sphere.iso $(BUILDDIR)
	cdi4dc/cdi4dc.exe $(BINDIR)/dream_sphere.iso $(BINDIR)/dream_sphere.cdi

clean:
	-rm -f $(BINDIR)/* $(BUILDDIR)/* $(OBJDIR)/*

rm-elf:
	-rm -f $(ELF_TARGET) $(OBJDIR)/romdisk.* $(BUILDDIR)/romdisk.*

$(BUILDDIR)/1st_read.bin: $(ELF_TARGET)
	bash ./ds_1st_read.sh $(ELF_TARGET) $(BUILDDIR)/1st_read.bin

$(ELF_TARGET): $(OBJS)
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(ELF_TARGET) $(KOS_START) \
		$(OBJS) $(OBJEXTRA) $(LIBS_USED)

run: $(ELF_TARGET)
	$(KOS_LOADER) $(ELF_TARGET)

dist:
	rm -f $(OBJS) $(BUILDDIR)/romdisk.img
	$(KOS_STRIP) $(ELF_TARGET)

# custom KOS targets to use subfolders
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	kos-cc $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	kos-c++ $(CFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	kos-c++ $(CFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/romdisk.img:
	$(KOS_GENROMFS) -f $(BUILDDIR)/romdisk.img -d $(ROMDISK_FOLDER) -v -x .svn

$(OBJDIR)/romdisk.o: $(BUILDDIR)/romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o $(BUILDDIR)/romdisk.img romdisk $(OBJDIR)/romdisk.o
