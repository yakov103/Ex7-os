#include <stdio.h>
#include "fs.hpp"
#include <string.h>
#include <string>

int main(int argc, char *argv[])
{
    // https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
    if (argc == 1)
    {
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
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

    mymkfs();
    myDIR a = myDIR();
    a.inode = allocate_file("direc");

    return 0;
} // main