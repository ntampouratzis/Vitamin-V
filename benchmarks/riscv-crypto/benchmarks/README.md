
# RISC-V Crypto Benchmarking

*A description of how the RISC-V Crypto extension benchmarking suite works.*

---

## Purpose

To evaluate a set of *popular* cryptographic algorithms on the *baseline* RISC-V architecture.

   These include:

   - The usual suspects from NIST:
     AES, SHA256, SHA512, SHA3

   - Other standardised and widely used algorithms: SM3, SM4

## Organisation

- `config/` - Contains toolchain configurations, allowing the same programs to be compiled and evaluated against RV64 architecture with the `B`itmanip extension, and with(out) the proposed
    scalar cryptography extensions.

- `share/` - General useful code / macros and instruction intrinsics.

- `test/` - Testbench programs for checking the correctness and performance
    of different algorithms.

- `crypto_hash/` - Hash algorithm implementations.
    Each directory under `crypto_has/` represents a single hash
    algorithm (SHA256/SHA512/SHA3 etc). Each algorithm may have several
    different implementations, optimising for different things, e.g. code size
    and/or performance.

### Makefile Structure

- The `common.mk` file contains useful macros for building libraries,
    objects and test executables.

- The top level `Makefile` *includes* `common.mk` and sub-makefiles in
    `crypto_hash/`, `test/` and so on.

- Each algorithm implementation has its own `Makefile.in`, which
  describes how to build a static library which can be linked against by
  a test program.

  - The static libraries are built with the intention of making it very
    easy to compile against them and run the same programs on different
    target simulators / devices.


## Build

The available tests that are executed in gem5: 

`build-test-aes_128_reference CONFIG=rv64-baseline`

`build-test-aes_192_reference CONFIG=rv64-baseline`

`build-test-aes_256_reference CONFIG=rv64-baseline`

`build-test-aes_128_zscrypto_rv64 CONFIG=rv64-zscrypto`

`build-test-aes_192_zscrypto_rv64 CONFIG=rv64-zscrypto`

`build-test-aes_256_zscrypto_rv64 CONFIG=rv64-zscrypto`

`build-test-sha256_reference CONFIG=rv64-baseline`

`build-test-sha256_zscrypto CONFIG=rv64-zscrypto`

`build-test-sha512_reference CONFIG=rv64-baseline`

`build-test-sha512_zscrypto_rv64 CONFIG=rv64-zscrypto`

`build-test-sha3_reference CONFIG=rv64-baseline`

`build-test-sha3_zscrypto_rv64 CONFIG=rv64-zscrypto`

`build-test-sm3_reference CONFIG=rv64-baseline`

`build-test-sm3_zscrypto_rv64 CONFIG=rv64-zscrypto`

`build-test-sm4_reference CONFIG=rv64-baseline`

`build-test-sm4_zscrypto CONFIG=rv64-zscrypto`

To be noticed that reference implementation is the SW implementation, while zscrypto_rv64 refers to the RISCV crypto-enabled extension.

- One *must* explicitly specify a build config using the `CONFIG=X` option.
  when invoking make:
    ```sh
    $> cd riscv-crypto
    $> source ./bin/conf.sh #setup the project workspace
    $> cd benchmarks
    $> make build-test-sha256_zscrypto CONFIG=rv64-zscrypto
    ```

  These configs are kept in the `$REPO_HOME/benchmarks/config/` directory,
  and specify different compiler and architecture flag combinations.

- Build results will be placed in `riscv-crypto/build/benchmarks/rv64-zscrypto/bin/test`.

## Running tests:

- Tests live in the `test/` directory, with one test *per algorithm*.
  A file is then linked against each different algorithm static library.

- To run the above test: 
  ```sh
  $> riscv-crypto/build/benchmarks/rv64-zscrypto/bin/test
  $> ./test_hash_sha256-sha256_zscrypto.elf
  ```
