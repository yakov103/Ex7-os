#pragma once

// meta information about the filesystem
// number of inodes
// numver of disk blocks
// size of the disk blocks

#define BLOCKSIZE 512
#define MAXFILESYSTEMSIZE 51600
#define MAX_FILES 10000

struct superblock
{
    int num_inodes;
    int num_blocks;
    int size_blocks;
};

struct inode
{
    int permissions;
    int used_size;
    int size;
    int first_block;
    char name[8];
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

extern struct inode myopenfile[MAX_FILES];

int myopen(const char *, int);

int mymount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags, const void *data);
