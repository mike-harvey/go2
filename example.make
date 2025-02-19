CXX = g++
CC = gcc
CFLAGS = -Wall -c
CXXFLAGS = -Wall -D__STDC_LIMIT_MACROS

OUTPUTDIR = ./bin/
MKDIR = mkdir -p $(OUTPUTDIR)
OBJECTC = redis.o

CSOURCES = \
     $(HIREDIS_FOLDER)/net.c \
     $(HIREDIS_FOLDER)/hiredis.c \
     $(HIREDIS_FOLDER)/sds.c \
     $(HIREDIS_FOLDER)/async.c

CXXSOURCES = \
    main.cpp 

all: server

server: 
    $(MKDIR)
    $(CC) $(CSOURCES) $(CFLAGS) -o $(OUTPUTDIR)$(OBJECTC)
    $(CXX) $(OUTPUTDIR)$(OBJECTC) $(CXXSOURCES) -o $(OUTPUTDIR)server

.PHONY: clean
clean:
    $(RM) -rf $(OUTPUTDIR)
    $(RM) ./*.gc??
    $(RM) ./*.o
