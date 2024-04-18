#ifndef _LIST

    #define _LIST
    #define _AUTO_LIST_REALLOC

    #include <stdio.h>
    #include <stdlib.h>


    typedef char* elem;

    const int LIST_SIZE = 11;
    const int LIST_NULL_ELEM = 0;
    const int _LIST_MULTIPLIER = 2;

    static const char* _GRAPH_FILE = "graph.dot";

    struct List{
        int free;
        int size;
        int capt; // capacity

        elem* data;

        int* next;
        int* prev;
    };


    /*
        \brief creates struct List

        \param lst - pointer to List struct
        \return 1 if failed to allocate memory, 0 otherwise
    */
    int listCTOR( List* lst, int size = LIST_SIZE );

    /*
        \brief destroys struct List

        \param lst - pointer to List struct
    */
    int listDTOR( List* lst );

    /*
        \brief adds new element to List
        Inserts new element right after [index] element. If there is no data in [index], then returns error code.

        Updates tail if new element added right after previous tail.

        \return FICTIVE_INDEX if [index] is not used in lst.
                error         some value from listVerify. Accures, if the list is incorrect
                idx           otherwise returns index of inserted element.
        FICTIVE_INDEX is negative.
    */
    int listInsert( List* lst, int index, elem value );

    /*
        \brief deletes element [index]
        Deletes element [index] from list.
        If there is no data in [index], then returns error code.
        If index equals to 0, then returns error code (we can't delete index 0 element).

        Updates head if some element now has 0 as prev index.

        \return FICTIVE_INDEX if [index] is not used in lst
                ZERO_DELETE   if [index] equals to 0
                error         some value from listVerify. Accures, if the list is incorrect
                value         if not FICTIVE_INDEX and ZERO_DELETE, value is deleted value that was stored under [index]
        ZERO_DELETE and FICTIVE_INDEX are negative
    */
    elem listDelete( List* lst, int index );

    /*
        \brief reallocates list
        Multiply current capacity by _LIST_MULTIPLIER. Exact capacity can be passed as second argument.

        !!IF NEW CAPACITY IS LESS THAN CURRENT, BE READY FOR UB!!

        By default, auto realloc is not active, however it can be turned on with defining _AUTO_LIST_REALLOC

        \return 1 if failed to allocate memory, 0 otherwise
    */

    int listRealloc( List* lst, int size = 0 );

    /*
        \brief checks list if its correct

        Can be turned off with defining _NO_LIST_VERIFY

        \return  0                allright
                LIST_NULL        if lst is nullptr
                ZERO_IS_FICTIVE  if element with index 0 is fictive

    */

    int listVerify( List* lst );

    void listDump  ( List* lst );
    int graphicDump( List* lst, const char* NAME = _GRAPH_FILE );


    enum ERRORS{
        ALLOCATION_ERR  = 5,
        LIST_NULL_PTR   = 4,
        ZERO_IS_FICTIVE = 3,
        ZERO_DELETE     = 2,
        FICTIVE_INDEX   = 1
    };

#endif
