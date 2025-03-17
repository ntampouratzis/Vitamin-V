
#include <stdlib.h>
#include <string.h>

#include "riscvcrypto/share/test.h"
#include "riscvcrypto/share/util.h"

#include "riscvcrypto/sha3/fips202.h"


int main(int argc, char ** argv) {

    printf("import sys, binascii, hashlib\n");
    printf("benchmark_name = \"" STR(TEST_NAME)"\"\n");

    const int num_tests = 10;
        
    unsigned long long   hash_input_len = TEST_HASH_INPUT_LENGTH    ;
    unsigned char      * hash_input                                 ;
    unsigned char        hash_signature  [CRYPTO_HASH_SHA3_512_BYTES] ;

    for(int i = 0; i < num_tests; i ++) {

        hash_input  = calloc(hash_input_len, sizeof(unsigned char));

        test_rdrandom(hash_input, hash_input_len);

        const uint64_t start_instrs   = test_rdinstret();

        FIPS202_SHA3_512(
            hash_input    ,
            hash_input_len,
            hash_signature 
        );
        
        const uint64_t end_instrs     = test_rdinstret();

        const uint64_t final_instrs   = end_instrs - start_instrs;

        printf("#\n# test %d/%d\n",i , num_tests);

        printf("input_len       = %llu\n", hash_input_len);
        
        printf("input_data      = ");
        puthex_py(hash_input,hash_input_len);
        printf("\n");

        printf("signature       = ");
        puthex_py(hash_signature, CRYPTO_HASH_SHA3_512_BYTES);
        printf("\n");

        printf("instr_count     = 0x");
        puthex64(final_instrs);
        printf("\n");
        
        printf("testnum         = %d\n",i);
        printf("ipb             = instr_count / input_len\n");

        printf("s3              = hashlib.sha3_512()\n");
        printf("s3.update( input_data )\n");
        printf("reference       = s3.digest()\n");
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

        hash_input_len += TEST_HASH_INPUT_LENGTH / 2;

        free(hash_input);

    }

    return 0;
}
