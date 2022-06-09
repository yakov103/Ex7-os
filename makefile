CC=g++
FLAGS=-std=c++2a -g -Wall 
# -Werror -Wextra 
# * libmylibc.so
# * mystdio.h

all:libmyfs.so  test 

libmylibc.so:
	$(CC) $(FLAGS) -g -fPIC -shared -o libmylibc.so myFILE.cpp 

libmyfs.so:
	$(CC) $(FLAGS) -g -fPIC -shared -o libmyfs.so myfs.cpp

run:
	./test 100

test:test.o libmyfs.so libmylibc.so
	$(CC) $(FLAGS) -g -o test test.o ./libmyfs.so ./libmylibc.so

test.o: test.cpp 
	$(CC) $(FLAGS) -g -c test.cpp

myfs.o: myfs.cpp myfs.hpp
	$(CC) $(FLAGS) -g -c myfs.cpp

myFILE.o: myFILE.cpp myFILE.hpp
	$(CC) $(FLAGS) -g -c myFILE.cpp

clean:
	rm -f *.o test fs_data a.out libmyfs.so libmylibc.so

# mkfs:
# 	$(CC) $(flags) -o mkfs mkfs.cpp; ./mkfs

# clean:
# 	rm -f mkfs