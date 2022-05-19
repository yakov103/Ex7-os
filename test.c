#include <stdio.h>
#include "fs.h"

void main()
{
    /**
     * @brief first check this
     *
     */
    // create_fs();
    // sync_fs();

    /***/
    mount_fs();
    // allocat_file("first");
    sync_fs();
    print_fs();
    printf("done\n");

    /**
     * @brief second check this
     *
     */
    // mount_fs();
    // sync_fs();
    // print_fs();
    // printf("done\n");
}