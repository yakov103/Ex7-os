#ifndef FS_HPP
#define FS_HPP
// meta information about the filesystem
// number of inodes
// numver of disk blocks
// size of the disk blocks

#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include <sys/types.h>

#define BLOCKSIZE 512
#define MAXFILESYSTEMSIZE 51600
#define MAX_FILES 10000

enum FileType
{
    FILE_TYPE_REGULAR,   // 0
    FILE_TYPE_DIRECTORY, // 1
    FILE_TYPE_UNSET      // 2
};

enum Permission
{
    PERMISSION_READ,    // 0
    PERMISSION_WRITE,   // 1
    PERMISSION_EXECUTE, // 2
    PERMISSION_UNSET,    // 3
    PERMISSION_READ_WRITE    // 4
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
    int current_offset = 0;
    int used_size = 0;
    int size;
    int first_block;
    char name[8];
};

class myDIR
{
public:
    int inode_num;
    struct inode *inode;
    static std::vector<std::string> files_names;
    static std::vector<int> open_files;
    myDIR() = default;
    myDIR(struct inode *inode, struct superblock *sb, struct inode *inodes)
    {
        // this->inode_num = ;
        this->inode = inode;
        this->inode->type = FILE_TYPE_DIRECTORY;
        strcpy(this->inode->name, "root");
        this->inode->permission = PERMISSION_READ;
        this->inode->used_size = 0;
        this->inode->size = 0;
        this->inode->first_block = -2;

        for (int i = 0; i < sb->num_inodes; i++)
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



void print_fs(); // print out info avbout the file system
int mymkfs(); // finish i think
int myopen(const char *, int); // finish i think open a inode with flags
int myclose(int); // finish i think
ssize_t myread(int, void *, size_t);// finish i think
ssize_t mywrite(int, void *, size_t);// finish i think
off_t mylseek(int, off_t, int); // finish i think 
myDIR *myopendir(const char *); // finish i think , open root directory


struct mydirent *myreaddir(myDIR *);
int myclosedir(myDIR *);

extern struct superblock sb;
extern struct inode *inodes;
extern struct disk_block *dbs;

#endif