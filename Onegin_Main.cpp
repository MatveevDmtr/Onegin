#include <stdio.h>
#include <TXLib.h>
#include <string.h>
#include <stdlib.h>

#include "defines.h"





typedef struct buffer_char
{
    char* Ptr;
    size_t Size;
    unsigned long int Num_lines;
}
type_buf_char;

typedef struct buffer_ptrs
{
    char** Ptr;
    size_t Size;
}
type_buf_ptrs;


int read_file(char* filename, type_buf_char* ptr_tb, type_buf_ptrs* ptr_pb);

char* allocate_text(int num_bytes);

char** allocate_ptrs(int num_ptrs);

int read_text(FILE* file, type_buf_char* ptr_tb);

int create_array_ptr(type_buf_char* ptr_tb, type_buf_ptrs* ptr_pb);

int get_file_size(FILE* file);

int count_lines(type_buf_char* ptr_tb);

bool isletter(char sym);

int test_comparison();

int str_compare(const char* ptr_line1, const char* ptr_line2, bool rev);

int sort_text(type_buf_ptrs* ptr_pb, char* type_sort);

int merge_sort_all(type_buf_ptrs* ptr_pb);

int single_merge(type_buf_ptrs* arr, type_buf_ptrs* temp, char** ptr_start, char** ptr_end);

int Merge(type_buf_ptrs* arr, type_buf_ptrs* temp, char** ptr1, char** ptr2, char** ptr2_end);

//int merge_sort_single(type_buf_ptrs* arr, type_buf_ptrs* temp_arr, char** ptr_begin, char** ptr_end);

//void Merge(type_buf_ptrs* arr, type_buf_ptrs* temp_arr, char** ptr1, char** ptr2, char** ptr_end);

int print_arr_ptrs(type_buf_ptrs* ptr_pb);


int main()
{
    type_buf_char buf_text = {NULL, 0, 0};
    type_buf_ptrs buf_ptrs = {NULL, 0   };

    read_file("composition.txt", &buf_text, &buf_ptrs);

    test_comparison();

    sort_text(&buf_ptrs, "merge");

    print_arr_ptrs(&buf_ptrs);
}



int read_file(char* filename, type_buf_char* ptr_tb, type_buf_ptrs* ptr_pb)   //fread ftell fseek
{
    FILE* text_file = fopen(filename, "rb");

    if(text_file == NULL)
    {
        $r;
        printf("File %s not found\n", filename);
        $d;
        return -1;
    }

    def_and_check(ptr_tb->Size, get_file_size(text_file), NULL);

    printf("Size of file is: %d bytes.\n", ptr_tb->Size);

    def_and_check(ptr_tb->Ptr, allocate_array(char, ptr_tb->Size), NULL);

    printf("Text location: %p\n", ptr_tb->Ptr);

    read_text(text_file, ptr_tb);

    fclose(text_file);

    int num_lines = count_lines(ptr_tb);

    printf("Num lines: %d\n", num_lines);

    def_and_check(ptr_pb->Ptr, allocate_array(char*, (*ptr_tb).Size), NULL);

    create_array_ptr(ptr_tb, ptr_pb);

    //txDump((*ptr_tb).Ptr);

    printf("Symbols 7-8 in buffer: %d %d\n", *((*ptr_tb).Ptr + 7), *((*ptr_tb).Ptr + 8));
    printf("Symbols 16-18 in buffer: %d %d %d\n", *((*ptr_tb).Ptr + 16), *((*ptr_tb).Ptr + 17), *((*ptr_tb).Ptr + 18));
    printf("Size of arr_ptrs: %d\n", (*ptr_pb).Size);


    //merge_sort_all(ptr_pb);

    //print_arr_ptrs(ptr_pb);

    return 0;
}

int create_array_ptr(type_buf_char* ptr_tb, type_buf_ptrs* ptr_pb)
{
    unsigned long int index_line = 0;

    (ptr_pb->Ptr)[index_line] = ptr_tb->Ptr;

    ptr_pb->Size++;

    printf("Line pointer: %d\n", (int*)(ptr_tb->Ptr));

    for (size_t i = 0; i < (*ptr_tb).Size; i++)
    {
        if ((ptr_tb->Ptr)[i] == '\n')
        {
            index_line++;

            (*ptr_pb).Ptr[index_line] = (*ptr_tb).Ptr + i + 1;

            printf("Line pointer: %d\n", (int*)((*ptr_tb).Ptr + i + 1));

            (*ptr_pb).Size++;
        }
    }

    return 1;
}

int read_text(FILE* file, type_buf_char* ptr_tb)
{
    size_t def_and_check(num_read_sym, fread(ptr_tb->Ptr, sizeof(char), ptr_tb->Size, file), 0);

    printf("buffer size: %d\n"
           "fread number of symbols: %d\n", ptr_tb->Size, num_read_sym);

    if (ptr_tb->Size != num_read_sym)
    {
        printf("Program dies from cringe\n");
        return 0;
    }

    return 1;
}

int count_lines(type_buf_char* ptr_tb)
{
    Assert(ptr_tb == NULL);

    size_t num_lines = 0;

    for(size_t i = 0; i < (*ptr_tb).Size; i++)
    {
        if (*(ptr_tb->Ptr + i) == '\n')
        {
            num_lines++;
        }
    }

    num_lines++;

    (*ptr_tb).Num_lines = num_lines;

    return num_lines;
}


/*char* allocate_text(int num_bytes)
{
    char* ptr_buf = (char*)calloc(num_bytes, sizeof(char));

    Assert(ptr_buf == NULL);

    return ptr_buf;
}*/


int get_file_size(FILE* file)
{
    Assert(file == NULL);

    fseek(file, 0, SEEK_END);

    int file_size = ftell(file);

    fseek(file, 0, SEEK_SET);

    return file_size;
}

bool isletter(char sym)
{
    //printf("a %d, z %d, A %d, Z %d, à %d, ÿ %d, À %d, ß %d\n", 'a', 'z', 'A', 'Z', 'à', 'ÿ', 'À', 'ß');

    if (('a' <= sym && sym <= 'z') ||
        ('A' <= sym && sym <= 'Z') ||
        ('à' <= sym && sym <= 'ÿ') ||
        ('À' <= sym && sym <= 'ß'))
    {
        return true;
    }

    return false;
}

int end_of_line(char sym)
{
    if (sym == '\0' || sym == '\n' || sym == '\r')
        return true;

    return false; // return cond ? true : false;
}

int str_compare(const char* ptr_line1, const char* ptr_line2, bool rev) // \n eof \0
{
    Assert(ptr_line1 == NULL);
    Assert(ptr_line2 == NULL);

    while(!end_of_line(*ptr_line1) && !end_of_line(*ptr_line2))
    {
        while (!end_of_line(*ptr_line1) && !isletter(*ptr_line1))
        {
            ptr_line1++;
            //printf("ptr_line1: %d\n", ptr_line1);
        }
        while (!end_of_line(*ptr_line2) && !isletter(*ptr_line2))
        {
            ptr_line2++;
        }

        if (*ptr_line1 != *ptr_line2)
        {
            return *ptr_line1 - *ptr_line2;
        }

        ptr_line1++;
        ptr_line2++;
    }

    if (end_of_line(*ptr_line1))
    {
        return -1;
    }

    if (end_of_line(*ptr_line2))
    {
        return 1;
    }

    return 0;
}

int comparator(const void* line1, const void* line2)
{
    return str_compare(*(const char**)line1, *(const char**)line2, 1);
}

int test_comparison()
{
    char line1[] = "abcDe";
    char line2[] = "abcd";
    int res = str_compare(line1, line2, 1);
    printf("Comparison %s and %s: %d\n", line1, line2, res);
    if (res < 0)
    {
        printf("Comparison %s and %s successful\n", line1, line2);

        return true;
    }
    printf("Comparison failed\n");

    return 0;
}

int sort_text(type_buf_ptrs* ptr_pb, char* type_sort)
{
    if (!strcmp(type_sort, "merge"))
    {
        merge_sort_all(ptr_pb);
    }
    else if(!strcmp(type_sort, "qsort"))
    {
        printf("Start qsort\n");

        qsort(ptr_pb->Ptr, ptr_pb->Size, sizeof(char*), comparator);
    }
    else
    {
        $r;
        printf("Undefined type of sort\n");
        $d;
    }
}

int merge_sort_all(type_buf_ptrs* ptr_pb)
{
    type_buf_ptrs temp_arr = {NULL, 0};

    def_and_check(temp_arr.Ptr, allocate_array(char*, ptr_pb->Size), NULL);

    for (size_t i = 0; i < ptr_pb->Size; i++)
    {
        temp_arr.Ptr[i] = (ptr_pb->Ptr)[i];
    }

    single_merge(ptr_pb, &temp_arr, (*ptr_pb).Ptr, (*ptr_pb).Ptr + (*ptr_pb).Size);
}

int print_arr_ptrs(type_buf_ptrs* ptr_pb)
{
    printf("Print sorted list: \n");
    for (size_t i = 0; i < (*ptr_pb).Size; i++)
    {
        printf("line: %c\t", *((*ptr_pb).Ptr[i]));
    }
    printf("\n");
}

int single_merge(type_buf_ptrs* arr, type_buf_ptrs* temp, char** ptr_start, char** ptr_end)
{
    char** ptr_mid = ptr_start + (ptr_end - ptr_start) / 2;

    if(ptr_end - ptr_start <= 1)
    {
        return 1;
    }

    single_merge(arr, temp, ptr_start, ptr_mid);
    single_merge(arr, temp, ptr_mid, ptr_end);

    Merge(arr, temp, ptr_start, ptr_mid, ptr_end);
}

int Merge(type_buf_ptrs* arr, type_buf_ptrs* temp, char** ptr1, char** ptr2, char** ptr2_end)
{
    char** ptr1_end = ptr2;

    int i = ptr1 - (arr->Ptr);
    while (ptr1 < ptr1_end && ptr2 < ptr2_end)
    {
        if (str_compare(*ptr1, *ptr2, 1) < 0)
        {
            (temp->Ptr)[i] = *ptr1;
            ptr1++;
        }
        else
        {
            (temp->Ptr)[i] = *ptr2;
            ptr2++;
        }
        i++;
    }

    while(ptr1 < ptr1_end)
    {
        (temp->Ptr)[i] = *ptr1;
        ptr1++;
        i++;
    }

    while(ptr2 < ptr2_end)
    {
        (temp->Ptr)[i] = *ptr2;
        ptr2++;
        i++;
    }

    for (size_t i_elem = 0; i_elem < (arr->Size); i_elem++)
    {
        (arr->Ptr)[i_elem] = (temp->Ptr)[i_elem];
    }
}
