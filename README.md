
# Ex7-os will compile only on ubuntu 20.04!! due to use of doctest.h for testing
## Authors

- [@Dolev Dublon, ID: 207867342](https://www.github.com/dolev146)
- [@Yakov Khodorkovsky, ID: 207045063 ](https://www.github.com/yakov103)

# How it works && how to run

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
  make; ./demo
```
```
less fs_data 
```
```
  make ./test
```
![image](https://user-images.githubusercontent.com/62290677/173178073-17cd760d-3941-4bb4-9a2f-84fda4c03b4d.png)
![image](https://user-images.githubusercontent.com/62290677/173178119-0049493c-b94b-4ae8-a938-2f8815ba9ec3.png)
![image](https://user-images.githubusercontent.com/62290677/173178151-8d96c7af-d74f-4083-9f20-20154ada7554.png)

you can also specify an amount of files (inodes) you want in the system as a aparameter

```
  make clean; make; ./demo 20 
```
20 will be the amount of inodes you will get.

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

![image](https://user-images.githubusercontent.com/62290677/173178077-5f0c1144-da39-4724-9441-63f26a8f3961.png)
![image](https://user-images.githubusercontent.com/62290677/173178116-bc391684-0ede-4d86-bf2f-1d869a0b634c.png)
![image](https://user-images.githubusercontent.com/62290677/173178155-ef9e2d1f-ca49-4698-9ff5-fb56a3aae89c.png)



