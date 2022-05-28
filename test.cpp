#include <stdio.h>
#include "fs.hpp"
#include <string.h>
#include <string>

int main(int argc, char *argv[])
{
    // https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
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
    printf("file num is %d\n", file_num);

    std::string data = "yakov is good ";

    mywrite(file_num, (void *)data.c_str(), strlen(data.c_str()));
    char buffer[100];
    myread(file_num, buffer, 10);
    printf("%s\n", buffer);

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

    print_fs();
    return 0;
} // main