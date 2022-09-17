#include "onegin.h"

int write_file(char* filename, type_buf_char* ptr_text_buf, type_buf_ptrs* ptr_buf_adrs)
{
    FILE* w_file = open_Wfile(filename);

    printf("Wfile opened\n");

    putting_buf_text_to_file(ptr_buf_adrs, w_file);

    fclose(w_file);
}

int putting_buf_text_to_file(type_buf_ptrs* ptr_buf_adrs, FILE* w_file)
{
    for (size_t i = 0; i < ptr_buf_adrs->Size; i++)
    {
        printf("try to print %d line\n", i);
        put_line(w_file, (ptr_buf_adrs->Ptr)[i]);
    }
}

FILE* open_Wfile(char* filename)
{
    FILE* w_file = fopen(filename, "wb");

    if(w_file == NULL)
    {
        $r;
        printf("Opening file to write %s failed\n", filename);
        $d;
        return NULL;
    }

    return w_file;
}

size_t len_line(char* ptr_line)
{
    size_t num_sym = 0;

    while(*ptr_line != EOF  &&
          *ptr_line != '\r' &&
          *ptr_line != '\n' &&
          *ptr_line != '\0')
    {
        num_sym += 1;

        ptr_line++;
    }
    *ptr_line = '\n';
    num_sym += 1;

    return num_sym;
}

int put_line(FILE* w_file, char* ptr_line)
{
    size_t length_line = len_line(ptr_line);
    size_t num_written_sym = fwrite(ptr_line, sizeof(char), length_line, w_file);

    if (num_written_sym != length_line)
    {
        $r;
        printf("Error in writing to file\n");
        Assert(num_written_sym != length_line);
        $d;

        return -1;
    }

    return 0;
}
