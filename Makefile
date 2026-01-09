CC := gcc
SRCDIR := src
TESTSDIR := tests/unity
ITESTSDIR := tests/integration
ITESTS_COMPOSE := $(ITESTSDIR)/docker-compose.yaml
LTESTSDIR := tests/load
INCDIR := include
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
DEPDIR := $(BUILDDIR)/dep
TESTSBUILDDIR := $(TESTSDIR)/$(BUILDDIR)
TESTSINCDIR := $(TESTSDIR)/$(INCDIR)

ITESTSBUILDDIR := $(ITESTSDIR)/$(BUILDDIR)
ITESTSINCDIR := $(ITESTSDIR)/$(INCDIR)

SRC = $(shell find $(SRCDIR) -name "*.c")

TESTSSRC = $(filter-out $(SRCDIR)/main.c,$(SRC))
TESTSSRC += $(shell find $(TESTSDIR) -name "*.c")
TESTSSRC += $(shell find tests/unity_framework -name "*.c")

ITESTSSRC = $(filter-out $(SRCDIR)/main.c,$(SRC))
ITESTSSRC += $(shell find $(ITESTSDIR) -name "*.c")
ITESTSSRC += $(shell find tests/unity_framework -name "*.c")

INCLUDE = $(shell find $(INCDIR) -type d)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
DEP = $(patsubst $(SRCDIR)/%.c,$(DEPDIR)/%.d,$(SRC))

TESTSINCLUDE = $(shell find $(TESTSINCDIR) -type d)
ITESTSINCLUDE = $(shell find $(ITESTSINCDIR) -type d)

PKG_LIBS = libulfius jansson liborcania libpq

CFLAGS  = -Wall -Wextra -pthread $(addprefix -I,$(INCLUDE)) $(shell pkg-config --cflags $(PKG_LIBS)) -MMD -MP -MF
LDLIBS  = -pthread $(shell pkg-config --libs $(PKG_LIBS))

TFLAGS = -Wall -Wextra -pthread $(addprefix -I,$(INCLUDE)) -Itests/unity_framework $(addprefix -I,$(TESTSINCLUDE)) $(shell pkg-config --cflags --libs $(PKG_LIBS))

ITFLAGS = -Wall -Wextra -pthread $(addprefix -I,$(INCLUDE)) -Itests/unity_framework $(addprefix -I,$(ITESTSINCLUDE)) $(shell pkg-config --cflags --libs $(PKG_LIBS))

TARGET = lab_api
TESTTARGET = $(addprefix tests_,$(TARGET))
ITESTTARGET = $(addprefix itests_,$(TARGET))

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

tests: build_tests run_tests

itests: db_up build_itests run_itests db_down

ltests:
	@k6 run $(LTESTSDIR)/load_test.js

build_tests:
	@mkdir -p $(TESTSBUILDDIR)
	$(CC) $(TFLAGS) $(TESTSSRC) -o $(TESTSBUILDDIR)/$(TESTTARGET)

build_itests:
	@mkdir -p $(ITESTSBUILDDIR)
	$(CC) $(ITFLAGS) $(ITESTSSRC) -o $(ITESTSBUILDDIR)/$(ITESTTARGET)

db_up:
	@docker compose -f $(ITESTS_COMPOSE) up -d

db_down:
	@docker compose -f $(ITESTS_COMPOSE) down -v

clean:
	rm -rf $(BUILDDIR)

run: $(BUILDDIR)/$(TARGET)
	./$<

clean_tests:
	rm -rf $(TESTSBUILDDIR)

run_tests: $(TESTSBUILDDIR)/$(TESTTARGET)
	./$<

clean_itests:
	rm -rf $(ITESTSBUILDDIR)

run_itests: $(ITESTSBUILDDIR)/$(ITESTTARGET)
	./$<

.PHONY: all run clean tests build_tests run_tests clean_tests itests db_up build_itests run_itests db_down clean_itests ltests
