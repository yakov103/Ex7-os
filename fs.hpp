#pragma once
// meta information about the filesystem
// number of inodes
// numver of disk blocks
// size of the disk blocks

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string.h>

#define BLOCKSIZE 512
#define MAXFILESYSTEMSIZE 51600
#define MAX_FILES 10000
extern struct inode myopenfile[MAX_FILES];

enum FileType
{
    FILE_TYPE_REGULAR,
    FILE_TYPE_DIRECTORY,
    FILE_TYPE_UNSET
};

enum Permission
{
    PERMISSION_READ,
    PERMISSION_WRITE,
    PERMISSION_EXECUTE,
    PERMISSION_UNSET
};

struct superblock
{
    int num_inodes;
    int num_blocks;
    int size_blocks;
};

struct inode
{
    enum FileType type = FILE_TYPE_UNSET;
    enum Permission permission = PERMISSION_UNSET;
    int used_size = 0;
    int size;
    int first_block;
    char name[8];
};

class myDIR
{
public:
    int inode_num;
    struct inode inode;
    std::vector<std::string> files_names;
    std::vector<std::string> open_files = {};
    myDIR() = default;
    myDIR(struct inode inode, struct superblock *sb, struct inode *inodes)
    {
        this->inode_num = ;
        this->inode = inode;
        this->inode.type = FILE_TYPE_DIRECTORY;
        strcpy(this->inode.name, "root");
        // TODO decide if this is the right way to do this
        // this->inode.permission = PERMISSION_READ;
        this->inode.used_size = 0;
        this->inode.size = 0;
        this->inode.first_block = -1;

        for (int i = 0; i < sb.num_inodes; i++)
        {
            files_names.push_back(inodes[i].name);
            std::cout << inodes[i].name << std::endl;
        }
    }
};

struct disk_block
{
    int next_block_num;
    char data[BLOCKSIZE];
};

void create_fs(); // initialize new filesystem
void mount_fs();  // load a file system
void sync_fs();   // write the file system

// return filenumber
int allocate_file(char name[8]);
void set_filesize(int filenum, int size);
// ssize_t mywrite(int myfd, const void *buf, size_t count);
__ssize_t mywrite(int myfd, const void *buf, size_t count);

void print_fs(); // print out info avbout the file system

void mymkfs();

int myopen(const char *, int);
int myclose(int);
ssize_t myread(int, void *, size_t t);
ssize_t mywrite(int, const void *, size_t);
off_t mylseek(int, off_t, int);
myDIR *myopendir(const char *);
struct mydirent *myreaddir(myDIR *);
int myclosedir(myDIR *);
