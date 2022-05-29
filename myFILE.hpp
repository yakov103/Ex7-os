#ifndef MYFILE_HPP
#define MYFILE_HPP
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <vector>
#include <string>
#include "fs.hpp"
// https://www.equestionanswers.com/c/c-printf-scanf-working-principle.php

using namespace std;

// enum Permission
// {
//     PERMISSION_READ,      // 0
//     PERMISSION_WRITE,     // 1
//     PERMISSION_EXECUTE,   // 2
//     PERMISSION_UNSET,     // 3
//     PERMISSION_READ_WRITE // 4
// };

class simple_file
{
public:
    enum Permission permition;
    int file_num;
    int current_offset;
    int used_size;
    int size;
    int first_block;
    char name[8];
    enum FileType type;
    simple_file() = default;
    simple_file(int file_num, int current_offset, int used_size, int size, int first_block, char name[8], enum FileType type, enum myFILEPERMITION permition)
    {
        this->file_num = file_num;
        this->current_offset = current_offset;
        this->used_size = used_size;
        this->size = size;
        this->first_block = first_block;
        strcpy(this->name, name);
        this->type = type;
        this->permition = permition;
    }
};

class myFILE
{
    // constructor
public:
    static vector<string> myFILEs_open;
    static vector<simple_file *> myFILEs;
    simple_file *file;
    char file_buffer[5120];
    myFILE();
    ~myFILE();
    myFILE(simple_file *file)
    {
        myFILEs.push_back(file);
        // myFILEs.push_back(simple_file(file_num, curr_offset, used_size, size, first_block, name, type, permition));
        myFILEs_open.push_back(file->name);
    }
};

myFILE *myfopen(const char *pathname, const char *mode);
int myfclose(myFILE *stream);
size_t myfread(void *ptr, size_t size, size_t nmemb, myFILE *stream);
size_t myfwrite(const void *ptr, size_t size, size_t nmemb, myFILE *stream);
int myfseek(myFILE *stream, long offset, int whence);
int myfscanf(myFILE *stream, const char *format, ...);
int myfprintf(myFILE *stream, const char *format, ...);

// myprintf();
char *_strrev(char *str);
char *_itoa(int i, char *strout, int base);
int myprint(char *str, ...);
// myprintf()

// myscanf();
int myscanf(char *str, ...);
// myscanf();

// int main(int argc, char *argv[])
// {
//   char c;
//   int i;
//   int h;
//   int o;
//   char str_buff[20];
//   int ret = 0;
//   printf("Enter char int hex oct string\n");
//   ret = scan("%c %d %x %o %s", &c, &i, &h, &o, str_buff);
//   printf("C = %c, I = %d, H = %d, O = %d, S = %s returns %d", c, i, h, o, str_buff, ret);
//   return 0;
// }

// int main(int argc, char *argv[])
// {
//     int ret;
//     std::string str = "hello world";
//     std::string param = "%c %d %o %x %s\n";
//     ret = myprint((char *) param.c_str(), 'A', 10, 100, 1000, str.c_str());
//     printf("printf returns %d bytes\n", ret);
//     return 0;
// }

#endif