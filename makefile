CC     = gcc
# setting some useful flags:
# std=c99 is the standard which you should be using
# -Wall means 'report all warnings' which is useful to help you write better code
# -Werror means 'make all warnings into errors' which means your code doesn't compile with warnings
# this is a good idea when code quality is important
# -g enables the use of GDB
#CFLAGS = -std=c99 -Wall -Werror -g
# libraries needed for linking
LDLIBS = `sdl2-config --cflags --libs`
# this is your list of executables which you want to compile with all
EXE    = pgmEcho pgmComp pgma2b pgmb2a pgmReduce

# we put 'all' as the first command as this will be run if you just enter 'make'
all: ${EXE}

# clean removes all object files - DO NOT UNDER ANY CIRCUMSTANCES ADD .c OR .h FILES
# rm is NOT REVERSIBLE.
clean:
	rm -rf *.o ${EXE}

# this is a rule to define how .o files will be compiled
# it means we do not have to write a rule for each .o file

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ `sdl2-config --cflags --libs` -lm

# for each executable, you need to tell the makefile the 'recipe' for your file
# at the moment, this is very simple as we are only using one .c file
# but as you refactor and add more .c and .h files
# these recipes will become more complex.


pgmEcho: pgmEcho.o img.o
	$(CC) $(CFLAGS) $^ -o $@ `sdl2-config --cflags --libs` -lm
pgmComp: pgmComp.o img.o
	$(CC) $(CFLAGS) $^ -o $@ `sdl2-config --cflags --libs` -lm
pgma2b: pgma2b.o img.o
	$(CC) $(CFLAGS) $^ -o $@ `sdl2-config --cflags --libs` -lm
pgmb2a: pgmb2a.o img.o
	$(CC) $(CFLAGS) $^ -o $@ `sdl2-config --cflags --libs` -lm
pgmReduce: pgmReduce.o img.o
	$(CC) $(CFLAGS) $^ -o $@ `sdl2-config --cflags --libs` -lm
