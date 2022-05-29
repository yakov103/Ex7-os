#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "fs.hpp"
/*
struct superblock
{
    int num_inodes;
    int num_blocks;
    int size_blocks;
};

struct inode
{
    int size;
    char name[8];
};

struct disk_block
{
    int next_block_num;
    char data[512];
};

*/

std::vector<int> myDIR::open_files;

struct superblock sb;
struct inode *inodes;
struct disk_block *dbs;
struct mydirent *file_entry;
int *current_entry = (int *)malloc(sizeof(int));

int find_empty_inode()
{
    int i;
    for (i = 0; i < sb.num_inodes; i++)
    {
        if (inodes[i].size == -1)
        {
            return i;
        }
    }
    return -1;
} // return empty inode

int get_block_num(int file, int offset)
{

    int togo = offset;
    int bn = inodes[file].first_block;
    while (togo > 0)
    {
        bn = dbs[bn].next_block_num;
        togo--;
    }
    return bn;
} // get_block_num

void shorten_file(int bn)
{
    int nn = dbs[bn].next_block_num;
    if (nn >= 0)
    {
        shorten_file(nn);
    }
    dbs[bn].next_block_num = -1;
} // shorten_file

int find_empty_block()
{
    int i;
    for (i = 0; i < sb.num_blocks; i++)
    {
        if (dbs[i].next_block_num == -1)
        {
            return i;
        }
    }
    return -1;
} // return empty block

// initialize new filesystem
void create_fs()
{
    sb.num_inodes = 10;
    sb.num_blocks = 100;
    sb.size_blocks = sizeof(struct disk_block);

    int i;
    inodes = (struct inode *)malloc(sizeof(struct inode) * sb.num_inodes);
    for (i = 0; i < sb.num_inodes; i++)
    {
        inodes[i].size = -1;
        inodes[i].first_block = -1;
        strcpy(inodes[i].name, "emptyfi");
        inodes[i].type = FILE_TYPE_UNSET;

    } // init inodes

    inodes[0].first_block = 0;
    inodes[1].first_block = 10;
    inodes[2].first_block = 20;
    inodes[3].first_block = 30;
    inodes[4].first_block = 40;
    inodes[5].first_block = 50;
    inodes[6].first_block = 60;
    inodes[7].first_block = 70;
    inodes[8].first_block = 80;
    inodes[9].first_block = 90;

    dbs = (struct disk_block *)malloc(sizeof(struct disk_block) * sb.num_blocks);

    for (i = 0; i < sb.num_blocks; i++)
    {
        dbs[i].next_block_num = -1;
    } // init disk_block

} // create filesystem

// load a file system
void mount_fs()
{
    FILE *file;
    file = fopen("fs_data", "r");

    // superblock
    fread(&sb, sizeof(struct superblock), 1, file);

    // inodes
    inodes = (struct inode *)malloc(sizeof(struct inode) * sb.num_inodes);
    dbs = (struct disk_block *)malloc(sizeof(struct disk_block) * sb.num_blocks);

    fread(inodes, sizeof(struct inode), sb.num_inodes, file);
    fread(dbs, sizeof(struct disk_block), sb.num_blocks, file);
    file_entry = (struct mydirent *)malloc(sizeof(struct mydirent));
    current_entry = (int *)malloc(sizeof(int));
    fclose(file);
} // mount_fs()

// write the file system
void sync_fs()
{
    FILE *file;
    file = fopen("fs_data", "w+");
    // superblock
    fwrite(&sb, sizeof(struct superblock), 1, file);

    fwrite(inodes, sizeof(struct inode), sb.num_inodes, file);
    fwrite(dbs, sizeof(struct disk_block), sb.num_blocks, file);

    fclose(file);

} // sync_fs

void print_fs()
{
    printf("Superblock info \n");
    printf("\tnum inodes: %d\n", sb.num_inodes);
    printf("\tnum blocks: %d\n", sb.num_blocks);
    printf("\tsize blocks: %d\n", sb.size_blocks);

    printf("inodes\n");
    int i;
    for (i = 0; i < sb.num_inodes; i++)
    {
        printf("\tsize: %d block: %d name: %s type: %d used_size: %d\n", inodes[i].size, inodes[i].first_block, inodes[i].name, inodes[i].type, inodes[i].used_size);
    } // init inodes

    for (i = 0; i < sb.num_blocks; i++)
    {
        printf("\tblock num: %d next block %d\n", i, dbs[i].next_block_num);
    } // init disk_block

} // print_fs

int allocate_file(char name[8])
{
    // check if file exists
    int i;
    for (i = 0; i < sb.num_inodes; i++)
    {
        if (strcmp(inodes[i].name, name) == 0)
        {
            printf("file already exists\n");
            return i;
        }
    }

    // find an empty inode
    int in = find_empty_inode();
    // find / claim a disk block
    // int block = find_empty_block();

    // claim them
    // inodes[in].first_block = block;
    inodes[in].size = 0;
    dbs[inodes[in].first_block].next_block_num = -2;

    strcpy((inodes[in]).name, name);
    // return the file descriptor
    return in;

} // allocate_file

// add / delet blocks
void set_filesize(int filenum, int size)
{

    // how many blocks should we have
    int tmp = size + BLOCKSIZE - 1;
    int num = tmp / BLOCKSIZE;
    int bn = inodes[filenum].first_block;
    num--;
    // grow the file if necessary
    while (num > 0)
    {
        // check next block number
        int next_num = dbs[bn].next_block_num;
        if (next_num == -1)
        {
            int empty = find_empty_block();
            dbs[bn].next_block_num = empty;
            dbs[empty].next_block_num = -2;
        }
        bn = dbs[bn].next_block_num;
        num--;
    }

    // shoten if necessary
    shorten_file(bn);
    dbs[bn].next_block_num = -2;

} // set_filesize

int mymkfs()
{

    create_fs();
    sync_fs();
    char param[8] = "root";
    int directory = allocate_file(param);
    inodes[directory].type = FILE_TYPE_DIRECTORY;
    *current_entry = 1;
    file_entry = (struct mydirent *)malloc(sizeof(struct mydirent));
    return directory;

} // mymkfs

int myopen(const char *pathname, int flags)
{

    int in;
    // check if file exists
    int file_num = -1;
    for (int i = 0; i < sb.num_inodes; i++)
    {
        if (strcmp(inodes[i].name, pathname) == 0)
        {
            file_num = i;
        }
    }

    //     enum Permission
    // {
    //     PERMISSION_READ, // 0
    //     PERMISSION_WRITE, // 1
    //     PERMISSION_EXECUTE, // 2
    //     PERMISSION_UNSET // 3
    // };
    if (flags == PERMISSION_READ)
    {
        // so its read only
        if (file_num == -1)
        {
            // error no such file
            printf("file does not exist\n");
            return -1;
        }
        else
        {
            myDIR::open_files.push_back(file_num);
            return file_num;
        }
    }
    if (flags == PERMISSION_WRITE || flags == PERMISSION_EXECUTE || flags == PERMISSION_READ_WRITE)
    {
        if (file_num == -1)
        {
            // error no such file
            // find an empty inode
            in = find_empty_inode();
            strcpy((inodes[in]).name, pathname);
            inodes[in].type = FILE_TYPE_REGULAR;
            inodes[in].permission = (Permission)flags;
            inodes[in].size = 0;
            dbs[inodes[in].first_block].next_block_num = -2;
            myDIR::open_files.push_back(in);
        }
        else
        {
            // exists
            in = file_num;
            myDIR::open_files.push_back(file_num);
        }
    }
    if (flags == PERMISSION_APPEND)
    {
        // so its append
        if (file_num == -1)
        {
            // error no such file
            printf("file does not exist\n");
            return -1;
        }
        else
        {
            // exists
            in = file_num;
            inodes[in].current_offset = inodes[in].used_size;
            myDIR::open_files.push_back(file_num);
        }
    }

    // // claim them
    // inodes[in].first_block = block;
    // dbs[block].next_block_num = -2;

    // return the file descriptor
    return in;

} // myopen

myDIR *myopendir(const char *name)
{
    if (name[0] != 'r' && name[1] != 'o' && name[2] != 'o' && name[3] != 't')
    {
        printf("invalid directory\n");
        return NULL;
    }
    myDIR *rootDIR = new myDIR();
    rootDIR->inode_num = 0;
    rootDIR->inode = &inodes[rootDIR->inode_num];
    if (rootDIR->inode->type != FILE_TYPE_DIRECTORY)
    {
        printf("not a directory\n");
        return NULL;
    }
    else
    {
        return rootDIR;
    }

} // myopendir

int myclose(int myfd)
{
    // TODO check the quality of code
    int i;
    for (i = 0; i < (int)myDIR::open_files.size(); i++)
    {
        if (myDIR::open_files[i] == myfd)
        {
            myDIR::open_files.erase(myDIR::open_files.begin() + i);
            return 0;
        }
    }
    return -1;
} // myclose

ssize_t myread(int myfd, void *buff, size_t count)
{
    printf("myread(%d, %p, %ld)\n", myfd, buff, count);
    char *data = (char *)buff;
    // check if myfd is opened
    if (std::find(myDIR::open_files.begin(), myDIR::open_files.end(), myfd) != myDIR::open_files.end())
    {
        if (inodes[myfd].type == FILE_TYPE_DIRECTORY)
        {
            printf("directory\n");
            return 0;
        }
        if (inodes[myfd].permission != PERMISSION_READ && inodes[myfd].permission != PERMISSION_READ_WRITE && myfd == 0)
        {
            printf("permission not set to read! denied\n");
            return 0;
        }
        if (inodes[myfd].current_offset + count > 5120)
        {
            printf("file write too big\n");
            return 0;
        }
        // TODO fix the other side of the equation
        if (inodes[myfd].used_size <= (int)count)
        {
            count = inodes[myfd].used_size;
        }

        int data_block_num = inodes[myfd].first_block;
        printf("\ncount %ld \n", count);
        int number_of_blocks_to_read = (int)count / BLOCKSIZE;
        number_of_blocks_to_read++;

        printf("\nnumber of blocks to read %d\n", number_of_blocks_to_read);
        int helper_choose_block = inodes[myfd].current_offset / BLOCKSIZE;
        int block_number = data_block_num + helper_choose_block;
        // int index_to_read = 0;
        int index_to_read = inodes[myfd].current_offset % BLOCKSIZE;
        size_t iter_number = 0;
        while (iter_number < count)
        {
            data[iter_number] = dbs[block_number].data[index_to_read];
            index_to_read++;
            if (index_to_read % BLOCKSIZE == 0)
            {
                block_number++;
                index_to_read = 0;
            }
            iter_number++;
        }
    }
    else
    {
        printf("file not open\n");
        return 0;
    }

    return 0;
} // myread

ssize_t mywrite(int myfd, void *buff, size_t count)
{
    printf("mywrite(%d, %p, %ld)\n", myfd, buff, count);
    const char *data = (const char *)buff;
    if (std::find(myDIR::open_files.begin(), myDIR::open_files.end(), myfd) != myDIR::open_files.end())
    {
        if (inodes[myfd].type == FILE_TYPE_DIRECTORY)
        {
            printf("directory\n");
            return 0;
        }
        if (inodes[myfd].permission != PERMISSION_WRITE && inodes[myfd].permission != PERMISSION_READ_WRITE && myfd == 0)
        {
            printf("permission not set to write! denied\n");
            return 0;
        }
        if (inodes[myfd].current_offset + count > 5120)
        {
            printf("file write too big\n");
            return 0;
        }

        int data_block_num = inodes[myfd].first_block;
        printf("\ncount %ld \n", count);
        int number_of_blocks_to_write = (int)count / BLOCKSIZE;
        printf("\nnumber of blocks to read %d\n", number_of_blocks_to_write);
        int helper_choose_block = inodes[myfd].current_offset / BLOCKSIZE;
        int block_number = data_block_num + helper_choose_block;

        int index_to_write = inodes[myfd].current_offset % BLOCKSIZE;
        size_t iter_number = 0;
        while (iter_number < count)
        {
            dbs[block_number].data[index_to_write] = data[index_to_write];
            index_to_write++;
            if (index_to_write % BLOCKSIZE == 0)
            {
                block_number++;
                index_to_write = 0;
            }
            iter_number++;
        }
        inodes[myfd].used_size = inodes[myfd].current_offset + count;
    }
    else
    {
        printf("file not open\n");
        return 0;
    }
    return 0;
} // mywrite

off_t mylseek(int fd, off_t offset, int whence)
{

    printf("mylseek(%d, %ld, %d)\n", fd, offset, whence);
    if (std::find(myDIR::open_files.begin(), myDIR::open_files.end(), fd) != myDIR::open_files.end())
    {
        if (inodes[fd].type == FILE_TYPE_DIRECTORY)
        {
            printf("directory\n");
            return -1;
        }
        if (inodes[fd].permission != PERMISSION_READ && inodes[fd].permission != PERMISSION_READ_WRITE && inodes[fd].permission != PERMISSION_WRITE && fd == 0)
        {
            printf("permission not set to read! denied\n");
            return 0;
        }

        if (whence == SEEK_SET)
        {
            if (offset > inodes[fd].used_size)
            {
                printf("offset is greater than file size\n");
                return -1;
            }
            else
            {
                inodes[fd].current_offset = offset;
                return offset;
            }
        }
        else if (whence == SEEK_CUR)
        {
            if (inodes[fd].current_offset + offset > inodes[fd].used_size)
            {
                printf("offset is greater than file size\n");
                return -1;
            }
            else
            {
                inodes[fd].current_offset += offset;
                return inodes[fd].current_offset;
            }
        }
        else if (whence == SEEK_END)
        {
            if (offset > inodes[fd].used_size)
            {
                printf("offset is greater than file size\n");
                return -1;
            }
            else
            {
                inodes[fd].current_offset = inodes[fd].used_size - offset;
                return inodes[fd].current_offset;
            }
        }
        else
        {
            printf("invalid whence\n");
            return -1;
        }
    }
    else
    {
        printf("file not open\n");
        return -1;
    }

    return -1;

}; // mylseek

struct mydirent *myreaddir(myDIR *dir)
{
    printf("myreaddir()\n");

    while (*current_entry < 10)
    {

        if (inodes[*current_entry].type == FILE_TYPE_DIRECTORY)
        {
            printf("directory\n");
            current_entry++;
            continue;
        }
        if (inodes[*current_entry].size >= 0)
        {
            file_entry->inode_num = *current_entry;
            strcpy(file_entry->d_name, inodes[*current_entry].name);
            (*current_entry)++;
            return file_entry;
        }
        *current_entry = 1;
        return NULL;
    }

    return file_entry;
}; // myreaddir

int myclosedir(myDIR *dir)
{
    // sync the data to the file system
    sync_fs();
    delete dir;
    printf("myclosedir()\n");
    return 0;
}; // myclosedir
