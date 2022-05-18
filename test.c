#include <stdio.h>
#include "fs.h"

void main()
{
    create_fs();
    sync_fs();
    printf("done\n");
    // printf("%d\n", sb.num_inodes);
}