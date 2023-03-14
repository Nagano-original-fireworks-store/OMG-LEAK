#===========================================================
# template makefile for gaps_server xxxgame.so
# tps_so_template
#===========================================================

###�����־###

C_FLAGS          = -Wall -D_GNU_SOURCE  -Wno-deprecated -fPIC -g -pipe -D_DEBUG -Woverloaded-virtual -Wpointer-arith -fno-strict-aliasing -std=c++0x
CXX_FLAGS        = -Wall -D_GNU_SOURCE  -Wno-deprecated -fPIC -g -pipe -D_DEBUG -Woverloaded-virtual -Wpointer-arith -D__cplusplus -fno-s -std=c++0x

TARGET = ../bin/Game.so
TARGET_HEAD = ../bin/gamehead.so
OBJ_DIR = ./obj/
AR = ar



DIRS := $(shell find . -type d ! -path "./obj*" ! -path "./protocol*" ! -path "."| awk '{print substr($$0,3,100)}')
mkdirs = $(foreach dir,$(DIRS),$(shell mkdir $(OBJ_DIR)$(dir)))

$(mkdirs)



FILES := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cc))
FILES := $(wildcard $(FILES))
#$(warning $(FILES))


SOURCE=$(wildcard *.cpp)
SOURCE+=$(wildcard *.c)
SOURCE+=$(wildcard *.cc *.cc)
SOURCE+=$(FILES)

SRC=$(SOURCE)

SRCOBJ=$(patsubst %.cc,%.o,$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRC))))
OBJS=$(addprefix $(OBJ_DIR), $(SRCOBJ))
INC_GAPSCOMM = -I../include -I./Protocol
LIB_GAPSCOMM = ../lib/libgapscomm.a
LIB_GAPSCOMM_HEAD = ../lib/libpkgheader.a

#此处配置项目依赖库查找路径，如-L/usr/local/protobuf34/lib
LIB_PATH = -L../lib/ -L/home/yanling.wu/protobuf34/lib -L.
#此处增加项目依赖头文件路径，如-I/usr/local/protobuf34/protobuf
INC = -I./ $(INC_GAPSCOMM) -I../tsf4g/include -I/home/yanling.wu/protobuf34/include
#此处在后面增加项目依赖库，如-lprotobuf
LIB = $(LIB_GAPSCOMM) $(LIB_PATH) -lgamecomm -lcomm -lscew -lexpat -lprotobuf

all:$(OBJS)
.PHONY:clean

$(OBJ_DIR)%.o: %.cpp
	@$(CXX) $(INC) $(C_FLAGS) -c $< -o $@ 
	@echo compile   $@ 
$(OBJ_DIR)%.o: %.c
	@$(CC)$(INC) $(C_FLAGS) -c $< -o $@ 
	@echo compile   $@	
$(OBJ_DIR)%.o: %.cc 
	@$(CC) $(INC) $(C_FLAGS) -c $< -o $@ 
	@echo compile   $@	
$(TARGET): $(OBJS)
	@$(AR) x $(LIB_GAPSCOMM)
	@echo $(CXX) $(C_FLAGS) -shared *.o  $^ -o $@ $(LIB) 
	@$(CXX) $(C_FLAGS) -shared *.o  $^ -o $@ $(LIB) 
	@rm *.o
	@echo -e "Create $@"
$(TARGET_HEAD): PkgHead.h PkgHead.cpp
	@$(AR) x $(LIB_GAPSCOMM_HEAD) 
	mv *.o $(OBJ_DIR)
	g++ -Wall -D_GNU_SOURCE -Wno-deprecated -fPIC -g -pipe -D_DEBUG -Woverloaded-virtual -Wpointer-arith -fno-strict-aliasing $(LIB) -shared ./obj/headersoexporter.o ./obj/PkgHead.o ./obj/ProtocolHead.o -o ../bin/gamehead.so ../lib/libpkgheader.a 



all:$(TARGET)
head: $(TARGET_HEAD)
clean:
	@rm -f $(TARGET)  $(OBJS)
	@rm -f ../bin/gamehead.so
	@echo rm $(OBJS)  $(TARGET)
	#@echo rm -rf $(OBJ_DIR)/*
