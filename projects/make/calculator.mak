# Determine build type based on CFLAGS #
ifeq ($(findstring -g,$(CFLAGS)),-g)
    BUILD_DIR = bin/debug
else
    BUILD_DIR = bin/release
endif

.DEFAULT_GOAL := $(BUILD_DIR)/calculator_test.out

INC_DIRS = -I$(CALC_INC_DIR) -I$(DS_INC_DIR)

# APIs to turn into .so files #
LIB_NAMES = stack 
CALC_NAMES = calculator

# Source directories #
DS_INC_DIR = ../ds/inc
DS_SRC_DIR = ../ds/src
CALC_SRC_DIR = calculator/src
CALC_INC_DIR = calculator/inc
TEST_DIR = calculator/test

# .so file names #
DS_SO_FILES = $(addprefix $(DS_SRC_DIR)/lib, $(addsuffix .so, $(LIB_NAMES)))
CALC_SO_FILE = $(addprefix $(CALC_SRC_DIR)/lib, $(addsuffix .so,$(CALC_NAMES)))

TARGET = $(BUILD_DIR)/calculator_test.out
OBJS = $(TEST_DIR)/calculator_test.o

# Create build directory #
$(BUILD_DIR):
	mkdir -p $@

# Build Shared librarys files in ../ds/src/ #
$(DS_SRC_DIR)/lib%.so: $(DS_SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_DIRS) -shared -o $@ $<

# Build Shared librarys in sched/src/ #
$(CALC_SRC_DIR)/lib%.so: $(CALC_SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_DIRS) -shared -o $@ $<

# Build Test object file #
$(TEST_DIR)/calculator_test.o: $(TEST_DIR)/calculator_test.c
	$(CC) $(CFLAGS) $(INC_DIRS) -c -o $@ $<

# build directory before linking (order-only prerequisite) #
$(TARGET): | $(BUILD_DIR)

# Test executable linked with shared library #
$(TARGET): $(OBJS) $(DS_SO_FILES) $(CALC_SO_FILE)
	$(CC) -o $@ $^ -L$(DS_SRC_DIR) -L$(CALC_SRC_DIR) $(addprefix -l, $(LIB_NAMES)) $(addprefix -l, $(CALC_NAMES)) -Wl,-rpath,$(abspath $(DS_SRC_DIR)):$(abspath $(CALC_SRC_DIR)) -lm

-include $(DS_SO_FILES:.so=.d) $(CALC_SO_FILE:.so=.d) $(OBJS:.o=.d)






