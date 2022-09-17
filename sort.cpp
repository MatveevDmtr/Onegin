#include <stdlib.h>

#include "onegin.h"

int comparator(const void* line1, const void* line2)
{
    return str_compare(*(const char**)line1, *(const char**)line2, 1); // enum
}

int sort_text(type_buf_ptrs* ptr_buf_adrs, char* type_sort)
{
    if (!strcmp(type_sort, "merge"))
    {
        merge_sort_all(ptr_buf_adrs);
    }
    else if(!strcmp(type_sort, "qsort"))
    {
        printf("Start qsort\n");

        qsort(ptr_buf_adrs->Ptr, ptr_buf_adrs->Size, sizeof(char*), comparator);
    }
    else
    {
        $r;
        printf("Undefined type of sort\n");
        $d;
    }
}

int merge_sort_all(type_buf_ptrs* ptr_buf_adrs)
{
    type_buf_ptrs temp_arr = {NULL, 0};

    def_and_check(temp_arr.Ptr, allocate_array(char*, ptr_buf_adrs->Size), NULL);

    for (size_t i = 0; i < ptr_buf_adrs->Size; i++)
    {
        temp_arr.Ptr[i] = (ptr_buf_adrs->Ptr)[i];
    }

    single_merge(ptr_buf_adrs, &temp_arr, (*ptr_buf_adrs).Ptr, (*ptr_buf_adrs).Ptr + (*ptr_buf_adrs).Size);
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
}int str_compare(const char* ptr_line1, const char* ptr_line2, bool rev)
{
    Assert(ptr_line1 == NULL);
    Assert(ptr_line2 == NULL);

    if (rev == REVERSE)
    {
        while(!end_of_line(*ptr_line1))
        {
            ptr_line1++;
        }
        ptr_line1--;

        while(!end_of_line(*ptr_line2))
        {
            ptr_line2++;
        }
        ptr_line2--;
    }

    while(!end_of_line(*ptr_line1) && !end_of_line(*ptr_line2))
    {
        while (!end_of_line(*ptr_line1) && !isletter(*ptr_line1))
        {
            ptr_line1++;
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
