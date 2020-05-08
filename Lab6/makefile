# Name: Mickey Obispo
# Project: Lab 6 Wack a Mole!

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLES=spiritd mole
SRC1=spiritd.c
OBJ1=spiritd.o

SRC2=mole.c
OBJ2=mole.o
# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g -Wall -Wextra

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: $(EXECUTABLE1) $(EXECUTABLE2)


# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
$(EXECUTABLE1): $(SRC1)
	$(CC) $(CFLAGS) -c $(SRC1)
	$(CC) $(CFLAGS) -o $@ $(OBJ1)
  
$(EXECUTABLE2): $(SRC2)
  $(CC) $(CFLAGS) -c $(SRC2)
  $(CC) $(CFLAGS) -o $@ $(OBJ2)

# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXECUTABLE1) $(EXECUTABLE2) $(OBJ1) $(OBJ2) *~
