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
    for ( int pos = 0; string[pos] != 0; pos++ ) ans += string[pos];
    return ans;
}

uint64_t hash5( const char* string ) {
    uint64_t ans = 0;

    for ( int pos = 0; string[pos] != 0; pos++ ) ans = string[pos] ^ ( ( ans >> 1 ) & 0x7FFFFFFFFFFFFFFF | ( ( ans % 2 ) << 63 ) );

    return ans;
}


uint64_t hash6( const char* string ) {
    uint64_t ans = 0;

    for ( int pos = 0; string[pos] != 0; pos++ ) ans = string[pos] ^ ( ( ans << 1 ) & 0x7FFFFFFFFFFFFFFF | ( ( ans % 2 ) << 63 ) );

    return ans;
}


uint64_t hash7( const char* string ) { // fletcher
    unsigned int sum1 = 0, sum2 = 0;

    for ( int pos = 0; string[pos] != 0; pos++ ) {
        sum1 = sum1 + string[pos];
        sum2 = sum2 + sum1;
    }

    return ( sum2 << 32 ) + sum1;
}
