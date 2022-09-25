
#include "defines.h"
#include "onegin.h"


int main(int argc, char* argv[])
{
    TYPE_SORT type_sort = MERGE; //default

    char input_file_name[MAX_LEN_LINE]= "composition.txt"; // default

    handle_cmd_args(argc, argv, &type_sort);

    type_buf_char buf_text             = {NULL, 0, 0};
    type_buf_structs arr_structs       = {NULL, 0   };
    type_buf_ptrs arr_adrs             = {NULL, 0   };

    read_file(input_file_name, &buf_text, &arr_structs, &arr_adrs);

    sort_and_write("out.txt", &buf_text, &arr_structs, &arr_adrs);

    getchar();
}

int handle_cmd_args(int argc, char** argv, TYPE_SORT* ptr_type_sort)
{
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
            *ptr_type_sort = MERGE;
        }
        else if(!strcmp(argv[args_count], "qsort"))
        {
            *ptr_type_sort = QSORT;
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
                "enter -h or help to read the instruction.\n"
                "The program starts with default parameters.\n");
        $d;
    }

    return 1;
}

int sort_and_write(char* filename,
                   type_buf_char* ptr_text_buf,
                   type_buf_structs* ptr_arr_structs,
                   type_buf_ptrs* ptr_arr_adrs)
{
    FILE* w_file = open_Wfile(filename);

    printf("Wfile opened\n");

    sort_text(ptr_arr_adrs, MERGE, comparator_straight);

    putting_buf_text_to_file(ptr_arr_adrs, w_file);

    sort_text(ptr_arr_adrs, MERGE, comparator_reverse);

    putting_buf_text_to_file(ptr_arr_adrs, w_file);

    put_buffer(w_file, ptr_arr_structs);

    fclose(w_file);
}

int print_arr_ptrs(type_buf_structs* ptr_arr_structs)
{
    printf("Print sorted list: \n");
    printf("size of array ptrs: %d\n", ptr_arr_structs->Size);
    for (size_t i = 0; i < ptr_arr_structs->Size; i++)
    {
        printf("line: %c\t", (ptr_arr_structs->Ptr)[i].Loc);
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
