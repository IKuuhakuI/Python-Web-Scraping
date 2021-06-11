#
# Universidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Eletronica e Computacao
# EEL670 - Linguagens de Programacao - Turma 2020/2
# Prof. Miguel Elias M. Campista
# Autor: Luiz Carlos Aguiar Carrion & Maria Eduarda de Souza Mafra
# Trabalho Final - Etapa 2
# Decricao: Makefile
#
 
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
WEBSCRAPINGOBJS = main.o scraping.o algorithms.o menu.o store.o
		    
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
