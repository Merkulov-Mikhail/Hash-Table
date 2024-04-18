#include "list.h"


#ifndef _NO_LIST_VERIFY
    #define VERIFY \
        int _r = listVerify( lst );\
        if ( _r ) return _r;
#else
    #define VERIFY ;
#endif


int listInsert( List* lst, int index, elem string ) {

    VERIFY

    #ifdef _AUTO_LIST_REALLOC
        if ( lst->capt <= lst->size + 1 )
            listRealloc( lst );
    #endif

    // if prev[index] is -1, then this index isn't used in List, so return error code
    if ( lst->prev[index] <= -1 ) return FICTIVE_INDEX;

    /*
        listInsert( &lst, 1, 2 )

                       we have
          1      3     ----------
           \    /      next(1): 3
            \  /       prev(3): 1
             \/        ----------

        1    2    3    we need
                       ----------
        \   /\   /     next(1): 2
         \ /  \ /      prev(3): 2
          V    V
                       next(2): 3
                       prev(2): 1
                       ----------
    */

    // position of new Node
    int pos = lst->free;
    // sets free to the next index of free block
    lst->free = lst->next[lst->free];

    lst->data[pos] = string;

    // next(2): 3; prev(2): 1
    lst->next[pos] = lst->next[index];
    lst->prev[pos] = index;

    // next(1): 2
    lst->next[index] = pos;

    // prev(3): 2
    lst->prev[lst->next[pos]] = pos;

    lst->size++;

    return pos;
}


elem listDelete( List* lst, int index ){

    int _r = listVerify( lst );
    if ( _r ) return ( elem ) _r;

    #ifdef _AUTO_LIST_REALLOC
        if ( lst->capt == lst->size + 1 )
            listRealloc( lst );
    #endif

    // if prev[index] is -1, then this index isn't used in List, so return error code
    if ( lst->prev[index] == -1 ) return ( elem ) FICTIVE_INDEX;

    // we CAN NOT delete 0 index
    if ( index == LIST_NULL_ELEM ) return ( elem ) ZERO_DELETE;

    /*
        listDelete( &lst, 2 )


        1    2    3     we have
                        ----------
         \   /\   /     next(1): 2
          \ /  \ /      next(2): 3
           V    V
                        prev(2): 1
                        prev(3): 2
                        ----------


          1    3        we need
          \    /        ----------
           \  /         next(1): 3
            \/          prev(3): 1
                        ----------
    */

    int prev = lst->prev[index],
        next = lst->next[index];

    // next(1): 3
    lst->next[prev] = next;

    // prev(3): 1
    lst->prev[next] = prev;

    elem toReturn = lst->data[index];

    lst->data[index] = 0;
    lst->prev[index] = -1;

    // updates singly linked list of fictive elements
    lst->next[index] = lst->free;
    lst->free = index;

    // if element's previous index is 0, then this element is head

    lst->size--;

    return toReturn;
}



int listCTOR( List* lst, int size ){

    if ( !lst )
        return 1;

    lst->free = 1;
    lst->size = 0;
    lst->capt = size;

    lst->next = ( int*  ) calloc( sizeof( int ),  lst->capt );
    lst->prev = ( int*  ) calloc( sizeof( int ),  lst->capt );
    lst->data = ( elem* ) calloc( sizeof( elem ), lst->capt );

    // if one of the callocs didn't work, we return an error code
    if ( !lst->next ||
         !lst->prev ||
         !lst->data )
        return 1;

    for ( int i = 0; i < lst->capt; i++ ){
        lst->next[i] = i + 1;
        lst->prev[i] = -1;
    }
    // Element zero - starting element, so it's next and prev is itself
    lst->prev[LIST_NULL_ELEM] = 0;
    lst->next[LIST_NULL_ELEM] = 0;
    // next(last_index) = 0
    lst->next[lst->capt - 1] = 0;

    return 0;

}


int getListTail( List* lst ){

    VERIFY

    return lst->prev[LIST_NULL_ELEM];

}


int getListHead( List* lst ){

    VERIFY

    return lst->next[LIST_NULL_ELEM];

}


int listDTOR( List* lst ){

    VERIFY

    for ( int i = 0; i < lst->size; i++ ){
        lst->data[i] = 0;
        lst->next[i] = 0;
        lst->prev[i] = 0;
    }

    lst->free = -1;
    lst->size = -1;
    lst->capt = -1;
    free( lst->next );
    free( lst->prev );
    free( lst->data );

    lst->next = nullptr;
    lst->prev = nullptr;
    lst->data = nullptr;

    return 0;
}

void listDump( List* lst ){

    printf("--LIST--\n");
    printf("head %d\ntail %d\nfree %d\nsize %d\n\n", getListHead( lst ), getListTail( lst ), lst->free, lst->size);

    for ( int i = 0; i < lst->capt; i++ ){
        if ( lst->prev[i] == -1 )
            continue;
        printf("--NODE #%d--\n", i);;
        printf("value %d\n", lst->data[i]);
        printf("next %d\n" , lst->next[i]);
        printf("prev %d\n" , lst->prev[i]);
        printf("\n");
    }

    printf("index\t");
    for ( int i = 0; i < lst->capt; i++)
        printf("%5d", i);
    printf("\nnext\t");

    for ( int i = 0; i < lst->capt; i++ ){
        printf("%5d", lst->next[i]);
    }

    printf("\nprev\t");
    for ( int i = 0; i < lst->capt; i++ ){
        printf("%5d", lst->prev[i]);
    }

    printf("\ndata\t");
    for ( int i = 0; i < lst->capt; i++ ){
        printf("%5d", lst->data[i]);
    }
    printf("\n--END OF LIST--\n\n");
}

int listVerify( List* lst ){

    if ( !lst       ||
         !lst->prev ||
         !lst->next ||
         !lst->data )
        return LIST_NULL_PTR;

    if ( lst->prev[LIST_NULL_ELEM] == -1 )
        return ZERO_IS_FICTIVE;

    return 0;
}


int listRealloc( List* lst, int size ){

    VERIFY

    int capacity = size;

    if (!capacity)
        capacity = lst->capt * _LIST_MULTIPLIER;

//----------------------------------------------------------------
    int*  tmpNext = ( int*  ) calloc( sizeof( int  ), capacity );

    if ( !tmpNext )
        return ALLOCATION_ERR;

    int*  tmpPrev = ( int*  ) calloc( sizeof( int  ), capacity );

    if ( !tmpPrev ){
        free( tmpNext );
        return ALLOCATION_ERR;
    }

    elem* tmpData = ( elem* ) calloc( sizeof( elem ), capacity );

    if ( !tmpData ){
        free( tmpNext );
        free( tmpPrev );
        return ALLOCATION_ERR;
    }
//----------------------------------------------------------------
    int redefinedFree = 0;
    for ( int i = 0; i < capacity; i++ ){
        if ( i >= lst->capt ){
            tmpNext[i] = i + 1;
            tmpPrev[i] = -1;
            tmpData[i] =  0;
        }
        else{
            tmpPrev[i] = lst->prev[i];
            tmpNext[i] = lst->next[i];
            tmpData[i] = lst->data[i];
        }
        if (!redefinedFree && tmpPrev[i] == -1){
            lst->free = i;
            redefinedFree = 1;
        }
    }

    tmpNext[capacity - 1] = LIST_NULL_ELEM;

    free( lst->prev );
    free( lst->next );
    free( lst->data );

    lst->capt = capacity;
    lst->next = tmpNext;
    lst->prev = tmpPrev;
    lst->data = tmpData;

    return 0;
}


int graphicDump( List* lst, const char* NAME ){

    VERIFY

    FILE* file = fopen( NAME, "w" );

    fprintf(file, "digraph List{\n\tNode[shape=rect, style=\"filled\", bordercolor=\"yellow\", color=\"#A8A8A8\"]\n");
    fprintf(file, "\thead [label=\"{head|<ptr>ptr}\", shape=record]\n");
    fprintf(file, "\ttail [label=\"{tail|<ptr>ptr}\", shape=record]\n");

    int curr = getListHead( lst );

    fprintf(file, "\t{rank=same; ");
    for ( int i = 0; i < lst->size; i++ ){
        fprintf( file, "prev%d ", curr );
        curr = lst->next[curr];
    }
    fprintf(file, "}\n");

    curr = getListHead( lst );
    fprintf(file, "\tprev%d", curr);


    for ( int i = 0; i < lst->size - 1; i++ ){
        fprintf(file, " -> prev%d", lst->next[curr]);
        curr = lst->next[curr];
    }

    fprintf(file, "[style=invis]\n\t");

    curr = getListHead( lst );
    for ( int i = 0; i < lst->size; i++ ){
        fprintf(file, "prev%d[label=\n\t\
<<table>\n\t\
    <tr>\n\t\
        <td>value = %d</td>\n\t\
    </tr>\n\t\
    <tr>\n\t\
        <td>index = %d</td>\n\t\
    </tr>\n\t\
</table>>, fillcolor=\"#A8A8A8\"]\n\n\t", curr, lst->data[curr], curr);
        curr = lst->next[curr];
    }

    curr = getListHead( lst );

    for ( int i = 0; i < lst->size; i++ ){
        if ( lst->next[curr] == LIST_NULL_ELEM )
            fprintf( file, "\tprev%d->prev%d[color=magenta]\n", curr, getListHead( lst ) );
        else
            fprintf( file, "\tprev%d->prev%d[color=magenta]\n", curr, lst->next[curr] );
        if ( lst->prev[curr] == LIST_NULL_ELEM )
            fprintf( file, "\tprev%d->prev%d[color=cyan]\n\n", curr, getListTail( lst ) );
        else
            fprintf( file, "\tprev%d->prev%d[color=cyan]\n\n", curr, lst->prev[curr] );
        curr = lst->next[curr];
    }

    fprintf(file, "\thead:ptr->prev%d[color=\"#006400\"]\n", getListHead( lst ));
    fprintf(file, "\ttail:ptr->prev%d[color=\"#000064\"]\n", getListTail( lst ));
    fprintf(file,  "}" );
    return 0;

}
