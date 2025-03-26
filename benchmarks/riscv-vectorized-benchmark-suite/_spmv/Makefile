#makefile

# Variables for the compiler and options
RISCV_BIN=${RISCV}/bin
PK=${RISCV}/riscv64-unknown-elf/bin/pk

# Variables for source code
SRC=src/spmv.c src/main.c
SRC_M8=src/spmv_m8.c src/main.c
BIN_DIR=bin
BIN_SERIAL=$(BIN_DIR)/spmv_serial.exe
BIN_VECTOR=$(BIN_DIR)/spmv_vector.exe
BIN_VECTOR_M8=$(BIN_DIR)/spmv_vector_m8.exe
DUMP_SERIAL=$(BIN_DIR)/spmv_serial.dump
DUMP_VECTOR=$(BIN_DIR)/spmv_vector.dump

start:
	rm -f bin/*.*

serial:
	@echo "Compiling serial version..."
	gcc -march=rv64gc -O2 -o $(BIN_SERIAL) $(SRC)
	
vector:
	@echo "Compiling vector version..."
	gcc -march=rv64gcv -DUSE_RISCV_VECTOR -O2 -I../common -o $(BIN_VECTOR) $(SRC)
	gcc -march=rv64gcv -DUSE_RISCV_VECTOR -O2 -I../common -o $(BIN_VECTOR_M8) $(SRC_M8)
	
clean:
	rm -f bin/*.dump; \
	rm -f bin/*.exe;
