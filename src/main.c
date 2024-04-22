#include "config.h"


int main() {


    FILE* File = fopen( "data.txt", "r" );
    List* table = tableCTOR();

    int chr = 0;
    int pos = 0;
    char* BigBuffer = ( char* ) calloc( sizeof( char ), 15 );

    while ( (chr = fgetc( File ) ) != EOF ){

        BigBuffer[pos++] = chr;

        if ( chr == '\n' ) {
            pos = 0;

            addItem( table, BigBuffer );
            BigBuffer = ( char* ) calloc( sizeof( char ), 15 );
        }
    }

    char hsh[5] = {};
    int tmp = 0;
    for ( int i = 10; i < 10000; i++ ){
        pos = 0;
        tmp = i;
        while ( tmp ) {
            hsh[pos] = tmp % 256;
            tmp >>= 8;
            pos++;
        }
        findItem( table, hsh );
    }

    fclose( File );
    File = fopen( OUTPUT_FILE, "w" );

    for ( pos = 0; pos < TABLES_NUMBER; pos++ ) {
        fprintf( File, "%d ", table[pos].size );
    }

    fclose( File );
    tableDTOR( table );
    return 0;
}
