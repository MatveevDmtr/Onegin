#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#define TX_COMPILED

#include <stdio.h>
#include <TXLib.h>
#include <string.h>
#include <stdlib.h>

#include "defines.h"

typedef struct buffer_char
{
    char* Ptr; //  ptr_text
    size_t Size;
    unsigned long int Num_lines;
}
type_buf_char;

typedef struct buffer_ptrs
{
    char** Ptr;   //  ptr_buf_adr
    size_t Size;
}
type_buf_ptrs;


int read_file(char* filename,
              type_buf_char* ptr_text_buf,
              type_buf_ptrs* ptr_buf_adrs,
              type_buf_ptrs* ptr_const_buf_ptrs);

char* allocate_text(int num_bytes);

char** allocate_ptrs(int num_ptrs);

int text_to_buffer(FILE* file, type_buf_char* ptr_text_buf);

FILE* open_file_rmode(char* filename);

int make_pointers_to_lines(type_buf_char* ptr_text_buf,
                           type_buf_ptrs* ptr_buf_adrs,
                           type_buf_ptrs* ptr_const_buf_adrs);

int create_array_ptr(type_buf_char* ptr_text_buf, type_buf_ptrs* ptr_buf_adrs);

int get_file_size(FILE* file);

int count_lines(type_buf_char* ptr_text_buf);

bool isletter(char sym);

int test_comparison();

int str_compare(const char* ptr_line1, const char* ptr_line2);

int str_compare_reverse(const char* ptr_line1, const char* ptr_line2);

int sort_text(type_buf_ptrs* ptr_buf_adrs,
              char* type_sort,
              int (*comparator)(const void* line1, const void* line2));

int merge_sort_all(type_buf_ptrs* ptr_buf_adrs,
                   int (*comparator)(const void* line1, const void* line2));

int single_merge(type_buf_ptrs* arr,
                 type_buf_ptrs* temp,
                 char** ptr_start,
                 char** ptr_end,
                 int (*comparator)(const void* line1, const void* line2));

int Merge(type_buf_ptrs* arr,
          type_buf_ptrs* temp,
          char** ptr1,
          char** ptr2,
          char** ptr2_end,
          int (*comparator)(const void* line1, const void* line2));

//int merge_sort_single(type_buf_ptrs* arr, type_buf_ptrs* temp_arr, char** ptr_begin, char** ptr_end);

//void Merge(type_buf_ptrs* arr, type_buf_ptrs* temp_arr, char** ptr1, char** ptr2, char** ptr_end);

int print_arr_ptrs(type_buf_ptrs* ptr_buf_adrs);

int sort_and_write(char* filename,
               type_buf_char* ptr_text_buf,
               type_buf_ptrs* ptr_buf_adrs,
               type_buf_ptrs* ptr_const_buf_adrs);

FILE* open_Wfile(char* filename);

int putting_buf_text_to_file(type_buf_ptrs* ptr_buf_adrs, FILE* w_file);

int end_of_line(char sym);

int put_line(FILE* w_file, char* ptr_line);

int is_line_empty(char* ptr_line);

int comparator_straight(const void* line1, const void* line2);

int comparator_reverse(const void* line1, const void* line2);

int print_help(char* filename);


enum TYPE_SORT
{
    MERGE = 0,
    QSORT = 1
};
//char sep_line[] = "Encyclopedia of Russian Life, (C) A.S.Pushkin feat. D.A.Matiushin\n";


#endif // ONEGIN_H_INCLUDED
