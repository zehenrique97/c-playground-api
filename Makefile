CC := gcc
SRCDIR := src
INCDIR := include
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
DEPDIR := $(BUILDDIR)/dep

SRC = $(shell find src -name "*.c")
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
DEP = $(patsubst $(SRCDIR)/%.c,$(DEPDIR)/%.d,$(SRC))

PKG_LIBS = libulfius jansson liborcania libpq

CFLAGS  = -Wall -Wextra -I$(INCDIR) $(shell pkg-config --cflags $(PKG_LIBS)) -MMD -MP -MF
LDLIBS  = $(shell pkg-config --libs $(PKG_LIBS))

TARGET = playground_api

all: create_build_dirs $(BUILDDIR)/$(TARGET)

create_build_dirs:
	mkdir -p $(BUILDDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(DEPDIR)

$(BUILDDIR)/$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.d)
	$(CC) $(CFLAGS) $(DEPDIR)/$*.d -c $< -o $@

-include $(DEP)

clean:
	rm -rf $(BUILDDIR)

run: $(BUILDDIR)/$(TARGET)
	./$<

.PHONY: all run clean
