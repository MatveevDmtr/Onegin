#define Assert(condition)                                  \
{                                                          \
    if(condition)                                          \
    {                                                      \
        $r;                                                \
        printf("ERROR in line %d in \n%s \nFound (%s).\n", \
                __LINE__, __FILE__, #condition);           \
        $d;                                                \
    }                                                      \
}

#define allocate_array(type, num_bytes)             \
(                                                   \
    printf ("Type_calloc: %s\n", #type),            \
    printf ("Sizeof type: %d\n", sizeof (type*)),   \
    (type*) calloc (num_bytes, sizeof (type))       \
)

#define allocate_array(type, num_elems)                             \
({                                                                  \
    type* location__ = (type*) calloc (num_elems, sizeof (type));   \
    printf ("Type_calloc: %s\n", #type);                            \
    printf ("Sizeof type: %d\n", sizeof (type*));                   \
    Assert(location__ == NULL);                                     \
    printf("Calloc returned: %p\n", location__);                    \
    location__;                                                     \
})

//char* a = alloc_array (int, 10);

#define safe_def_int(func, invalid_value)    \
({                                            \
    int variable__ = func;                   \
    Assert(variable__ == invalid_value);     \
    variable__;                               \
})

#define logdval(var) \
    printf("Value: #var = %d", var);

/*#define $(var, func, invalid_value) \
    var = func;\
    Assert(var = invalid_value);

   */
