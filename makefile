all:clean test

test:test.o fs.o fs.h
	gcc -g -Wall -o test test.o fs.o

test.o: test.c fs.h
	gcc -g -Wall -c test.c

fs.o: fs.c fs.h
	gcc -g -Wall -c fs.c

clean:
	rm -f *.o test fs_data

# mkfs:
# 	$(CC) $(flags) -o mkfs mkfs.cpp; ./mkfs

# clean:
# 	rm -f mkfs