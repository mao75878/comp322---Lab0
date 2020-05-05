# Name: Mickey Obispo
# Project: Lab 2: Launch-Tube

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLES=launch tube
SRC1=launch.c
file1=launch
OBJ=launch.o

SRC2=tube.c
file2=tube
OBJ2=tube.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: $(EXECUTABLES)


# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
$(EXECUTABLES): 
	$(CC) $(CFLAGS) -c $(SRC1) -Wall -Wextra
	$(CC) $(CFLAGS) -o $(file1) $(OBJ1)
  
  $(CC) $(CFLAGS) -c $(SRC2) -Wall -Wextra
  $(CC) $(CFLAGS) -o $(file2) $(OBJ2)

# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXECUTABLES) $(OBJ1) *~
  rm -f $(EXECUTABLES) $(OBJ2) *~
