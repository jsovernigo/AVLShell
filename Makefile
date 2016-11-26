CC		=gcc
CFLAGS	=-Wall -pedantic -std=c99 -g
OBJECTS	=driver.o avltree.o treeLib.o strRecord.o
EXEC 	=avltree
COMP	=build
FILES	=./src/driver.c ./src/avltree.c ./src/treeLib.c ./src/strRecord.c
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

driver.o: ./src/driver.c $(wildcard include*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/driver.c -I$(INCLUDE)

avltree.o: ./src/avltree.c $(wildcard include*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/avltree.c -I$(INCLUDE)

treeLib.o: ./src/treeLib.c $(wildcard include*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/treeLib.c -I$(INCLUDE)

strRecord.o: ./src/strRecord.c $(wildcard include*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/strRecord.c -I$(INCLUDE)
#
# Clean-up rules.  Removes the executable and objects.
#

clean:
	rm $(EXEC) $(OBJECTS)
