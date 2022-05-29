CC=g++
FLAGS=-std=c++2a -g -Wall 
# -Werror -Wextra 

all:test 

run:
	./test 100

test:test.o fs.o fs.hpp myFILE.o myFILE.hpp
	$(CC) $(FLAGS) -o test test.o fs.o myFILE.o 

test.o: test.cpp fs.hpp
	$(CC) $(FLAGS) -c test.cpp

fs.o: fs.cpp fs.hpp
	$(CC) $(FLAGS) -c fs.cpp

myFILE.o: myFILE.cpp myFILE.hpp
	$(CC) $(FLAGS) -c myFILE.cpp

clean:
	rm -f *.o test fs_data a.out

# mkfs:
# 	$(CC) $(flags) -o mkfs mkfs.cpp; ./mkfs

# clean:
# 	rm -f mkfs