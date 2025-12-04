CC = gcc
SRCDIR = src
BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
DEPDIR = $(BUILDDIR)/dep

SRC = $(shell find src -name "*.c")
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
DEP = $(patsubst $(SRCDIR)/%.c,$(DEPDIR)/%.d,$(SRC))

PKG_LIBS = libulfius jansson liborcania libpq

CFLAGS  += -Wall -Wextra $(shell pkg-config --cflags $(PKG_LIBS))
LDLIBS  += $(shell pkg-config --libs $(PKG_LIBS))

TARGET = my_api

all: $(BUILDDIR) $(OBJDIR) $(DEPDIR) $(TARGET)
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DEPDIR):
	mkdir -p $(DEPDIR)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(BUILDDIR)/$@ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -MF $(DEPDIR)/$*.d -c $< -o $@

-include $(DEP)

clean:
	rm -rf $(BUILDDIR)

run: $(BUILDDIR)/$(TARGET)
	./$(BUILDDIR)/$(TARGET)

.PHONY: all run clean
