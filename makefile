CC=g++
flags=-Wall -Wextra -Werror -std=c++11

all:mkfs

mkfs:
	$(CC) $(flags) -o mkfs mkfs.cpp; ./mkfs
clean:
	rm -f mkfs