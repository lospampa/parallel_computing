CC=gcc
CFLAGS= #for openmp code, include the flag -fopenmp

hello:
	$(CC) hello.c -o hello $(CFLAGS)

run:
	./hello
	# if you want to change the number of running threads: export OMP_NUM_THREADS=x, where x is the number of threads.

clean:
	rm hello