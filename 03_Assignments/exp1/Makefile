CUR_DIR := .
BIN_DIR := $(CUR_DIR)/Bin
INC_DIR := $(CUR_DIR)/Inc
OBJ_DIR := $(CUR_DIR)/Obj
SRC_DIR := $(CUR_DIR)/Src
LIB_DIR := $(CUR_DIR)/Lib
LIB_DIR_STATIC := $(LIB_DIR)/static

# Compiler and Archiver
CC := gcc
AR := ar
CFLAGS := -Wall -Wextra -I $(INC_DIR)

# Object files
OBJ_FILES := $(OBJ_DIR)/func_sub.o $(OBJ_DIR)/func_add.o $(OBJ_DIR)/main.o

# Ensure directories exist
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR) $(LIB_DIR_STATIC))

create_obj_static: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

create_lib_static: create_obj_static
	$(AR) rcs $(LIB_DIR_STATIC)/libexp1.a $(OBJ_DIR)/func_sub.o $(OBJ_DIR)/func_add.o

all: create_lib_static
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_DIR_STATIC) -lexp1 -o $(BIN_DIR)/static

clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_DIR_STATIC)/*.a $(BIN_DIR)/static

.PHONY: all create_obj_static create_lib_static clean