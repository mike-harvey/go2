CXX = g++
CC = gcc
CFLAGS = -Wall -c
CXXFLAGS = -Wall -D__STDC_LIMIT_MACROS

#OUTPUTDIR = ./bin/
MKDIR = mkdir -p $(OUTPUTDIR)

CSOURCES = \
	edge.c

CXXSOURCES = \
	main.cpp 

COBJECTS = $(patsubst %.c, %.o, $(CSOURCES))

all: edge

edge: 
#	$(MKDIR)
	$(CC) $(CFLAGS) $(CSOURCES)
	$(CXX) $(COBJECTS) $(CXXSOURCES) -o edge

.PHONY: clean
clean: 
	$(RM) -rf $(OUTPUTDIR)
	$(RM) ./*.gc??
	$(RM) ./*.o
