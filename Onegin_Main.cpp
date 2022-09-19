
#include "defines.h"
#include "onegin.h"


int main(int argc, char* argv[])
{
    //int* location = allocate_array(int, 15);

    //$(location);
    //return 0;
    TYPE_SORT type_sort = MERGE;
    // move from main
    char input_file_name[30] = "composition.txt"; // magic number

    for(int args_count = 1; args_count < argc; args_count++)
    {
        if (!strcmp(argv[args_count], "stop"))
        {
            return 0;
        }
        else if (!strcmp(argv[args_count], "help") ||
                 !strcmp(argv[args_count], "h"   ) ||
                 !strcmp(argv[args_count], "-h"  ))
        {
            print_help("help.txt");
            return 0;
        }
        else if(!strcmp(argv[args_count], "merge"))
        {
            type_sort = MERGE;
        }
        else if(!strcmp(argv[args_count], "qsort"))
        {
            type_sort = QSORT;
        }
        else if(!strcmp(argv[args_count], "merge"))
        {
            type_sort = MERGE;
        }
        else
        {
            $r;
            printf("Incorrect parameters chosen.\n"
                   "The program starts with default parameters.\n");
            $d;
        }
    }

    if(argc == 1)
    {
        $r;
        printf("Mode of the program has not been chosen.\n"
                "Please, restart the program and "
                "enter -h or help to read the instruction.\n");
        $d;
        return 0;
    }

    type_buf_char buf_text       = {NULL, 0, 0};
    type_buf_ptrs buf_ptrs       = {NULL, 0   };
    type_buf_ptrs const_buf_ptrs = {NULL, 0   }; // origin

    read_file(input_file_name, &buf_text, &buf_ptrs, &const_buf_ptrs); // wtf buf_ptrs

    print_arr_ptrs(&buf_ptrs);

    test_comparison();

    sort_and_write("out.txt", &buf_text, &buf_ptrs, &const_buf_ptrs);

    getchar();
}
// move to main
int sort_and_write(char* filename,
                   type_buf_char* ptr_text_buf,
                   type_buf_ptrs* ptr_buf_adrs,
                   type_buf_ptrs* ptr_const_buf_adrs)
{
    FILE* w_file = open_Wfile(filename);

    printf("Wfile opened\n");
                            // enum??
    sort_text(ptr_buf_adrs, "merge", comparator_straight);

    putting_buf_text_to_file(ptr_buf_adrs, w_file);

    sort_text(ptr_buf_adrs, "merge", comparator_reverse);

    putting_buf_text_to_file(ptr_buf_adrs, w_file);

    putting_buf_text_to_file(ptr_const_buf_adrs, w_file);

    fclose(w_file);
}


/*char* allocate_text(int num_bytes)
{
    char* ptr_buf = (char*)calloc(num_bytes, sizeof(char));

    Assert(ptr_buf == NULL);

    return ptr_buf;
}*/


int print_arr_ptrs(type_buf_ptrs* ptr_buf_adrs)
{
    printf("Print sorted list: \n");
    printf("size of array ptrs: %d\n", ptr_buf_adrs->Size);
    for (size_t i = 0; i < ptr_buf_adrs->Size; i++)
    {
        printf("line: %c\t", *(ptr_buf_adrs->Ptr[i]));
    }
    printf("\n");
}

int print_help(char* filename)
{
    FILE* help_file = open_file_rmode(filename);

    type_buf_char buf_help = {NULL, 0, 0};

    buf_help.Size = safe_def_int(get_file_size(help_file), NULL);

    buf_help.Ptr = allocate_array(char, buf_help.Size);

    text_to_buffer(help_file, &buf_help);

    buf_help.Num_lines = count_lines(&buf_help);

    $g;
    printf("%s\n", buf_help.Ptr);
    $d;
}
