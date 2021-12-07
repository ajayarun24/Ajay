EXENAME = main
OBJS = main.o roadtripgraph.o parsing.o calculator.o testing.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

include cs225/make/cs225.mk

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

#object file dependncies
main.o : main.cpp roadtripgraph.cpp roadtripgraph.h parsing.h parsing.cpp calculator.h calculator.cpp testing.h testing.cpp bfs.o
	$(CXX) $(CXXFLAGS) main.cpp

roadtripgraph.o : roadtripgraph.cpp roadtripgraph.h 
	$(CXX) $(CXXFLAGS) roadtripgraph.cpp

parsing.o : parsing.h parsing.cpp  
	$(CXX) $(CXXFLAGS) parsing.cpp

calculator.o : calculator.h calculator.cpp
	$(CXX) $(CXXFLAGS) calculator.cpp

testing.o : parsing.h parsing.cpp testing.h testing.cpp 
	$(CXX) $(CXXFLAGS) testing.cpp

bfs.o : bfs.h bfs.cpp
	$(CXX) $(CXXFLAGS) bfs.cpp

# Custom Clang version enforcement Makefile rule:
# for using 'make test'
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

test: output_msg ../catch/catchmain.cpp ../tests/graph-tests.cpp graph.cpp vertex.cpp utility.cpp
	$(LD) ../catch/catchmain.cpp ../tests/graph-tests.cpp graph.cpp vertex.cpp utility.cpp $(LDFLAGS) -o test

.PHONY: output_msg