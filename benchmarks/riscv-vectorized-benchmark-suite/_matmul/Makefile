#makefile

start:
	rm -f bin/*.*

serial:
	echo "serial"
	gcc -march=rv64gcv -mabi=lp64d -O3 -o bin/matmul_serial.exe src/matmul.c src/main.c

vector:
	echo "vector"
	gcc -march=rv64gcv -mabi=lp64d -DUSE_RISCV_VECTOR -O3 -o bin/matmul_vector.exe src/matmul.c src/main.c
	gcc -march=rv64gcv -mabi=lp64d -DUSE_RISCV_VECTOR -O3 -o bin/matmul_vector_m8_T.exe src/matmul_m8_T.c src/main_T.c	
	gcc -march=rv64gcv -mabi=lp64d -DUSE_RISCV_VECTOR -O3 -o bin/matmul_vector_m1_T.exe src/matmul_m1_T.c src/main_T.c

clean:
	rm -f bin/*.dump; \
	rm -f bin/*.exe;
