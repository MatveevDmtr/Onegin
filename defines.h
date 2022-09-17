#define Assert(condition) \
{\
        if(condition)\
        {\
        $r;\
        printf("ERROR in line %d in \n%s \nFound (%s).\n", __LINE__, __FILE__, #condition);\
        $d;\
        }\
}

#define allocate_array(type, num_bytes)        \
    (type*) calloc (num_bytes, sizeof (type)); \
    printf ("Type_calloc: %s\n", #type);       \
    printf ("Sizeof type: %d\n", sizeof (type*))

//char* a = alloc_array (int, 10);

#define def_and_check(variable, func, invalid_value) \
    variable = func; \
    Assert(variable == invalid_value);

#define logdval(var) \
    printf("Value: #var = %d", var);

#define $(var, func, invalid_value) \
    var = func;\
    Assert(var = nivelid_value);
