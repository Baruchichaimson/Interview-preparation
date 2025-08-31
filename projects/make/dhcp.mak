#========================
# Makefile – DHCP Test
#========================

# Determine build type based on CFLAGS
ifeq ($(findstring -g,$(CFLAGS)),-g)
    BUILD_DIR = bin/debug
else
    BUILD_DIR = bin/release
endif

.DEFAULT_GOAL := $(BUILD_DIR)/dhcp_test.out

# Directories
DHCP_SRC_DIR = dhcp/src
DHCP_INC_DIR = dhcp/inc
TEST_DIR     = dhcp/test

# Compiler flags
INC_DIRS = -I$(DHCP_INC_DIR)

# Source files
DHCP_SRCS = $(DHCP_SRC_DIR)/trie.c $(DHCP_SRC_DIR)/dhcp.c
DHCP_OBJS = $(DHCP_SRCS:.c=.o)
TEST_OBJS = $(TEST_DIR)/dhcp_test.o

TARGET = $(BUILD_DIR)/dhcp_test.out

#========================
# Rules
#========================

# Create build directory
$(BUILD_DIR):
	mkdir -p $@

# Compile DHCP source files
$(DHCP_SRC_DIR)/%.o: $(DHCP_SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_DIRS) -c -o $@ $<

# Compile test file
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_DIRS) -c -o $@ $<

# Link executable
$(TARGET): $(TEST_OBJS) $(DHCP_OBJS) | $(BUILD_DIR)
	$(CC) -o $@ $^

# Optional: include dependency files if needed
-include $(DHCP_OBJS:.o=.d) $(TEST_OBJS:.o=.d)
