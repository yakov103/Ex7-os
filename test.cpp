#include "doctest.h"
#include <stdio.h>
#include "myfs.hpp"
#include "mystdio.h"

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

//  printf(RED "red\n"     RESET);
//   printf(GRN "green\n"   RESET);
//   printf(YEL "yellow\n"  RESET);
//   printf(BLU "blue\n"    RESET);
//   printf(MAG "magenta\n" RESET);
//   printf(CYN "cyan\n"    RESET);
//   printf(WHT "white\n"   RESET);

TEST_CASE("no throw")
{
    printf(CYN "**********first test**********\n" RESET);
    sb.num_inodes = 10;
    CHECK_NOTHROW(mymkfs());
    printf(GRN "CHECK_NOTHROW(mymkfs()); good!\n" RESET);

    const char *dir_name = "root";
    myDIR *root = myopendir(dir_name);
    CHECK_NOTHROW(myopendir(dir_name));
    printf(GRN "CHECK_NOTHROW(myopendir(dir_name)); good!\n" RESET);

    const char *file_name = "test";
    myopen(file_name, PERMISSION_READ_WRITE);
    printf(GRN "myopen(file_name, PERMISSION_READ_WRITE); good!\n" RESET);
    int file_num = myopen(file_name, PERMISSION_READ_WRITE);
    std::string data = "yakov is good ";
    mywrite(file_num, (void *)data.c_str(), strlen(data.c_str()));
    CHECK_NOTHROW(mywrite(file_num, (void *)data.c_str(), strlen(data.c_str())));
    printf(GRN "CHECK_NOTHROW(mywrite(file_num, (void *)data.c_str(), strlen(data.c_str()))); good!\n" RESET);

    CHECK_NOTHROW(mylseek(file_num, 6, SEEK_SET));
    printf(GRN "CHECK_NOTHROW(mylseek(file_num, 6, SEEK_SET)); good!\n" RESET);

    char buffer[100];
    CHECK_NOTHROW(myread(file_num, buffer, 7));
    printf(GRN "CHECK_NOTHROW(myread(file_num, buffer, 7)); good!\n" RESET);
    CHECK_NOTHROW(myclose(file_num));
    const char *file_name2 = "second";
    int file_num2 = myopen(file_name2, PERMISSION_READ_WRITE);
    CHECK_NOTHROW(myopen(file_name2, PERMISSION_READ_WRITE));
    printf(GRN "myopen(file_name2, PERMISSION_READ_WRITE); good!\n" RESET);

    std::string data2 = "dolev dublon king ";

    CHECK_NOTHROW(mywrite(file_num2, (void *)data2.c_str(), strlen(data2.c_str())));
    printf(GRN "CHECK_NOTHROW(mywrite(file_num2, (void *)data2.c_str(), strlen(data2.c_str()))); good!\n" RESET);
    CHECK_NOTHROW(mylseek(file_num2, 6, SEEK_SET));
    printf(GRN "CHECK_NOTHROW(mylseek(file_num2, 6, SEEK_SET)); good!\n" RESET);

    char buffer2[100];

    CHECK_NOTHROW(myread(file_num2, buffer2, 7));
    printf(GRN "CHECK_NOTHROW(myread(file_num2, buffer2, 7)); good!\n" RESET);

    CHECK_NOTHROW(myclose(file_num2));
    printf(GRN "CHECK_NOTHROW(myclose(file_num2)); good!\n" RESET);

    struct mydirent *directory_entry;
    CHECK_NOTHROW(myreaddir(root));
    printf(GRN "CHECK_NOTHROW(myreaddir(root)); good!\n" RESET);
    if (root == NULL)
    {
        printf("Error! Unable to open directory.\n");
        exit(1);
    }
    while ((directory_entry = myreaddir(root)) != NULL)
    {
        // printf(">> %s\n", directory_entry->d_name);
    }
    CHECK_NOTHROW(myclosedir(root));
    printf(GRN "CHECK_NOTHROW(myclosedir(root)); good!\n" RESET);
    CHECK_NOTHROW(sync_fs());
    printf(GRN "CHECK_NOTHROW(sync_fs()); good!\n" RESET);
}

TEST_CASE("demo"){
    printf(CYN "**********second test**********\n" RESET);
    sb.num_inodes = 10;
    CHECK_NOTHROW(mymkfs());
    printf(GRN "CHECK_NOTHROW(mymkfs()); good!\n" RESET);

    const char *dir_name = "root";
    myDIR *root = myopendir(dir_name);
    CHECK_NOTHROW(myopendir(dir_name));
    printf(GRN "CHECK_NOTHROW(myopendir(dir_name)); good!\n" RESET);

    const char *file_name = "test";
    myopen(file_name, PERMISSION_READ_WRITE);
    printf(GRN "myopen(file_name, PERMISSION_READ_WRITE); good!\n" RESET);
    int file_num = myopen(file_name, PERMISSION_READ_WRITE);
    std::string data = "yakov is good ";
    mywrite(file_num, (void *)data.c_str(), strlen(data.c_str()));
    CHECK_NOTHROW(mywrite(file_num, (void *)data.c_str(), strlen(data.c_str())));
    printf(GRN "CHECK_NOTHROW(mywrite(file_num, (void *)data.c_str(), strlen(data.c_str()))); good!\n" RESET);

    CHECK_NOTHROW(mylseek(file_num, 6, SEEK_SET));
    printf(GRN "CHECK_NOTHROW(mylseek(file_num, 6, SEEK_SET)); good!\n" RESET);

    char buffer[100];
    CHECK_NOTHROW(myread(file_num, buffer, 7));
    printf(GRN "CHECK_NOTHROW(myread(file_num, buffer, 7)); good!\n" RESET);
    CHECK_NOTHROW(myclose(file_num));
    const char *file_name2 = "second";
    int file_num2 = myopen(file_name2, PERMISSION_READ_WRITE);
    CHECK_NOTHROW(myopen(file_name2, PERMISSION_READ_WRITE));
    printf(GRN "myopen(file_name2, PERMISSION_READ_WRITE); good!\n" RESET);
    
}