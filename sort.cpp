#include <stdlib.h>

#include "onegin.h"

int comparator_straight(const void* line1, const void* line2)
{
    fprintf(stderr, "Pointers in comparator:      %p %p\n",    line1, line2);
    fprintf(stderr, "Changing type in comparator: %p %p\n\n",  *(const char**)line1, *(const char**)line2);
    fprintf(stderr, "Strings in comparator:      /%s/%s/\n\n", *(const char**)line1, *(const char**)line2);

    return str_compare(*(const char**)line1, *(const char**)line2); // enum
}

int comparator_reverse(const void* line1, const void* line2)
{
    return str_compare_reverse(*(const char**)line1, *(const char**)line2); // enum
}

int sort_text(type_buf_ptrs* ptr_buf_adrs,
              char* type_sort,
              int (*comparator)(const void* line1, const void* line2))
{
    if (!strcmp(type_sort, "merge")) // case
    {
        merge_sort_all(ptr_buf_adrs, comparator);
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

int merge_sort_all(type_buf_ptrs* ptr_buf_adrs, int (*comparator)(const void* line1, const void* line2))
{
    type_buf_ptrs temp_arr = {NULL, 0};

    temp_arr.Ptr = allocate_array(char*, ptr_buf_adrs->Size);

    Assert(temp_arr.Ptr == NULL);

    for (size_t i = 0; i < ptr_buf_adrs->Size; i++)
    {
        temp_arr.Ptr[i] = (ptr_buf_adrs->Ptr)[i];
    }

    single_merge(ptr_buf_adrs,
                 &temp_arr,
                 ptr_buf_adrs->Ptr,
                 ptr_buf_adrs->Ptr + ptr_buf_adrs->Size,
                 comparator);
}

int single_merge(type_buf_ptrs* arr,
                 type_buf_ptrs* temp,
                 char** ptr_start,
                 char** ptr_end,
                 int (*comparator)(const void* line1, const void* line2))
{
    char** ptr_mid = ptr_start + (ptr_end - ptr_start) / 2;

    if (ptr_end - ptr_start <= 1)
    {
        return 1;
    }

    single_merge(arr, temp, ptr_start, ptr_mid, comparator);
    single_merge(arr, temp, ptr_mid  , ptr_end, comparator);

    Merge(arr, temp, ptr_start, ptr_mid, ptr_end, comparator);
}

int Merge(type_buf_ptrs* arr,
          type_buf_ptrs* temp,
          char** ptr1,
          char** ptr2,
          char** ptr2_end,
          int (*comparator)(const void* line1, const void* line2))
{
    char** ptr1_end = ptr2;

    int i = ptr1 - (arr->Ptr);
    while (ptr1 < ptr1_end && ptr2 < ptr2_end)
    {
        printf("Pointers to comparator: %p %p\n", *ptr1,  *ptr2);
        printf("Strings  to comparator: %c %c\n", **ptr1, **ptr2);

        if (comparator((const void*)ptr1, (const void*)ptr2) < NULL)
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

int str_compare(const char* ptr_line1, const char* ptr_line2)
{
    Assert(ptr_line1 == NULL);
    Assert(ptr_line2 == NULL);

    bool end1_reached = false;
    bool end2_reached = false;

    printf("Ptr_to_sym_in_line1: %d, ptr_to_sym_in_line2^ %d", ptr_line1, ptr_line2);

    while(!(end1_reached = end_of_line(*ptr_line1)) &&
          !(end2_reached = end_of_line(*ptr_line2)))
    {

        printf("sym_in_line1: %c, sym_in_line2^ %c", *ptr_line1, *ptr_line2);
        while (!(end1_reached = end_of_line(*ptr_line1)) && !isletter(*ptr_line1))
        {
            ptr_line1++;
        }
        while (!(end2_reached = end_of_line(*ptr_line2)) && !isletter(*ptr_line2))
        {
            ptr_line2++;
        }

        if (end1_reached || end2_reached)
        {
            break;
        }

        if (*ptr_line1 != *ptr_line2)
        {
            return *ptr_line1 - *ptr_line2;
        }

        ptr_line1++;
        ptr_line2++;
    }

    if (end1_reached)
    {
        return -1;
    }

    if (end2_reached)
    {
        return 1;
    }

    return 0;
}

int str_compare_reverse(const char* ptr_line1, const char* ptr_line2) // array struct
{
    Assert(ptr_line1 == NULL);
    Assert(ptr_line2 == NULL);

    const char* ptr_line1_start = ptr_line1;
    const char* ptr_line2_start = ptr_line2;

    while(!end_of_line(*ptr_line1))
    {
        ptr_line1++;
    }
    ptr_line1--;

    //printf("last sym of line: %c\n", *ptr_line1);

    while(!end_of_line(*ptr_line2))
    {
        ptr_line2++;
    }
    ptr_line2--;

    //printf("last sym of line: %c\n", *ptr_line2);

    bool start1_reached = false;
    bool start2_reached = false;


    while(!(start1_reached = (ptr_line1 < ptr_line1_start)) &&
          !(start2_reached = (ptr_line2 < ptr_line2_start)))
    {
        while (!(start1_reached = (ptr_line1 < ptr_line1_start)) && !isletter(*ptr_line1))
        {
            ptr_line1--;
        }
        while (!(start2_reached = (ptr_line2 < ptr_line2_start)) && !isletter(*ptr_line2))
        {
            ptr_line2--;
        }

        if (start1_reached || start2_reached)
        {
            break;
        }

        if (*ptr_line1 != *ptr_line2)
        {
            return *ptr_line1 - *ptr_line2;
        }

        ptr_line1--;
        ptr_line2--;
    }

    if (start1_reached)
    {
        return -1;
    }

    if (start2_reached)
    {
        return 1;
    }

    return 0;
}

int test_comparison()
{
    char line1[] = "abcDe";
    char line2[] = "abcd";
    int res = str_compare(line1, line2);
    printf("Comparison %s and %s: %d\n", line1, line2, res);
    if (res < 0)
    {
        printf("Comparison %s and %s successful\n", line1, line2);

        return true;
    }
    printf("Comparison failed\n");

    return 0;
}
