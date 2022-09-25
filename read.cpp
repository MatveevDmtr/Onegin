#include <sys\stat.h>

#include "onegin.h"
#include "defines.h"

int read_file(char* filename,
              type_buf_char* ptr_text_buf,
              type_buf_structs* ptr_arr_structs,
              type_buf_ptrs* ptr_arr_adrs)
{
    FILE* text_file = open_file_rmode(filename);

    ptr_text_buf->Size = safe_def_int(get_file_size(text_file) + 1, NULL + 1);

    printf("Size of file is: %d bytes.\n", ptr_text_buf->Size);

    ptr_text_buf->Ptr = allocate_array(char, ptr_text_buf->Size);

    text_to_buffer(text_file, ptr_text_buf);

    fclose(text_file);

    make_pointers_to_lines(ptr_text_buf,
                           ptr_arr_structs,
                           ptr_arr_adrs);

    printf("Symbols 7-8 in buffer: %d %d\n", *((*ptr_text_buf).Ptr + 7), *((*ptr_text_buf).Ptr + 8));
    printf("Symbols 16-18 in buffer: %d %d %d\n", *((*ptr_text_buf).Ptr + 16), *((*ptr_text_buf).Ptr + 17), *((*ptr_text_buf).Ptr + 18));
    printf("Size of arr_ptrs: %d\n", (*ptr_arr_structs).Size);

    return 0;
}

FILE* open_file_rmode(char* filename)
{
    FILE* r_file = fopen(filename, "rb");

    if(r_file == NULL)
    {
        $r;
        printf("File %s not found\n", filename);
        $d;
        return NULL;
    }

    return r_file;
}

int make_pointers_to_lines(type_buf_char* ptr_text_buf,
                           type_buf_structs* ptr_arr_structs,
                           type_buf_ptrs* ptr_arr_adrs)
{
    ptr_text_buf->Num_lines = count_lines(ptr_text_buf);

    printf("Num lines: %d\n", ptr_text_buf->Num_lines);

    ptr_arr_structs      ->Ptr = allocate_array(type_prop_line , ptr_text_buf->Num_lines);
    ptr_arr_adrs         ->Ptr = allocate_array(type_prop_line*, ptr_text_buf->Num_lines);

    ptr_arr_structs->Size = ptr_text_buf->Num_lines;
    ptr_arr_adrs   ->Size = ptr_text_buf->Num_lines;

    create_array_ptr(ptr_text_buf, ptr_arr_structs, ptr_arr_adrs);
}

int text_to_buffer(FILE* file, type_buf_char* ptr_text_buf)
{
    size_t num_read_sym = fread(ptr_text_buf->Ptr, sizeof(char), ptr_text_buf->Size, file);
    // ferror
    Assert(num_read_sym == 0);

    printf("buffer size: %d\n"
           "fread number of symbols: %d\n", ptr_text_buf->Size, num_read_sym);

    if (ptr_text_buf->Size - 1 != num_read_sym)
    {
        printf("Program dies from cringe encoding\n");
        return 0;
    }

    return 1;
}

int create_array_ptr(type_buf_char*    ptr_text_buf,
                     type_buf_structs* ptr_arr_structs,
                     type_buf_ptrs* ptr_arr_adrs)
{
    unsigned long int index_line = 0;

    char* ptr_prev_line = ptr_text_buf->Ptr;

    for (size_t i = 0; i < ptr_text_buf->Size; i++)
    {
        printf("sym: %c\n", (ptr_text_buf->Ptr)[i]);
        if (end_of_line((ptr_text_buf->Ptr)[i]))
        {
            if (!is_line_empty(ptr_prev_line))
            {
                (ptr_arr_structs->Ptr)[index_line] = {ptr_prev_line,
                                                     (ptr_text_buf->Ptr) + i - ptr_prev_line};

                (ptr_arr_adrs->Ptr)[index_line] = (ptr_arr_structs->Ptr) + index_line;

                printf("Len line while creating struct array: %d\n", (ptr_text_buf->Ptr) + i - ptr_prev_line);

                index_line++;

                printf("Line pointer: %d\n", (int*)ptr_prev_line);
            }

            ptr_prev_line = (ptr_text_buf->Ptr) + i + 1;
        }
    }

    printf("Len first line: %d", (ptr_arr_structs->Ptr)[0].Loc);

    return 1;
}

static int is_line_empty(char* ptr_line)
{
    while (!end_of_line(*ptr_line))
    {
        if (isletter(*ptr_line))
        {
            return 0;
        }
        ptr_line++;
    }
    return 1;
}

int count_lines(type_buf_char* ptr_text_buf)
{
    Assert(ptr_text_buf == NULL);

    size_t num_lines = 0;

    char* ptr_prev_line = ptr_text_buf->Ptr;

    for(size_t i = 0; i < ptr_text_buf->Size; i++)
    {
        if (*(ptr_text_buf->Ptr + i) == '\n')
        {
            if (!is_line_empty(ptr_prev_line))
            {
                num_lines++;
            }
            ptr_prev_line = ptr_text_buf->Ptr + i + 1;
        }
    }

    if (!is_line_empty(ptr_prev_line))
    {
        num_lines++;
    }

    ptr_text_buf->Num_lines = num_lines;

    printf("Num lines: ", num_lines);

    return num_lines;
}

int get_file_size(FILE* file)
{
    Assert(file == NULL);

    struct stat buf;

    int errcode = fstat(fileno(file), &buf);

    Assert(errcode != NULL);

    printf("File size = %d\n", buf.st_size);

    return buf.st_size;
}

bool isletter(char sym)
{
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
    return (sym == '\0' ||
            sym == '\n' ||
            sym == '\r') ?
            true : false;
}

