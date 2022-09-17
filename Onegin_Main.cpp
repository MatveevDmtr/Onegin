#include <stdio.h>
#include <TXLib.h>
#include <string.h>
#include <stdlib.h>

#include "defines.h"
#include "onegin.h"


int main()
{
    type_buf_char buf_text = {NULL, 0, 0};
    type_buf_ptrs buf_ptrs = {NULL, 0   };

    read_file("composition.txt", &buf_text, &buf_ptrs); // wtf buf_ptrs

    print_arr_ptrs(&buf_ptrs);

    test_comparison();

    sort_text(&buf_ptrs, "merge");

    print_arr_ptrs(&buf_ptrs);

    write_file("out.txt", &buf_text, &buf_ptrs);
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
