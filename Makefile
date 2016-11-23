CC		=gcc
CFLAGS	=-Wall -pedantic -std=c99 -g
OBJECTS	=q1.o q2.o arrayHeap.o fHeap.o tree.o verify.o driver.o
EXEC 	=q1
COMP	=build
FILES	=./src/q1.c ./src/q2.c ./src/arrayHeap.c ./src/fHeap.c ./src/tree.c ./src/verify.c
INCLUDE	=./include


#
# This specifies which rules take no parameters.
#
.PHONY: all clean


all: $(COMP)


#
# This is the normal compilation rule.  Simply typing 'make' will run this
#
$(COMP): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS)

#
# Object rules:
#

q1.o: ./src/q1.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/q1.c -I$(INCLUDE)

q2.o: ./src/q2.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/q2.c -I$(INCLUDE)

arrayHeap.o: ./src/arrayHeap.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/arrayHeap.c -I$(INCLUDE)

fHeap.o: ./src/fHeap.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/fHeap.c -I$(INCLUDE)

tree.o: ./src/tree.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/tree.c -I$(INCLUDE)

verify.o: ./src/verify.c $(wildcard include*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/verify.c -I$(INCLUDE)

driver.o: ./src/driver.c $(wildcard include*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/driver.c -I$(INCLUDE)




#
# Clean-up rules.  Removes the executable and objects.
#

clean:
	rm $(EXEC1) $(EXEC2) $(OBJECTS)
