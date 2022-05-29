// #pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// https://www.equestionanswers.com/c/c-printf-scanf-working-principle.php

enum myFILEPERMITION
{
    READ = 1,
    WRITE = 2,
    READ_WRITE = 3,
    APPEND = 4,
    EXECUTE = 5
};

class myFILE
{
private:
    /* data */
public:
    myFILE(/* args */);
    ~myFILE();
};

myFILE::myFILE(/* args */)
{
}

myFILE::~myFILE()
{
}

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