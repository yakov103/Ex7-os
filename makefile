CC=g++
FLAGS=-std=c++2a -g -Wall 
# -Werror -Wextra 
# * libmylibc.so
# * mystdio.h

all:libmyfs.so  demo test

libmylibc.so:
	$(CC) $(FLAGS) -g -fPIC -shared -o libmylibc.so myFILE.cpp 

libmyfs.so:
	$(CC) $(FLAGS) -g -fPIC -shared -o libmyfs.so myfs.cpp

run:
	./test 100

demo:demo.o libmyfs.so libmylibc.so
	$(CC) $(FLAGS) -g -o demo demo.o ./libmyfs.so ./libmylibc.so

demo.o: demo.cpp 
	$(CC) $(FLAGS) -g -c demo.cpp

myfs.o: myfs.cpp myfs.hpp
	$(CC) $(FLAGS) -g -c myfs.cpp

myFILE.o: myFILE.cpp myFILE.hpp
	$(CC) $(FLAGS) -g -c myFILE.cpp

test:TestCounter.o Test.o
	g++ -g -o test TestCounter.o Test.o ./libmyfs.so ./libmylibc.so

TestCounter.o:
	$(CC) $(FLAGS) -g -c TestCounter.cpp

Test.o:
	$(CC) $(FLAGS) -g -c Test.cpp

clean:
	rm -f *.o test fs_data a.out libmyfs.so libmylibc.so demo

# mkfs:
# 	$(CC) $(flags) -o mkfs mkfs.cpp; ./mkfs

# clean:
# 	rm -f mkfs