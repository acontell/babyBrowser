CC    ?= clang
CXX   ?= clang++

EXE = dp_browser

CDEBUG = -g -Wall

CXXDEBUG = -g -Wall

CSTD = -std=c99
CXXSTD = -std=c++14

CFLAGS = -Wno-deprecated-register -O0  $(CDEBUG) $(CSTD) 
CXXFLAGS = -Wno-deprecated-register -O0  $(CXXDEBUG) $(CXXSTD)

SUBDIRS = Parser

CPPOBJ = main

FILES = $(addsuffix .cpp, $(CPPOBJ))

OBJS  = $(addsuffix .o, $(CPPOBJ))

CLEANLIST =  $(OBJS) $(EXE)\

.PHONY: all
all: wc

wc: $(FILES)
	$(MAKE) -C Parser
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) $(SUBDIRS)/*.o $(LIBS)

.PHONY: test
test:
	test/test0.pl

.PHONY: clean
clean:
	$(MAKE) -C Parser clean
	rm -rf $(CLEANLIST)

