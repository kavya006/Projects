# *****************************************************************************************
# Project:              Networks
# Subtree:              /home1/hema/Networks/src
# Filename:             Makefile for Networks
# Programmer:           Hema A Murthy
# Host System:          Linux
# Date Created:         08/March/2008
# Project:              Client and  Server
# *****************************************************************************************

SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin
INCDIR = ./src/include/
CFLAGS = -g -c -Wall -O -I$(INCDIR)
CC = gcc
CC1 = g++ -std=c++11

all :	$(BINDIR)/Server $(BINDIR)/Client 

$(BINDIR)/Server : $(OBJDIR)/Server.o \
	$(OBJDIR)/DgEcho.o 
	$(CC1) -g -o$(BINDIR)/Server \
	$(OBJDIR)/Server.o \
	$(OBJDIR)/DgEcho.o \
	-I$(INCDIR)	

$(BINDIR)/Client : $(OBJDIR)/Client.o \
	$(OBJDIR)/DgClient.o 
	$(CC) -g -o$(BINDIR)/Client  \
	$(OBJDIR)/Client.o \
	$(OBJDIR)/DgClient.o \
	-I$(INCDIR)

$(OBJDIR)/Server.o : $(SRCDIR)/Server.c
	$(CC1) $(CFLAGS) -o $(OBJDIR)/Server.o $(SRCDIR)/Server.c 

$(OBJDIR)/DgEcho.o : $(SRCDIR)/DgEcho.c 
	$(CC1) $(CFLAGS) -o $(OBJDIR)/DgEcho.o $(SRCDIR)/DgEcho.c 

$(OBJDIR)/Client.o : $(SRCDIR)/Client.c 
	$(CC) $(CFLAGS) -o $(OBJDIR)/Client.o $(SRCDIR)/Client.c 

$(OBJDIR)/DgClient.o : $(SRCDIR)/DgClient.c 
	$(CC) $(CFLAGS) -o $(OBJDIR)/DgClient.o $(SRCDIR)/DgClient.c 
clean: 
	rm -fr $(BINDIR)/Server $(BINDIR)/Client $(OBJDIR)/Server.o \
	$(OBJDIR)/DgEcho.o $(OBJDIR)Client.o $(OBJDIR)/DgClient.o 



