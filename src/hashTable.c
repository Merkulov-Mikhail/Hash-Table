#include "config.h"


List* tableCTOR() {

    List* table = ( List* ) calloc( sizeof( List ), TABLES_NUMBER );

    for ( int pos = 0; pos < TABLES_NUMBER; pos++ )
        listCTOR( table + pos );

    return table;
}

void tableDTOR( List* table ) {

    for ( int pos = 0; pos < TABLES_NUMBER; pos++ ) {
        // for ( int val = table->next[LIST_NULL_ELEM]; table->next[val] != LIST_NULL_ELEM; val = table->next[val] )
        // free( table->data[val] );

        listDTOR( table + pos );
    }

    free( table );
}


uint64_t addItem( List* table, char* string ) {

    uint64_t item_hash = HASH( string ) % MOD % TABLES_NUMBER;

    listInsert( table + item_hash, LIST_NULL_ELEM, string );

    return item_hash;

}


int findItem( List* table, const char* string ) {

    uint64_t item_hash = HASH( string ) % MOD % TABLES_NUMBER;
    List* currTable = table + item_hash;

    for ( int itemPos = currTable->next[LIST_NULL_ELEM]; itemPos != LIST_NULL_ELEM; itemPos = currTable->next[itemPos] )
        if ( !strcmp( string, currTable->data[itemPos] ) )
            return 1;

    return 0;
}

