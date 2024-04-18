#include "config.h"


uint64_t hash1( const char* string ) {
    return 42;
}

uint64_t hash2( const char* string ) {
    STRING_VERIFY( string );

    return *string;
}

uint64_t hash3( const char* string ) {
    STRING_VERIFY( string );

    return strlen( string );
}

uint64_t hash4( const char* string ) {
    STRING_VERIFY( string );

    uint64_t ans = 0;
    for ( int pos = 0; string[pos] != 0; string++ ) ans += string[pos];
    return ans;
}

uint64_t hash5( const char* string ) {
    return 0;
}
