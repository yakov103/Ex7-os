#include <stdio.h>
#include "myfs.hpp"
#include "mystdio.h"
#include <string.h>
#include <string>

// uncomment this    if (argc == 1)
// uncomment this    {
// uncomment this        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
// uncomment this    }
// uncomment this    if (argc >= 2)
// uncomment this    {
// uncomment this        if (std::stoi(argv[1]) >= MAXFILESYSTEMSIZE)
// uncomment this        {
// uncomment this            printf("\nERROR:The Number Passed Is Greater Than file system memory\n");
// uncomment this            return 1;
// uncomment this        }
// printf("\nNumber Of Arguments Passed: %d", argc);
// printf("\n----Following Are The Command Line Arguments Passed----");
// for (counter = 0; counter < argc; counter++)
// {
//     printf("\nargv[%d]: %s", counter, argv[counter]);
// }
// uncomment this    }

int main(int argc, char *argv[])
{
    // https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
    if (argc == 1)
    {
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
        sb.num_inodes = 10;
    }
    if (argc >= 2)
    {
        if (std::stoi(argv[1]) >= MAXFILESYSTEMSIZE)
        {
            printf("\nERROR:The Number Passed Is Greater Than file system memory\n");
            return 1;
        }
        // printf("\nNumber Of Arguments Passed: %d", argc);
        // printf("\n----Following Are The Command Line Arguments Passed----");
        // for (counter = 0; counter < argc; counter++)
        // {
        //     printf("\nargv[%d]: %s", counter, argv[counter]);
        // }
    }

    /**
     * @brief first check this
     *
     */
    // create_fs();
    // sync_fs();

    /***/
    // mount_fs();
    // // allocate_file("first");
    // sync_fs();
    // print_fs();
    // printf("done\n");

    /*****
     * * another example
     * *
     * ****/

    // mount_fs();
    // // alocate_file("first");

    // set_filesize(0, 1000);
    // print_fs();

    // set_filesize(0, 5000);
    // print_fs();

    // print_fs();

    // sync_fs();
    // print_fs();
    // printf("done\n");

    /*****
     * * another example
     * *
     * ****/

    // mount_fs();
    // // int file = allocate_file("first");
    // // set_filesize(0, 4200);
    // int file = allocate_file("second");
    // set_filesize(file, 4200);

    // char *data = "yakov is good ";

    // // https://stackoverflow.com/questions/2329842/checking-for-success-of-fwrite-in-c-perror
    // // ssize_t mywrite(int myfd, const void *buf, size_t count);

    // mywrite(file, data, strlen(data));

    // sync_fs();

    // print_fs();
    // printf("done\n");

    int dir_num = mymkfs();
    const char *dir_name = "root";
    myDIR *root = myopendir(dir_name);

    if (root->inode_num == dir_num)
    {
        printf("\nroot directory is created\n");
    }
    else
    {
        printf("\nroot directory is not created\n");
    }

    //     enum Permission
    // {
    //     PERMISSION_READ, // 0
    //     PERMISSION_WRITE, // 1
    //     PERMISSION_EXECUTE, // 2
    //     PERMISSION_UNSET // 3
    // };
    const char *file_name = "first";
    int file_num = myopen(file_name, PERMISSION_READ_WRITE);
    printf("myopen: file num is %d\n", file_num);
    std::string data = "yakov is good ";
    mywrite(file_num, (void *)data.c_str(), strlen(data.c_str()));
    mylseek(file_num, 6, SEEK_SET);
    char buffer[100];
    myread(file_num, buffer, 7);
    myclose(file_num);
    const char *file_name2 = "second";
    int file_num2 = myopen(file_name2, PERMISSION_READ_WRITE);
    printf("myopen: file num is %d\n", file_num2);
    std::string data2 = "dolev dublon king ";
    mywrite(file_num2, (void *)data2.c_str(), strlen(data2.c_str()));
    mylseek(file_num2, 6, SEEK_SET);
    char buffer2[100];
    myread(file_num2, buffer2, 7);
    printf("myread: %s\n", buffer2);
    myclose(file_num2);

    // test FILE
    myFILE *file = myfopen(file_name, "r+");
    char buffer3[100];
    myfread(buffer3, 14, 1, file);
    printf("return from myfread: %s\n", buffer3);
    /* Seek to the beginning of the file */
    mylseek(file->file->file_num, 0, SEEK_SET);

    char buffer4[100] = "buffer 4 has written";
    myfwrite(buffer4, 5, 1, file);

    /* Seek to the beginning of the file */
    mylseek(file->file->file_num, 0, SEEK_SET);
    char buffer5[100];
    myfscanf(file, "%s", buffer5);
    printf("return from myfscanf: %s\n", buffer5);
    char buffer6[100] = "buffer 6 has written";
    myfprintf(file, "%s", buffer6);
    /* Seek to the beginning of the file */
    mylseek(file->file->file_num, 0, SEEK_SET);
    char buffer7[100];
    myfscanf(file, "%s", buffer7);
    printf("return from myfscanf: %s\n", buffer7);
    myfclose(file);

    struct mydirent *directory_entry;

    if (root == NULL)
    {
        printf("Error! Unable to open directory.\n");
        exit(1);
    }
    while ((directory_entry = myreaddir(root)) != NULL)
    {
        printf(">> %s\n", directory_entry->d_name);
    }
    myclosedir(root);

    // char data[8] = "dolev";
    // https://stackoverflow.com/questions/2329842/checking-for-success-of-fwrite-in-c-perror
    // ssize_t mywrite(int myfd, const void *buf, size_t count);
    // mywrite(file, data, sizeof(data));
    // myDIR a = myDIR();
    // char mySTR[8] = "direct";
    // int inode_num = allocate_file(mySTR);
    // a.inode_num = inode_num;
    // a.inode = &inodes[inode_num];

    sync_fs();

    // print_fs();
    return 0;
} // main
