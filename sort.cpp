#include <stdlib.h>

#include "onegin.h"

int comparator_straight(const void* line1, const void* line2)
{
    fprintf(stderr, "Pointers in comparator:      %p %p\n",    line1, line2);
    fprintf(stderr, "Changing type in comparator: %p %p\n\n",  (type_prop_line*)line1, (type_prop_line*)line2);
    fprintf(stderr, "Strings in comparator:      /%s/%s/\n\n", (*(type_prop_line**)line1)->Loc,
                                                               (*(type_prop_line**)line2)->Loc);

    return str_compare(*(type_prop_line**)line1, *(type_prop_line**)line2);
}

int comparator_reverse(const void* line1, const void* line2)
{
    return str_compare_reverse(*(type_prop_line**)line1,
                               *(type_prop_line**)line2);
}

int sort_text(type_buf_ptrs* ptr_arr_adrs,
              TYPE_SORT type_sort,
              int (*comparator)(const void* line1, const void* line2))
{
    switch(type_sort)
    {
        case MERGE:
            merge_sort_all(ptr_arr_adrs, comparator);
            break;

        case QSORT:
            printf("Start qsort\n");
            qsort(ptr_arr_adrs->Ptr, ptr_arr_adrs->Size, sizeof(char*), comparator);
            break;

        default:
            $r;
            printf("Undefined type of sort\n");
            $d;
    }
}

int merge_sort_all(type_buf_ptrs* ptr_arr_adrs, int (*comparator)(const void* line1, const void* line2))
{
    type_buf_ptrs temp_arr = {NULL, 0};

    temp_arr.Ptr = allocate_array(type_prop_line*, ptr_arr_adrs->Size);

    Assert(temp_arr.Ptr == NULL);

    for (size_t i = 0; i < ptr_arr_adrs->Size; i++)
    {
        temp_arr.Ptr[i] = (ptr_arr_adrs->Ptr)[i];
    }
    printf("Copy to temp finished\n");
    printf("SIze of arr_adrs: %d\n", ptr_arr_adrs->Size);

    single_merge(ptr_arr_adrs,
                 &temp_arr,
                 ptr_arr_adrs->Ptr,
                 ptr_arr_adrs->Ptr + ptr_arr_adrs->Size,
                 comparator);
}

int single_merge(type_buf_ptrs* arr,
                 type_buf_ptrs* temp,
                 type_prop_line** ptr_start,
                 type_prop_line** ptr_end,
                 int (*comparator)(const void* line1, const void* line2))
{
    printf("start end pointers: %d %d\n", ptr_start, ptr_end);
    type_prop_line** ptr_mid = ptr_start + (ptr_end - ptr_start) / 2;

    if (ptr_end - ptr_start <= 1)
    {
        return 1;
    }

    single_merge(arr, temp, ptr_start, ptr_mid, comparator);
    single_merge(arr, temp, ptr_mid  , ptr_end, comparator);

    printf("going to Merge\n");

    Merge(arr, temp, ptr_start, ptr_mid, ptr_end, comparator);
}

int Merge(type_buf_ptrs* arr,
          type_buf_ptrs* temp,
          type_prop_line** ptr1,
          type_prop_line** ptr2,
          type_prop_line** ptr2_end,
          int (*comparator)(const void* line1, const void* line2))
{
    type_prop_line** ptr1_end = ptr2;

    int i = ptr1 - (arr->Ptr);
    printf("start While in Merge\n");
    while (ptr1 < ptr1_end && ptr2 < ptr2_end)
    {
        printf("Adr ptr1: ", &ptr1);
        printf("Pointers to comparator: %p %p\n", ptr1,  ptr2);

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

int str_compare(type_prop_line* ptr_struct_line1, type_prop_line* ptr_struct_line2)
{
    Assert(ptr_struct_line1 == NULL);
    Assert(ptr_struct_line2 == NULL);

    bool end1_reached = false;
    bool end2_reached = false;

    char* ptr_line1 = ptr_struct_line1->Loc;
    char* ptr_line2 = ptr_struct_line2->Loc;

    char* ptr_end1 = ptr_struct_line1->Loc + ptr_struct_line1->Len;
    char* ptr_end2 = ptr_struct_line2->Loc + ptr_struct_line2->Len;

    printf("Ptr_to_sym_in_line1: %d, ptr_to_sym_in_line2: %d\n", ptr_line1, ptr_line2);

    while(!(end1_reached = (ptr_line1 < ptr_end1)) &&
          !(end2_reached = (ptr_line2 < ptr_end2)))
    {
        printf("sym_in_line1: %c, sym_in_line2^ %c", *ptr_line1, *ptr_line2);
        while (!(end1_reached = (ptr_line1 < ptr_end1)) && !isletter(*ptr_line1))
        {
            ptr_line1++;
        }
        while (!(end2_reached = (ptr_line2 < ptr_end2)) && !isletter(*ptr_line2))
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

int str_compare_reverse(type_prop_line* ptr_struct_line1,
                        type_prop_line* ptr_struct_line2)
{
    Assert(ptr_struct_line1 == NULL);
    Assert(ptr_struct_line2 == NULL);

    const char* ptr_line1_start = ptr_struct_line1->Loc;
    const char* ptr_line2_start = ptr_struct_line2->Loc;

    char* ptr_line1 = ptr_struct_line1->Loc + ptr_struct_line1->Len - 1;
    char* ptr_line2 = ptr_struct_line2->Loc + ptr_struct_line2->Len - 1;

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
