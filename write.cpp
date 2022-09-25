#include "onegin.h"

int putting_buf_text_to_file(type_buf_ptrs* ptr_arr_adrs, FILE* w_file)
{
    for (size_t i = 0; i < ptr_arr_adrs->Size; i++)
    {
        printf("try to print %d line\n", i);
        put_line(w_file, (ptr_arr_adrs->Ptr)[i]);
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

int put_line(FILE* w_file, type_prop_line* ptr_struct_line)
{
    size_t num_written_sym = fwrite(ptr_struct_line->Loc, sizeof(char), ptr_struct_line->Len, w_file);

    fputc('\n', w_file);

    if (num_written_sym != ptr_struct_line->Len)
    {
        $r;
        printf("Error in writing to file\n");
        Assert(num_written_sym != ptr_struct_line->Len);
        $d;

        return -1;
    }

    return 0;
}


int put_buffer(FILE* w_file, type_buf_structs* ptr_arr_structs)
{
    printf("Size of arr_structs: %d", ptr_arr_structs->Size);

    for (size_t i = 0; i < ptr_arr_structs->Size; i++)
    {
        printf("try to print %d line\n", i);
        printf("ptr: %d, size: %d\n", (ptr_arr_structs->Ptr)[i].Loc, (ptr_arr_structs->Ptr)[i].Len);

        size_t num_written_sym = fwrite((ptr_arr_structs->Ptr)[i].Loc,
                                        sizeof(char),
                                        (ptr_arr_structs->Ptr)[i].Len,
                                        w_file);

        fputc('\n', w_file);

        if (num_written_sym != (ptr_arr_structs->Ptr)[i].Len)
        {
            $r;
            printf("Error in writing to file\n");
            Assert(num_written_sym != (ptr_arr_structs->Ptr)[i].Len);
            $d;

            return -1;
        }
    }

    return 0;
}
