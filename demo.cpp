#include <stdio.h>
#include "myfs.hpp"
#include "mystdio.h"
#include <string.h>
#include <string>

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
            printf("\nERROR:The Number Passed Is TOO much big\n");
            return 1;
        }
        // get the argv to number
        int argv_to_number = std::stoi(argv[1]);
        // devide by 10 and if the number is smallar than 10 then make it 10
        if (argv_to_number <= 10)
        {
            argv_to_number = 10;
        }
        // then devide by 10 and multiply by ten to get the number of inodes
        sb.num_inodes = (argv_to_number / 10 * 10) + 10;
        // printf("\nnumber of inodes %d\n", sb.num_inodes);
        // return 1;
    }

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

    char buffer4[100] = "buffer 4.5 has written";
    myfwrite(buffer4, strlen(buffer4), 1, file);

    /* Seek to the beginning of the file */
    mylseek(file->file->file_num, 0, SEEK_SET);
    char buffer5[100];
    float number4 = 0.0;
    myfscanf(file, "%s %f", buffer5, &number4);
    printf("return from myfscanf: %s  : %f\n", buffer5, number4);
    char buffer6[100] = "buffer 6 has written";
    mylseek(file->file->file_num, 0, SEEK_SET);
    int q = 0;
    myfprintf(file, "%s", buffer6);
    /* Seek to the beginning of the file */
    mylseek(file->file->file_num, 0, SEEK_SET);
    char buffer7[100];
    myfscanf(file, "%s %d", buffer7, &q);
    printf("return from myfscanf: %s %d\n", buffer7, q);

    


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

    print_fs();
    sync_fs();

    return 0;
} // main
