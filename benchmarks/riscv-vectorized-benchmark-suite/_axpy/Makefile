#makefile

start:
	rm bin/*.*

serial:
	echo "serial"
	gcc -march=rv64g -O2 -c -o src/utils.o src/utils.c
	gcc -march=rv64g -O2 -c -o src/axpy.o src/axpy.c
	gcc -march=rv64g -O2 -c -o src/main.o src/main.c
	gcc -march=rv64g -O2 -o bin/axpy_serial.exe src/*.o -lm
	rm src/*.o
	
vector:
	echo "vector"
	gcc -march=rv64gcv -DUSE_RISCV_VECTOR  -O2 -c -o src/axpy.o src/axpy.c
	gcc -march=rv64gcv -DUSE_RISCV_VECTOR  -O2 -c -o src/main.o src/main.c
	gcc -march=rv64gcv -DUSE_RISCV_VECTOR  -O2 -c -o src/utils.o src/utils.c
	gcc -march=rv64gcv -DUSE_RISCV_VECTOR  -O2 -o bin/axpy_vector.exe src/*.o -lm
	rm src/*.o

vector_m8:
	echo "vector_m8"
	gcc -march=rv64gcv -DUSE_RISCV_VECTOR  -O2 -c -o src/axpy_m8.o src/axpy_m8.c
	gcc -march=rv64gcv -DUSE_RISCV_VECTOR  -O2 -c -o src/main.o src/main.c
	gcc -march=rv64gcv -DUSE_RISCV_VECTOR  -O2 -c -o src/utils.o src/utils.c
	gcc -march=rv64gcv -DUSE_RISCV_VECTOR  -O2 -o bin/axpy_vector_m8.exe src/*.o -lm
	rm src/*.o

clean:
	rm bin/*.exe;
