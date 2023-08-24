# **Parallel Computing**

# **OpenMP**

OpenMP (Open Multi-Processing) is an application programming interface (API) that supports multi-platform shared-memory multiprocessing programming in C, C++, and Fortran. It consists of a set of compiler #pragmas that control how the program works. The pragmas are designed so that even if the compiler does not support them, the program will still yield correct behavior, but without any parallelism.


## **1 Execution Model**

The OpenMP API uses the fork-join model of parallel execution. Multiple threads of execution perform tasks deﬁned implicitly or explicitly by OpenMP directives. The OpenMP API is intended to support programs that will execute correctly both as parallel programs (multiple threads of execution and a full OpenMP support library) and as sequential programs (directives ignored and a simple OpenMP stubs library). However, a conforming OpenMP program may execute correctly as a parallel program but not as a sequential program, or may produce diﬀerent results when executed as a parallel program compared to when it is executed as a sequential program. Further, using diﬀerent numbers of threads may result in diﬀerent numeric results because of changes in the association of numeric operations. For example, a serial addition reduction may have a diﬀerent pattern of addition associations than a parallel reduction. These diﬀerent associations may change the results of ﬂoating-point addition.

An OpenMP program begins as a single thread of execution, called an initial thread. An initial thread executes sequentially, as if the code encountered is part of an implicit task region, called an initial task region, that is generated by the implicit parallel region surrounding the whole program.

## **2 OpenMP syntax**

All OpenMP constructs in C and C++ are indicated with a ```#pragma omp``` followed by parameters, ending in a newline. The pragma usually applies only into the statement immediately following it, except for the ```barrier``` and ```flush``` commands, which do not have associated statements.


### **2.1 Directive Format**

OpenMP directives are speciﬁed with a directive-speciﬁcation. A directive-speciﬁcation consists of the directive-speciﬁer and any clauses that may optionally be associated with the OpenMP directive. An OpenMP directive may be specified as a pragma directive:
  
```
#pragma omp directive-specification new-line
```

or a pragma operator:

```
_Pragma("omp directive-specification")
```

### **2.2 Clause Format**

OpenMP clauses are speciﬁed as part of a directive-speciﬁcation. Clauses are optional and, thus, may be omitted from a directive-speciﬁcation unless otherwise speciﬁed. The order in which clauses appear on directives is not signiﬁcant unless otherwise speciﬁed.


## **3 Exploiting Parallelism**

This section discuss constructs for generating and controlling parallelism.


### **3.1 The Parallel construct**

The parallel construct starts a parallel block. It creates a *team* of N threads (where N is determined at runtime, usually from the number of CPU cores), all of which execute the next statement (or the next block). After the statement, the threads join back into one.


```
int main(int argc, char **argv){
    \* sequential region *\

    #pragma omp parallel
    {
        \* parallel region *\
    }

    \* sequential region *\

    return 0;
}
```

#### Exercise 1: Parallelizing the first code

For this exercise, you must apply the ```#pragma omp parallel```to parallelize the code [hello.c](src/hello/hello.c). For that, follow the steps below:
1. In the terminal, go to the directory by typing : ```cd /src/hello```
2. Compile the sequential code and execute: ```make && make run```. The output of this execution will be a single message *Hello World*.
3. Parallelize the code [hello.c](src/hello/hello.c) with the OpenMP parallel constructor so that multiple *Hello World* are printed, one by each thread. Don't forget to save the modifications.
4. When step 3 is done, edit the [Makefile](src/hello/Makefile) to include the flag ```-fopenmp```. Don't forget to save the modifications.
5. Compile the OpenMP code and execute it: ```make && make run```. The output with two threads should be as follows:

       Hello World
       Hello World
       

### **3.1.1 Playing with the number of threads**

By default, the number of threads that are created to execute each parallel region matches the number of cores in the architecture. However, the user can modify this number via environment variable, function in the source code, or via clause.
1. **Environment Variable**: In the Linux terminal, you can type the following command to define the number of threads equal to 4:
    ```
    export OMP_NUM_THREADS=4
    ```
2. **Function**: Inside the code, the user can use the following function to define the number of threads equal to 4:
    ```
    omp_set_num_threads(4);
    ```
3. **Clause**: Along with the parallel construct, the user can use the following clause to define the number of threads equal to 4:
    ```
    #pragma omp parallel num_threads(4)
    ```

#### Exercise 2: Changing the number of threads

For this exercise, you must apply the previous knowledge acquired to change the number of running threads in the parallel region for the code [hello.c](src/hello/hello.c) (to execute it, you can follow the same steps as Exercise 1). 
1. To use the environment variable, you can type it directly into the terminal below or edit the Makefile.
2. To use the funtion, you need to write it before the parallel constructor.



### **3.2 teams construct**



### **3.3 simd construct**



