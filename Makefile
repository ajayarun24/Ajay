#Executable names:
EXE = main
TEST = test

#Add all object files needed for compiling:
EXE_OBJ = main.o 
OBJS = parsing.o roadtripgraph.o calculator.o main.o


#Use the cs225 makefile template:
include cs225/make/cs225.mk

ccred=$(shell echo -e "\033[0;31m")
 ccyellow=$(shell echo -e "\033[0;33m")
 ccend=$(shell echo -e "\033[0m")

 IS_EWS=$(shell hostname | grep "ews.illinois.edu")
 IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
 ifneq ($(strip $(IS_EWS)),)
 ifeq ($(strip $(IS_CORRECT_CLANG)),)
 CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1'. $(ccend))
 endif
 else
 CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
 endif

 output_msg: ; $(CLANG_VERSION_MSG)
 .PHONY: output_msg