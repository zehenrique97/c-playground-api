CC := gcc
SRCDIR := src
TESTSDIR := tests
INCDIR := include
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
DEPDIR := $(BUILDDIR)/dep
TESTSBUILDDIR := $(TESTSDIR)/$(BUILDDIR)
TESTSINCDIR := $(TESTSDIR)/$(INCDIR)

SRC = $(shell find $(SRCDIR) -name "*.c")

TESTSSRC = $(filter-out $(SRCDIR)/main.c,$(SRC))
TESTSSRC += $(shell find $(TESTSDIR) -name "*.c")

INCLUDE = $(shell find $(INCDIR) -type d)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
DEP = $(patsubst $(SRCDIR)/%.c,$(DEPDIR)/%.d,$(SRC))

TESTSINCLUDE = $(shell find $(TESTSINCDIR) -type d)

PKG_LIBS = libulfius jansson liborcania libpq

CFLAGS  = -Wall -Wextra $(addprefix -I,$(INCLUDE)) $(shell pkg-config --cflags $(PKG_LIBS)) -MMD -MP -MF
LDLIBS  = $(shell pkg-config --libs $(PKG_LIBS))

TFLAGS = -Wall -Wextra $(addprefix -I,$(INCLUDE)) -Itests/unity $(addprefix -I,$(TESTSINCLUDE)) $(shell pkg-config --cflags --libs $(PKG_LIBS))

TARGET = lab_api
TESTTARGET = $(addprefix tests_,$(TARGET))

all: create_build_dirs $(BUILDDIR)/$(TARGET)

create_build_dirs:
	mkdir -p $(BUILDDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(DEPDIR)

$(BUILDDIR)/$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.d)
	$(CC) $(CFLAGS) $(DEPDIR)/$*.d -c $< -o $@

-include $(DEP)

tests:
	@mkdir -p $(TESTSBUILDDIR)
	$(CC) $(TFLAGS) $(TESTSSRC) -o $(TESTSBUILDDIR)/$(TESTTARGET)

clean:
	rm -rf $(BUILDDIR)

run: $(BUILDDIR)/$(TARGET)
	./$<

clean_tests:
	rm -rf $(TESTSBUILDDIR)

run_tests: $(TESTSBUILDDIR)/$(TESTTARGET)
	./$<

.PHONY: all run clean tests run_tests clean_tests
