CC=g++
flags=-Wall -Wextra -Werror -std=c++2a

all:mkfs main

main:main.cpp
	$(CC) $(flags) main.cpp -o main

mkfs:
	$(CC) $(flags) -o mkfs mkfs.cpp; ./mkfs

clean:
	rm -f mkfs