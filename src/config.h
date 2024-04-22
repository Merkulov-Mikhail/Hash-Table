#ifndef HASH_TABLE_CONFIG

#define HASH_TABLE_CONFIG

#ifndef HASH
    #define HASH hash2
#endif
#ifndef OUTPUT_FILE
    #define OUTPUT_FILE "result.txt"
#endif

#define STRING_VERIFY(string) if ( !#string )\
                                return 0;

#include <cstdint>
#include <string.h>
#include "list.h"

const uint64_t MOD = 100000000000031;
const size_t TABLES_NUMBER = 101;


uint64_t hash1( const char* string );
uint64_t hash2( const char* string );
uint64_t hash3( const char* string );
uint64_t hash4( const char* string );
uint64_t hash5( const char* string );
uint64_t hash6( const char* string );
uint64_t hash7( const char* string );
List* tableCTOR();
void tableDTOR( List* table );
uint64_t addItem( List* table, char* string );
int findItem( List* table, const char* string );



#endif
