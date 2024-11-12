CC = g++
CFLAGS = -Wall -g

MAKEFILES = $(shell find . -maxdepth 2 -type f -name Makefile)
SUBDIRS   = $(filter-out ./,$(dir $(MAKEFILES)))

default: all

all: 
	for dir in $(SUBDIRS); do \
		make -C $$dir all; \
	done
	$(OBJECTFILES = $(shell find . -maxdepth 2 -type f -name *.o))
	for path in $(OBJECTFILES); do \
		mv $$path ./; \
	done
	g++ -o test test.cpp *.o

clean:
	rm -f *.o