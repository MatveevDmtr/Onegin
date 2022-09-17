#include "onegin.h"
#include "defines.h"

int read_file(char* filename, type_buf_char* ptr_text_buf, type_buf_ptrs* ptr_buf_adrs)   //fread ftell fseek
{
    FILE* text_file = open_file_rmode(filename);

    //def_and_check(ptr_text_buf->Size, get_file_size(text_file), NULL);

    ptr_text_buf->Size = get_file_size(text_file) + 1;

    Assert(ptr_text_buf->Size == NULL);

    printf("Size of file is: %d bytes.\n", ptr_text_buf->Size);

    //def_and_check(ptr_text_buf->Ptr, allocate_array(char, ptr_text_buf->Size), NULL);

    ptr_text_buf->Ptr = (char*) calloc(ptr_text_buf->Size, sizeof(char));

    Assert(ptr_text_buf->Ptr == NULL);

    text_to_buffer(text_file, ptr_text_buf); //r_file?      // rename

    //print_arr_ptrs(ptr_buf_adrs);

    fclose(text_file);

    make_pointers_to_lines(ptr_text_buf, ptr_buf_adrs);

    //txDump((*ptr_text_buf).Ptr);

    printf("Symbols 7-8 in buffer: %d %d\n", *((*ptr_text_buf).Ptr + 7), *((*ptr_text_buf).Ptr + 8));
    printf("Symbols 16-18 in buffer: %d %d %d\n", *((*ptr_text_buf).Ptr + 16), *((*ptr_text_buf).Ptr + 17), *((*ptr_text_buf).Ptr + 18));
    printf("Size of arr_ptrs: %d\n", (*ptr_buf_adrs).Size);

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

// rename, transfer to read_file
int make_pointers_to_lines(type_buf_char* ptr_text_buf, type_buf_ptrs* ptr_buf_adrs)
{
    ptr_text_buf->Num_lines = count_lines(ptr_text_buf);

    printf("Num lines: %d\n", ptr_text_buf->Num_lines);

    ptr_buf_adrs->Ptr = (char**) calloc(ptr_buf_adrs->Size, sizeof(char*));

    create_array_ptr(ptr_text_buf, ptr_buf_adrs);

}

int text_to_buffer(FILE* file, type_buf_char* ptr_text_buf)
{
    size_t num_read_sym = fread(ptr_text_buf->Ptr, sizeof(char), ptr_text_buf->Size, file);



    Assert(num_read_sym == 0);

    printf("buffer size: %d\n"
           "fread number of symbols: %d\n", ptr_text_buf->Size, num_read_sym);

    if (ptr_text_buf->Size - 1!= num_read_sym)
    {
        printf("Program dies from cringe\n");
        return 0;
    }

    return 1;
}

int create_array_ptr(type_buf_char* ptr_text_buf, type_buf_ptrs* ptr_buf_adrs) // replace
{
    unsigned long int index_line = 0;

    char* ptr_prev_line = ptr_text_buf->Ptr;

    //(ptr_buf_adrs->Ptr)[index_line] = ptr_text_buf->Ptr;
    //printf("start_ptr_size: %d", ptr_buf_adrs->Size);

    //printf("Line pointer: %d\n", (int*)(ptr_text_buf->Ptr));

    for (size_t i = 0; i < ptr_text_buf->Size; i++)
    {
        printf("sym: %c\n", (ptr_text_buf->Ptr)[i]);
        if (end_of_line((ptr_text_buf->Ptr)[i]))
        {
            if (!is_line_empty(ptr_prev_line))
            {
                ptr_buf_adrs->Size++;

                (ptr_buf_adrs->Ptr)[index_line] = ptr_prev_line;

                index_line++;

                printf("Line pointer: %d\n", (int*)ptr_prev_line);
            }

            ptr_prev_line = (ptr_text_buf->Ptr) + i + 1;
        }
    }

    return 1;
}

int is_line_empty(char* ptr_line)
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
        }   // empty lines
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
    return (sym == '\0' ||
            sym == '\n' ||
            sym == '\r') ?
            true : false;
    // return cond ? true : false;
}

