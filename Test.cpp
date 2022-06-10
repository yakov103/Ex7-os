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

/**
 * @brief     Tests the myfs class.
 *
 * int mymount(const char *source, const char *target,

const char *filesystemtype, unsigned long

mountflags, const void *data);

int myopen(const char *pathname, int flags);

int myclose(int myfd);

ssize_t myread(int myfd, void *buf, size_t count);

ssize_t mywrite(int myfd, const void *buf, size_t count);

off_t mylseek(int myfd, off_t offset, int whence);

myDIR *myopendir(const char *name);

struct mydirent *myreaddir(myDIR *dirp);

int myclosedir(myDIR *dirp);

 */

/**
 * @brief
 *
myFILE *myfopen(const char *restrict pathname, const char *restrict mode)

int myfclose(myFILE *stream);

size_t myfread(void *restrict ptr, size_t size, size_t nmemb, myFILE *restrict stream);

size_t myfwrite(const void *restrict ptr, size_t size, size_t nmemb, myFILE *restrict stream);

int myfseek(myFILE *stream, long offset, int whence);

int myfscanf(myFILE *restrict stream,

const char *restrict format, ...);

int myfprintf(myFILE *restrict stream,

const char *restrict format, ...);

 *
 */

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

    // test FILE
    myFILE *file = myfopen(file_name, "r+");
    CHECK_NOTHROW(myfopen(file_name, "r+"));
    printf(GRN "myfopen(file_name, \"r+\"); good!\n" RESET);

    char buffer3[100];
    myfread(buffer3, 14, 1, file);
    CHECK_NOTHROW(myfread(buffer3, 14, 1, file));
    printf(GRN "myfread(buffer3, 14, 1, file); good!\n" RESET);

    /* Seek to the beginning of the file */
    mylseek(file->file->file_num, 0, SEEK_SET);
    CHECK_NOTHROW(mylseek(file->file->file_num, 0, SEEK_SET));
    printf(GRN "mylseek(file->file->file_num, 0, SEEK_SET); good!\n" RESET);

    // test myfseek
    myfseek(file, 6, SEEK_SET);
    CHECK_NOTHROW(myfseek(file, 6, SEEK_SET));
    printf(GRN "myfseek(file, 6, SEEK_SET); good!\n" RESET);

    char buffer4[100] = "buffer 4.5 has written";
    myfwrite(buffer4, strlen(buffer4), 1, file);
    CHECK_NOTHROW(myfwrite(buffer4, strlen(buffer4), 1, file));
    printf(GRN "myfwrite(buffer4, strlen(buffer4), 1, file); good!\n" RESET);

    /* Seek to the beginning of the file */
    mylseek(file->file->file_num, 0, SEEK_SET);
    CHECK_NOTHROW(mylseek(file->file->file_num, 0, SEEK_SET));
    printf(GRN "mylseek(file->file->file_num, 0, SEEK_SET); good!\n" RESET);

    char buffer5[100];
    float number4 = 0.0;
    myfscanf(file, "%s %f", buffer5, &number4);
    CHECK_NOTHROW(myfscanf(file, "%s %f", buffer5, &number4));
    printf(GRN "myfscanf(file, buffer5, &number4); good!\n" RESET);

    char buffer6[100] = "buffer 6 has written";
    mylseek(file->file->file_num, 0, SEEK_SET);
    CHECK_NOTHROW(mylseek(file->file->file_num, 0, SEEK_SET));
    printf(GRN "mylseek(file->file->file_num, 0, SEEK_SET); good!\n" RESET);

    int q = 0;
    myfprintf(file, "%s", buffer6);
    CHECK_NOTHROW(myfprintf(file, "%s", buffer6));
    printf(GRN "myfprintf(file, ; good!\n" RESET);

    /* Seek to the beginning of the file */
    mylseek(file->file->file_num, 0, SEEK_SET);
    CHECK_NOTHROW(mylseek(file->file->file_num, 0, SEEK_SET));
    printf(GRN "mylseek(file->file->file_num, 0, SEEK_SET); good!\n" RESET);

    char buffer7[100];
    myfscanf(file, "%s %d", buffer7, &q);
    CHECK_NOTHROW(myfscanf(file, "%s %d", buffer7, &q));
    printf(GRN "myfscanf(file, , buffer7, &q); good!\n" RESET);

    CHECK_NOTHROW(myfclose(file));
    printf(GRN "myfclose(file); good!\n" RESET);

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
    CHECK_NOTHROW(mymount());
    printf(GRN "CHECK_NOTHROW(mymount()); good!\n" RESET);
}

TEST_CASE("demo")
{
    printf(CYN "**********second test**********\n" RESET);
    sb.num_inodes = 10;
    mymkfs();
    const char *dir_name = "root";
    myDIR *root = myopendir(dir_name);
    const char *file_name = "first";
    int file_num = myopen(file_name, PERMISSION_READ_WRITE);
    std::string data = "yakov is good ";
    mywrite(file_num, (void *)data.c_str(), strlen(data.c_str()));
    char buffer[100];
    memset(buffer, 0, 100);
    myread(file_num, buffer, 5);
    CHECK(strncmp(buffer, "yakov", 5) == 0);
    printf(GRN "CHECK(strcmp(buffer, \"yakov\") == 0); good!\n" RESET);
    mylseek(file_num, 6, SEEK_SET);
    myread(file_num, buffer, 7);
    CHECK(strcmp(buffer, "is good") == 0);
    printf(GRN "CHECK(strcmp(buffer, \"is good\") == 0); good!\n" RESET);
    // close the file and open it in append mode and test
    myclose(file_num);
    file_num = myopen(file_name, PERMISSION_APPEND);
    // break Test.cpp:229 break myfs.cpp:472 continue  break myfs.cpp:482 print dbs[block_number].data
    // clean buffer
    char buffer2[100];
    memset(buffer2, 0, 100);
    mywrite(file_num, (void *)data.c_str(), strlen(data.c_str()));
    myclose(file_num);
    file_num = myopen(file_name, PERMISSION_READ_WRITE);
    myread(file_num, buffer2, 28);
    // CHECK(strcmp(buffer, "yakov is good yakov is good") == 0);

    CHECK(buffer2[0] == 'y');
    CHECK(buffer2[1] == 'a');
    CHECK(buffer2[2] == 'k');
    CHECK(buffer2[3] == 'o');
    CHECK(buffer2[4] == 'v');
    CHECK(buffer2[5] == ' ');
    CHECK(buffer2[6] == 'i');
    CHECK(buffer2[7] == 's');
    CHECK(buffer2[8] == ' ');
    CHECK(buffer2[9] == 'g');
    CHECK(buffer2[10] == 'o');
    CHECK(buffer2[11] == 'o');
    CHECK(buffer2[12] == 'd');
    CHECK(buffer2[13] == ' ');
    CHECK(buffer2[14] == 'y');
    CHECK(buffer2[15] == 'a');
    CHECK(buffer2[16] == 'k');
    CHECK(buffer2[17] == 'o');
    CHECK(buffer2[18] == 'v');
    CHECK(buffer2[19] == ' ');
    CHECK(buffer2[20] == 'i');
    CHECK(buffer2[21] == 's');
    CHECK(buffer2[22] == ' ');
    CHECK(buffer2[23] == 'g');
    CHECK(buffer2[24] == 'o');
    CHECK(buffer2[25] == 'o');
    CHECK(buffer2[26] == 'd');
    CHECK(buffer2[27] == ' ');


    printf(GRN "CHECK(strcmp(buffer, \"yakov\") == 0); good!\n" RESET);

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