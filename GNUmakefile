OS = $(shell uname -s) # Sistema Operacional

CC = g++

LD = $(CC)

# CFLAGS / LFLAGS ########################
CFLAGS = -Wall

ifeq ($(debug), _MY_DEBUG_)
CFLAGS = -Wall -D_MY_DEBUG_
endif

LFLAGS = -Wall
##########################################

# LAB 01 #################################
WEBSCRAPINGOBJS = mainTest.o scraping.o algorithms.o
		    
WEBSCRAPING = webScraping
##########################################

EXECS = $(WEBSCRAPING)

ALL = $(EXECS)
all: $(ALL)

# Regra implicita ########################
.cpp.o:
	$(CC) $(CFLAGS) -c -I/usr/include/python3.8/ $< 
##########################################

# TRAB 01 ################################
webScraping: $(WEBSCRAPINGOBJS)
	$(LD) $(LFLAGS) -o $@ $(WEBSCRAPINGOBJS) -L/usr/lib/python3.8/config-3.8m-x86_64-linux-gnu -lpython3.8
##########################################

# Clean ##################################
clean:
	rm -f *.o $(ALL)

clean-objs:
	rm -f *.o
