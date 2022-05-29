#include "myFILE.hpp"

myFILE::myFILE(/* args */){
    this->file->permition = UNSET;
    this->file->file_num = 0;
    this->file->current_offset = 0;
    this->file->used_size = 0;
    this->file->size = 0;
    this->file->first_block = 0;
    strcpy(this->file->name, "");
    this->file->type = FILE_TYPE_UNSET;
};
myFILE::~myFILE(){

};

myFILE *myfopen(const char *pathname, const char *mode)
{
    myFILE* myfile_ptr = new myFILE();
    
    // myFILE *myFILE = new myFILE();
    // myFILE->myFILE_mode = UNSET;
    // myFILE->myFiles_open.push_back(pathname);
    // return myFILE;
}

int myprint(char *str, ...)
{
    va_list vl;
    int i = 0, j = 0;
    char buff[100] = {0}, tmp[20];
    char *str_arg;

    va_start(vl, str);
    while (str && str[i])
    {
        if (str[i] == '%')
        {
            i++;
            switch (str[i])
            {
            /* Convert char */
            case 'c':
            {
                buff[j] = (char)va_arg(vl, int);
                j++;
                break;
            }
            /* Convert decimal */
            case 'd':
            {
                _itoa(va_arg(vl, int), tmp, 10);
                strcpy(&buff[j], tmp);
                j += strlen(tmp);
                break;
            }
            case 'f':
            {
                _itoa(va_arg(vl, double), tmp, 10);
                strcpy(&buff[j], tmp);
                j += strlen(tmp);
                break;
            }
            /* Convert hex */
            case 'x':
            {
                _itoa(va_arg(vl, int), tmp, 16);
                strcpy(&buff[j], tmp);
                j += strlen(tmp);
                break;
            }
            /* Convert octal */
            case 'o':
            {
                _itoa(va_arg(vl, int), tmp, 8);
                strcpy(&buff[j], tmp);
                j += strlen(tmp);
                break;
            }
            /* copy string */
            case 's':
            {
                str_arg = va_arg(vl, char *);
                strcpy(&buff[j], str_arg);
                j += strlen(str_arg);
                break;
            }
            }
        }
        else
        {
            buff[j] = str[i];
            j++;
        }
        i++;
    }
    fwrite(buff, j, 1, stdout);
    va_end(vl);
    return j;
}

char *_itoa(int i, char *strout, int base)
{
    char *str = strout;
    int digit, sign = 0;
    if (i < 0)
    {
        sign = 1;
        i *= -1;
    }
    while (i)
    {
        digit = i % base;
        *str = (digit > 9) ? ('A' + digit - 10) : '0' + digit;
        i = i / base;
        str++;
    }
    if (sign)
    {
        *str++ = '-';
    }
    *str = '\0';
    _strrev(strout);
    return strout;
}

char *_strrev(char *str)
{
    int i;
    int len = 0;
    char c;
    if (!str)
        return NULL;
    while (str[len] != '\0')
    {
        len++;
    }
    for (i = 0; i < (len / 2); i++)
    {
        c = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = c;
    }
    return str;
}

int myscanf(char *str, ...)
{
    va_list vl;
    int i = 0, j = 0, ret = 0;
    char buff[100] = {0}, c;
    char *out_loc;
    while (c != '\n')
    {
        if (fread(&c, 1, 1, stdin))
        {
            buff[i] = c;
            i++;
        }
    }
    va_start(vl, str);
    i = 0;
    while (str && str[i])
    {
        if (str[i] == '%')
        {
            i++;
            switch (str[i])
            {
            case 'c':
            {
                *(char *)va_arg(vl, char *) = buff[j];
                j++;
                ret++;
                break;
            }
            case 'd':
            {
                *(int *)va_arg(vl, int *) =
                    strtol(&buff[j], &out_loc, 10);
                j += out_loc - &buff[j];
                ret++;
                break;
            }
            case 'f':
            {
                *(float *)va_arg(vl, float *) =
                    strtof(&buff[j], &out_loc);
                j += out_loc - &buff[j];
                ret++;
                break;
            }
            case 'x':
            {
                *(int *)va_arg(vl, int *) =
                    strtol(&buff[j], &out_loc, 16);
                j += out_loc - &buff[j];
                ret++;
                break;
            }
            case 'o':
            {
                *(int *)va_arg(vl, int *) =
                    strtol(&buff[j], &out_loc, 8);
                j += out_loc - &buff[j];
                ret++;
                break;
            }
            case 's':
            {
                out_loc = (char *)va_arg(vl, char *);
                strcpy(out_loc, &buff[j]);
                j += strlen(&buff[j]);
                ret++;
                break;
            }
            }
        }
        else
        {
            buff[j] = str[i];
            j++;
        }
        i++;
    }
    va_end(vl);
    return ret;
}