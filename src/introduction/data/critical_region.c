#include <stdio.h>
#include <omp.h>

int main() {
  // shared variable
    int sum_shared = 0;
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        // private variable
        int sum_local = 0;
        #pragma omp for nowait
        for (int i = 0; i < 10; ++i) {
            sum_local += i;
        }
        // critical section to update the shared variable
        printf("Thread %d, local_sum = %d\n", omp_get_thread_num(), sum_local);
        #pragma omp critical
        {
            sum_shared += sum_local;
        }
    }
    printf("total sum: %d\n", sum_shared);
    return 0;
}