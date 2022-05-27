CC=g++
FLAGS=-std=c++2a -g -Wall

all:test run

run:
	./test 100

test:test.o fs.o fs.hpp
	$(CC) $(FLAGS) -o test test.o fs.o

test.o: test.cpp fs.hpp
	$(CC) $(FLAGS) -c test.cpp

fs.o: fs.cpp fs.hpp
	$(CC) $(FLAGS) -c fs.cpp

clean:
	rm -f *.o test fs_data a.out

# mkfs:
# 	$(CC) $(flags) -o mkfs mkfs.cpp; ./mkfs

# clean:
# 	rm -f mkfs