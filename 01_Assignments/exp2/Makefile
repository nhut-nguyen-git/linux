CUR_DIR := .
BIN_DIR := $(CUR_DIR)/Bin
INC_DIR := $(CUR_DIR)/Inc
OBJ_DIR := $(CUR_DIR)/Obj
SRC_DIR := $(CUR_DIR)/Src
LIB_DIR := $(CUR_DIR)/Lib

LIB_DIR_SHARED := $(LIB_DIR)/shared

C_FLAG = -I $(INC_DIR)


create_obj_shared:
	gcc -c -fPIC $(SRC_DIR)/startup.c -o $(OBJ_DIR)/startup.o -I $(INC_DIR)
	gcc -c -fPIC $(SRC_DIR)/func_add.c -o $(OBJ_DIR)/func_add.o -I $(INC_DIR)
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)

create_lib_shared:
	gcc -shared $(OBJ_DIR)/startup.o $(OBJ_DIR)/func_add.o -o $(LIB_DIR_SHARED)/libexp2.so

all: create_obj_shared create_lib_shared
	gcc  $(OBJ_DIR)/main.o -L$(LIB_DIR_SHARED) -lexp2 -o $(BIN_DIR)/shared

clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_DIR_SHARED)/*.so $(BIN_DIR)/shared