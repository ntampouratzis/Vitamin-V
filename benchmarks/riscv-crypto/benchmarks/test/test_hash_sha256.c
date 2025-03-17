
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>

#include "riscvcrypto/share/test.h"

#include "riscvcrypto/sha256/api_sha256.h"

long calculate_time_difference(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
}




int main(int argc, char ** argv) {

    printf("import sys, binascii, Crypto.Hash.SHA256 as SHA2_256\n");
    printf("benchmark_name = \"" STR(TEST_NAME)"\"\n");

    const int num_tests = 10;
        
    size_t     message_len  = TEST_HASH_INPUT_LENGTH  ;
    uint8_t  * message      ;
    uint32_t   digest    [8];


    for(int i = 0; i < num_tests; i ++) {

        message  = calloc(message_len, sizeof(unsigned char));

        test_rdrandom(message, message_len);
struct timeval start, end;

gettimeofday(&start, NULL);

        sha256_hash (
            digest      ,
            message     ,
            message_len
        );

gettimeofday(&end, NULL);

long elapsed_time = calculate_time_difference(start, end);

    printf("Elapsed time: %ld microseconds\n", elapsed_time);

        printf("#\n# test %d/%d\n",i , num_tests);

        printf("input_len       = %u\n", message_len);
        
        printf("input_data      = ");
        puthex_py(message,message_len);
        printf("\n");

        printf("signature       = ");
        puthex_py((uint8_t*)digest, 8*4);
        printf("\n");
     
        printf("testnum         = %d\n",i);
        printf("ipb             = instr_count / input_len\n");

        printf("reference       = SHA2_256.new(input_data).digest()\n");
        printf("if( reference  != signature ):\n");
        printf("    print(\"Test %d failed.\")\n", i);
        printf("    print( 'input     == %%s' %% ( binascii.b2a_hex( input_data ) ) )" "\n"   );
        printf("    print( 'reference == %%s' %% ( binascii.b2a_hex( signature ) ) )" "\n"   );
        printf("    print( '          != %%s' %% ( binascii.b2a_hex( reference ) ) )" "\n"   );
        printf("    sys.exit(1)\n");
        printf("else:\n");
        printf("    print(\""STR(TEST_NAME)" Test %%d passed. "
               "%%d instrs / %%d bytes. IPB=%%f\" %% "
               "(testnum,instr_count,input_len,ipb))\n");

        message_len += TEST_HASH_INPUT_LENGTH / 2;

        free(message);

    }

    return 0;
}
