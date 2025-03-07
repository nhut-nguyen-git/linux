CUR_DIR := .
BIN_DIR := $(CUR_DIR)/Bin
INC_DIR := $(CUR_DIR)/Inc
OBJ_DIR := $(CUR_DIR)/Obj
SRC_DIR := $(CUR_DIR)/Src
LIB_DIR := $(CUR_DIR)/Lib
LIB_DIR_STATIC := $(LIB_DIR)/static


C_FLAG = -I $(INC_DIR)


create_obj_static: 
	gcc -c $(SRC_DIR)/startup.c -o $(OBJ_DIR)/startup.o -I $(INC_DIR)
	gcc -c $(SRC_DIR)/func_add.c -o $(OBJ_DIR)/func_add.o -I $(INC_DIR)
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)


create_lib_static:
	ar rcs $(LIB_DIR_STATIC)/libexp1.a $(OBJ_DIR)/startup.o $(OBJ_DIR)/func_add.o



all: create_obj_static create_lib_static
	gcc   $(OBJ_DIR)/main.o  -L$(LIB_DIR_STATIC) -lexp1 -o $(BIN_DIR)/static


clean:
	rm -rf $(OBJ_DIR)/*.o  $(LIB_DIR_STATIC)/*.a $(BIN_DIR)/static