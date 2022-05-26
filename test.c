#include <stdio.h>
#include "fs.h"

int main()
{
    /**
     * @brief first check this
     *
     */
    create_fs();
    sync_fs();

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

    // set_filesize(0, 1000);
    // print_fs();

    // sync_fs();
    // print_fs();
    // printf("done\n");

    /*****
     * * another example
     * *
     * ****/

    mount_fs();
    // allocate_file("first");
    int file = allocate_file("another");

    char *data = "dolev";
    

    // https://stackoverflow.com/questions/2329842/checking-for-success-of-fwrite-in-c-perror
    // ssize_t mywrite(int myfd, const void *buf, size_t count);

    mywrite(file, data, sizeof(data));

    sync_fs();

    print_fs();
    printf("done\n");

    return 0;
} // main