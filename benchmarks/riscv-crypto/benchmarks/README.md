
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


## Build & Run

- One *must* explicitly specify a build config using the `CONFIG=X` option.
  when invoking make:
    ```sh
    $> cd $REPO_HOME/benchmarks
    $> make all CONFIG=rv64-baseline-b
    $> make all CONFIG=rv64-baseline
    $> make all CONFIG=rv64-zscrypto
    ```

  These configs are kept in the `$REPO_HOME/benchmarks/config/` directory,
  and specify different compiler and architecture flag combinations.

  - **Note:** Not all targets are expected to build for all configurations.
    E.g. the SHA512 `zscrypto` benchmark will not work on an `rv32-*`
    target, since it requires 64-bit only instructions.

- Build results will be placed in `$REPO_BUILD/benchmarks/[CONFIG]/*`.

- For those without tab-completion, running
  ```sh
  $> make CONFIG=rv64-baseline print-build-targets
  $> make CONFIG=rv64-baseline print-all-targets
  ```
  Will tell you which build / simulation targets there are.

### Running tests:

- Tests live in the `test/` directory, with one test *per algorithm*.
  A file is then linked against each different algorithm static library.

- To run all of the tests for a given config:
  ```sh
  $> make CONFIG=rv64-baseline run
  ```

- Or see which run targets are available:
  ```sh
  $> make CONFIG=rv64-baseline print-run-targets
  ```

- The results of a run are placed in
  `$REPO_BUILD/benchmarks/[CONFIG]/log/test/*`.
  Each log file contains the `stdout` of the test, including instruction
  execution counts.

- Each test *prints* python3 code to `stdout`. This python code is then
  executed to check that the algorithm produced the correct results
  against a completely different implementation.
