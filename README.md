
# Ex7-os
## Authors

- [@Dolev Dublon, ID: 207867342](https://www.github.com/dolev146)
- [@Yakov Khodorkovsky, ID: 207045063 ](https://www.github.com/yakov103)

# Bulding FAT32 virtual file system demo

in this project we need to make a virtual file system replica 
we need to implement the data class.

* myDIR
* mydirent
* myfs.h
* libmyfs.so


```
int mymount(const char *source, const char *target,

const char *filesystemtype, unsigned long

mountflags, const void *data);

int myopen(const char *pathname, int flags);

int myclose(int myfd);

ssize_t myread(int myfd, void *buf, size_t count);

ssize_t mywrite(int myfd, const void *buf, size_t count);

off_t mylseek(int myfd, off_t offset, int whence);

myDIR *myopendir(const char *name);

struct mydirent *myreaddir(myDIR *dirp);

int myclosedir(myDIR *dirp);
```

* myFILE
* libmylibc.so
* mystdio.h



```

myFILE *myfopen(const char *restrict pathname, const char *restrict mode)

int myfclose(myFILE *stream);

size_t myfread(void *restrict ptr, size_t size, size_t nmemb, myFILE *restrict stream);

size_t myfwrite(const void *restrict ptr, size_t size, size_t nmemb, myFILE *restrict stream);

int myfseek(myFILE *stream, long offset, int whence);

int myfscanf(myFILE *restrict stream,

const char *restrict format, ...);

int myfprintf(myFILE *restrict stream,

const char *restrict format, ...);

```

# How it works

we create a file named fs_data , which is going to be the file system.
the size of the file will be determined by the parameter entered.

which contain a superblock
10% inodes
and the other 90% of the size will be the datablocks 512 bytes size each

the max file size is 5120
the main folder is the root folder.
which will contain all the files in the file system.

dirent contains d_name member so that in order to look for files in the filesystem
we open the root folder and iterate over the directory entry and print the files names
file name cant be longer than 8 bytes

to see the change in the filesystem 
```bash
  make; ./test
```

```
less fs_data 
```

## Run Locally

Clone the project

```bash
  git clone https://github.com/yakov103/Ex7-os.git
```

Go to the project directory

```bash
  cd Ex7-os
```

Install dependencies

```bash
  sudo apt install make
  sudo apt install g++ 
```

test the program

```bash
  make; ./test
```


## Running Tests

The first test will test handling multiple clients

first  run the server

```bash
  make clean;  make; ./test
```


