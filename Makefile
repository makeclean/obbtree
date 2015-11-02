# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -std=c++11
OMPFLAGS = -fopenmp

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#

all: obbtree obbtree_omp

obbtree: main.cpp obbbox.o obbbox_creator.o obbtree_navigator.o 
	$(CC) $(CFLAGS) -o obbtree main.cpp obbbox.o obbbox_creator.o obbtree_navigator.o

obbtree_omp: main.cpp obbbox.o obbbox_creator.o obbtree_navigator.o 
	$(CC) $(CFLAGS) $(OMPFLAGS) -o obbtree_omp main.cpp obbbox.o obbbox_creator.o obbtree_navigator.o

obbbox_creator.o: obbbox_creator.cpp obbbox.hpp obbbox_creator.hpp
	$(CC) $(CFLAGS) -c obbbox_creator.cpp

obbtree_navigator.o: obbtree_navigator.cpp obbbox.hpp obbtree_navigator.hpp
	$(CC) $(CFLAGS) -c obbtree_navigator.cpp

obbbox.o: obbbox.cpp obbbox.hpp
	$(CC) $(CFLAGS) -c obbbox.cpp

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) obbtree obbtree_navigator *.o *~
