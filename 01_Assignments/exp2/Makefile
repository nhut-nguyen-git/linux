CUR_DIR := .
BIN_DIR := $(CUR_DIR)/Bin
INC_DIR := $(CUR_DIR)/Inc
OBJ_DIR := $(CUR_DIR)/Obj
SRC_DIR := $(CUR_DIR)/Src
LIB_DIR := $(CUR_DIR)/Lib
LIB_DIR_SHARED := $(LIB_DIR)/shared

# Compiler flags
CC := gcc
CFLAGS := -Wall -Wextra -fPIC -I $(INC_DIR)
LDFLAGS := -L$(LIB_DIR_SHARED) -lexp2
SHARED_FLAGS := -shared

# Object files
OBJ_FILES := $(OBJ_DIR)/startup.o $(OBJ_DIR)/func_add.o $(OBJ_DIR)/main.o

# Ensure necessary directories exist
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR) $(LIB_DIR_SHARED))

create_obj_shared: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

create_lib_shared: create_obj_shared
	$(CC) $(SHARED_FLAGS) $(OBJ_DIR)/startup.o $(OBJ_DIR)/func_add.o -o $(LIB_DIR_SHARED)/libexp2.so

all: create_lib_shared
	$(CC) $(OBJ_DIR)/main.o $(LDFLAGS) -o $(BIN_DIR)/shared

clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_DIR_SHARED)/*.so $(BIN_DIR)/shared

.PHONY: all create_obj_shared create_lib_shared clean