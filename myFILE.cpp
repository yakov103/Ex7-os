#include "mystdio.h"
#include <stdlib.h>

vector<string> myFILEs_open;
vector<simple_file *> myFILEs;

myFILE::myFILE(/* args */)
{
    this->file = new simple_file();
    this->file->permition = PERMISSION_UNSET;
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

    myFILE *myfile_ptr = new myFILE();
    if (mode[0] == 'r' && strlen(mode) == 1)
    {
        int file_number = myopen(pathname, PERMISSION_READ);
        if (file_number == -1)
        {
            return NULL;
        }
        myfile_ptr->file->permition = PERMISSION_READ;
        myfile_ptr->file->file_num = file_number;
        myfile_ptr->file->current_offset = 0;
        myfile_ptr->file->used_size = inodes[file_number].used_size;
        myfile_ptr->file->size = inodes[file_number].size;
        myfile_ptr->file->first_block = inodes[file_number].first_block;
        strcpy(myfile_ptr->file->name, inodes[file_number].name);
        myfile_ptr->file->type = inodes[file_number].type;
        myFILEs_open.push_back(inodes[file_number].name);
        // myread(myfile_ptr->file->file_num, (void *)myfile_ptr->file_buffer, myfile_ptr->file->used_size);
        return myfile_ptr;
    }
    else if (mode[0] == 'w' && strlen(mode) == 1)
    {
        int file_number = myopen(pathname, PERMISSION_WRITE);
        if (file_number == -1)
        {
            return NULL;
        }
        myfile_ptr->file->permition = PERMISSION_WRITE;
        myfile_ptr->file->file_num = file_number;
        myfile_ptr->file->current_offset = 0;
        myfile_ptr->file->used_size = inodes[file_number].used_size;
        myfile_ptr->file->size = inodes[file_number].size;
        myfile_ptr->file->first_block = inodes[file_number].first_block;
        strcpy(myfile_ptr->file->name, inodes[file_number].name);
        myfile_ptr->file->type = inodes[file_number].type;
        myFILEs_open.push_back(inodes[file_number].name);
        myread(myfile_ptr->file->file_num, (void *)myfile_ptr->file_buffer, myfile_ptr->file->used_size);
    }
    else if (mode[0] == 'a' && strlen(mode) == 1)
    {
        int file_number = myopen(pathname, PERMISSION_APPEND);
        if (file_number == -1)
        {
            return NULL;
        }
        myfile_ptr->file->permition = PERMISSION_APPEND;
        myfile_ptr->file->current_offset = myfile_ptr->file->used_size;
        myfile_ptr->file->file_num = file_number;
        myfile_ptr->file->used_size = inodes[file_number].used_size;
        myfile_ptr->file->size = inodes[file_number].size;
        myfile_ptr->file->first_block = inodes[file_number].first_block;
        strcpy(myfile_ptr->file->name, inodes[file_number].name);
        myfile_ptr->file->type = inodes[file_number].type;
        myFILEs_open.push_back(inodes[file_number].name);
        myread(myfile_ptr->file->file_num, (void *)myfile_ptr->file_buffer, myfile_ptr->file->used_size);
    }
    else if (mode[0] == 'r' && mode[1] == '+')
    {
        int file_number = myopen(pathname, PERMISSION_READ_WRITE);
        if (file_number == -1)
        {
            return NULL;
        }
        myfile_ptr->file->permition = PERMISSION_READ_WRITE;
        myfile_ptr->file->file_num = file_number;
        myfile_ptr->file->current_offset = 0;
        myfile_ptr->file->used_size = inodes[file_number].used_size;
        myfile_ptr->file->size = inodes[file_number].size;
        myfile_ptr->file->first_block = inodes[file_number].first_block;
        strcpy(myfile_ptr->file->name, inodes[file_number].name);
        myfile_ptr->file->type = inodes[file_number].type;
        myFILEs_open.push_back(inodes[file_number].name);
        myread(myfile_ptr->file->file_num, (void *)myfile_ptr->file_buffer, myfile_ptr->file->used_size);
    }
    else
    {
        myfile_ptr->file->permition = PERMISSION_UNSET;
    }
    return myfile_ptr;
}

int myfclose(myFILE *stream)
{
    int file_number = stream->file->file_num;
    myFILEs_open.erase(std::remove(myFILEs_open.begin(), myFILEs_open.end(), inodes[file_number].name), myFILEs_open.end());
    myclose(file_number);
    return file_number;
}

size_t myfread(void *ptr, size_t size, size_t nmemb, myFILE *stream)
{
    // check if the file is opened in write mode
    if (stream->file->permition != PERMISSION_READ && stream->file->permition != PERMISSION_READ_WRITE && stream->file->permition != PERMISSION_APPEND)
    {
        return 0;
    }

    // check if the file is in filesopen
    if (std::find(myFILEs_open.begin(), myFILEs_open.end(), inodes[stream->file->file_num].name) == myFILEs_open.end())
    {
        return 0;
    }

    int current_offset = inodes[stream->file->file_num].current_offset;
    int used_size = inodes[stream->file->file_num].used_size;
    int size_to_read = size * nmemb;
    int size_to_read_from_buffer = 0;
    if (current_offset + size_to_read > used_size)
    {
        size_to_read_from_buffer = used_size - current_offset;
    }
    else
    {
        size_to_read_from_buffer = size_to_read;
    }
    myread(stream->file->file_num, ptr, size_to_read_from_buffer);
    // memcpy(ptr, stream->file_buffer + current_offset, size_to_read_from_buffer);
    stream->file->current_offset += size_to_read_from_buffer;
    return size_to_read_from_buffer;
}

size_t myfwrite(const void *ptr, size_t size, size_t nmemb, myFILE *stream)
{
    // check if the file is opened in write mode
    if (stream->file->permition != PERMISSION_WRITE && stream->file->permition != PERMISSION_READ_WRITE && stream->file->permition != PERMISSION_APPEND)
    {
        return 0;
    }

    // check if the file is in filesopen
    if (std::find(myFILEs_open.begin(), myFILEs_open.end(), inodes[stream->file->file_num].name) == myFILEs_open.end())
    {
        return 0;
    }

    // int current_offset = inodes[stream->file->file_num].current_offset;
    // int used_size = inodes[stream->file->file_num].used_size;
    int size_to_write = size * nmemb;
    int size_to_write_from_buffer = 0;
    size_to_write_from_buffer = size_to_write;

    // use mywrite to write to the file
    mywrite(stream->file->file_num, (void *)ptr, size_to_write_from_buffer);
    // break myFILE.cpp:164
    // memcpy(stream->file_buffer + current_offset, ptr, size_to_write_from_buffer);
    // stream->file->current_offset += size_to_write_from_buffer;
    return size_to_write_from_buffer;
}

int myfseek(myFILE *stream, long offset, int whence)
{

    // check if the file is opened in write mode
    if (stream->file->permition != PERMISSION_READ && stream->file->permition != PERMISSION_READ_WRITE && stream->file->permition != PERMISSION_APPEND)
    {
        return -1;
    }

    // check if the file is in filesopen
    if (std::find(myFILEs_open.begin(), myFILEs_open.end(), inodes[stream->file->file_num].name) == myFILEs_open.end())
    {
        return -1;
    }

    int current_offset = stream->file->current_offset;
    int used_size = stream->file->used_size;
    int size_to_seek = offset;
    int size_to_seek_from_buffer = 0;
    if (whence == SEEK_SET)
    {
        if (size_to_seek > used_size)
        {
            return -1;
        }
        else
        {
            size_to_seek_from_buffer = size_to_seek;
        }
    }
    else if (whence == SEEK_CUR)
    {
        if (current_offset + size_to_seek > used_size)
        {
            return -1;
        }
        else
        {
            size_to_seek_from_buffer = current_offset + size_to_seek;
        }
    }
    else if (whence == SEEK_END)
    {
        if (used_size + size_to_seek > used_size)
        {
            return -1;
        }
        else
        {
            size_to_seek_from_buffer = used_size + size_to_seek;
        }
    }
    else
    {
        return -1;
    }
    stream->file->current_offset = size_to_seek_from_buffer;
    return 0;
}

int myfscanf(myFILE *stream, const char *format, ...)
{

    // check if the file is opened in write mode
    if (stream->file->permition != PERMISSION_READ && stream->file->permition != PERMISSION_READ_WRITE && stream->file->permition != PERMISSION_APPEND)
    {
        return -1;
    }

    // check if the file is in filesopen
    if (std::find(myFILEs_open.begin(), myFILEs_open.end(), inodes[stream->file->file_num].name) == myFILEs_open.end())
    {
        return -1;
    }
    // need to be like myfprintf but the opposite

    // so first we start with myread
    int current_offset = 0;
    int used_size = inodes[stream->file->file_num].used_size;
    int size_to_read = used_size - current_offset;
    char *buffer = (char *)malloc(size_to_read);
    // break myFILE.cpp:273
    myread(stream->file->file_num, buffer, size_to_read);

    // now we start to check which format we have
    char tmp[20];
    int i = 0, j = 0;
    va_list vl;
    va_start(vl, format);
    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'd')
            {
                bzero(tmp, 20);
                int *p = va_arg(vl, int *);
                int x = 0;
                while (buffer[j] != ' ' && buffer[j] != '\n' && buffer[j] != '\0')
                {
                    tmp[x] = buffer[j];
                    j++;
                    x++;
                }
                tmp[x] = '\0';
                // break myFILE.cpp:301
                //
                *p = atoi(tmp);
                j++;
            }
            else if (format[i] == 's')
            {
                bzero(tmp, 20);
                char *p = va_arg(vl, char *);
                while (buffer[j] != ' ' && buffer[j] != '\n' && buffer[j] != '\0')
                {
                    tmp[j] = buffer[j];
                    j++;
                }
                tmp[j] = '\0';
                strcpy(p, tmp);
                j++;
            }
            else if (format[i] == 'c')
            {
                bzero(tmp, 20);
                char *p = va_arg(vl, char *);
                int x = 0;
                while (buffer[j] != ' ' && buffer[j] != '\n' && buffer[j] != '\0')
                {
                    tmp[j] = buffer[j];
                    j++;
                    x++;
                }
                tmp[x] = '\0';
                *p = tmp[0];
                j++;
            }
            else if (format[i] == 'f')
            {
                bzero(tmp, 20);
                float *p = va_arg(vl, float *);
                int x = 0;
                while (buffer[j] != ' ' && buffer[j] != '\n' && buffer[j] != '\0')
                {
                    tmp[x] = buffer[j];
                    j++;
                    x++;
                }
                tmp[x] = '\0';
                *p = atof(tmp);
                j++;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            i++;
        }
    }

    return 0;
}

int mystrlen(char *str)
{

    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

int myfprintf(myFILE *stream, const char *format, ...)
{
    // check if the file is opened in write mode
    if (stream->file->permition != PERMISSION_WRITE && stream->file->permition != PERMISSION_READ_WRITE && stream->file->permition != PERMISSION_APPEND)
    {
        return -1;
    }

    // check if the file is in filesopen
    if (std::find(myFILEs_open.begin(), myFILEs_open.end(), inodes[stream->file->file_num].name) == myFILEs_open.end())
    {
        return -1;
    }
    char buff[100] = {0}, tmp[20];
    int i = 0, j = 0;
    va_list vl;
    va_start(vl, format);
    while (format && format[i])
    {
        if (format[i] == '%')
        {
            i++;
            switch (format[i])
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
            /* copy string */
            case 's':
            {
                strcpy(&buff[j], va_arg(vl, char *));
                break;
            }
            }
        }
        else
        {
            buff[j] = format[i];
            j++;
        }
        i++;
    }
    size_t size_to_write = mystrlen(buff);
    // break myFILE.cpp:357
    mywrite(stream->file->file_num, buff, size_to_write);
    va_end(vl);

    return mystrlen(buff);
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
