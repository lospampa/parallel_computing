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

---

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

Within a ```parallel``` region, thread numbers uniquely identify each thread (from 0 to the number of created threads - 1). A thread can obtain its own thread number by calling the function ```omp_get_thread_num()```. A thread can also get the total number of threads that are running the ```parallel``` region through the function ```omp_get_num_threads()```.

If a thread in a ```parallel``` region encounters another ```#pragma omp parallel``` directive, it creates a new team of threads. 

An implicit barrier occurs at the end of a ```parallel``` region to join all threads. After the end of such region, only the master thread of the team resumes execution.


#### Exercise 1: Parallelizing the first code

For this exercise, you must apply the ```#pragma omp parallel```to parallelize the code [hello.c](src/hello/hello.c). For that, follow the steps below:
1. In the terminal, go to the directory by typing : ```cd /src/hello```
2. Compile the sequential code and execute: ```make && make run```. The output of this execution will be a single message 

        Hello World

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
2. To use the function, you need to write it before the parallel constructor.
3. To use the clause, you just need to write it in the end of the ```#pragma omp parallel``` directive.

After trying the different ways of defining the number of threads, take a time to do the following:
1. Create more than one parallel region in the source code and identify each parallel region with a different printf. 
2. What happens when the number of threads is defined via environment variable?
3. What happens when the number of threads is defined via function? Try using this function with different number of threads right before each parallel region.
4. What happens when the number of threads is defined via clause? Try using different values for each parallel region.
5. Is there a precedence when defining the number of threads?

#### Exercise 3: What is wrong with this code?

In this exercise, you will run an application that performs the addVectors operation in parallel. This application is parallelized with only the ```#pragma omp parallel```directive. You can find the source code [here](src/addVectors/addVectors.c). To run, do the following steps:
1. In the terminal, go to the folder addVectors: ```cd src/addVectors/```
2. To compile: ```make```
3. To run: ```make run```
4. What is the output? Why all threads are computing the same indices of each array?
5. Take a time to understand what is happening in this exercise. Also, remember that the ```#pragma omp parallel``` directive only creates a team of threads. That is, it does not divide the workload (iterations) between the threads. 
6. We will cover the worksharing constructor in the next chapter.


### **3.1.2 Clauses**

#### **3.1.2.1 private(list)**

This clause declares the scope of the data variables in ```list``` to be private to each thread during the parallel region. Data variables in list are separated by commas, as exemplified below for variables ```a``` and ```b``` .

```
int a, b, c;
#pragma omp parallel private(a, b)
{
    a = omp_get_thread_num();
    b = srand();
    printf("thread id %d generated a random value %d\n", a, b);
}

```


#### **3.1.2.2 shared(list)**

When this clause is employed, the scope of the comma-separated data variables in list are defined to be shared across all threads. By default, all variables are shared among the threads. In the example below, the array ```A``` is declared to be shared.

```
int A[N];
#pragma omp parallel shared(A)
{
    int sum_per_thread = 0;
    for(int i = 0; i < N; i++){
        sum_per_thread += A[i] * omp_get_thread_num();
    }    
}
```

#### **3.1.2.3 firstprivate(list)**

When this clause is applied to a parallel region, the scope of the data variables in ```list``` to be private to each thread. Different from the ```private``` clause, each new private variable is initialized with the value of the original variable as if there was an implied declaration within the statement block. Also, data variables in list are separated by commas. In the example below, the printed values for ```a``` and ```b``` should be 100 and 10, respectively.

```
int a = 100, b = 10, c;
#pragma omp parallel private(c) firstprivate(a, b)
{
    printf("thread id %d with values a (%d), b(%d) and c(%d)\n", omp_get_thread_num(), a, b, c);
}

```

#### **3.1.2.4 num_threads(int n)**

When this clause is employed, the value of ```n``` is an integer expression that specifies the number of threads to use for the parallel region. If dynamic adjustment of the number of threads is also enabled, then ```n``` specifies the maximum number of threads to be used. In the example below, 16 threads should be created and each one should print its id along with the number 16.

```
int nThreads = 16;
int idThread, totalThreads;
#pragma omp parallel num_threads(nThreads) private(idThread) shared(totalThreads)
{
    idThread = omp_get_thread_num();
    totalThreads = omp_get_num_threads();
    printf("I am thread %d from a total of %d threads\n", idThread, totalThreads);       
}
```


#### **3.1.2.5 reduction(operator: list)**

This clause performs a reduction on all scalar variables in ```list``` using the specified ```operator```. Reduction variables in list are separated by commas. When it is employed, a private copy of each variable in list is created for each thread. At the end of the statement block, the final values of all private copies of the reduction variable are combined in a manner appropriate to the operator, and the result is placed back in the original value of the shared reduction variable. For example, when the max operator is specified, the original reduction variable value combines with the final values of the private copies by using the following expression:

```
    original_reduction_variable = original_reduction_variable < private_copy ?
    private_copy : original_reduction_variable;
```

When the programming language is C or C++, the following operators can be used.
 
<table ><tr><th > Identifier	<th><th>   Initializer <th><th>   Combiner <tr><tr>
<tr><td> +	                <td><td>   omp_priv = 0	            <td><td>    omp_out += omp_in <tr><tr>
<tr><td> -	                <td><td>   omp_priv = 0	            <td><td>    omp_out += omp_in <tr><tr>
<tr><td> *	                <td><td>   omp_priv = 1	            <td><td>    omp_out *= omp_in <tr><tr>
<tr><td> &	                <td><td>   omp_priv = ~ 0	        <td><td>    omp_out &= omp_in <tr><tr>
<tr><td> |	                <td><td>   omp_priv = 0	            <td><td>    omp_out |= omp_in <tr><tr>
<tr><td> ^	                <td><td>   omp_priv = 0	            <td><td>    omp_out ^= omp_in <tr><tr>
<tr><td> &&	            <td><td>   omp_priv = 1	                <td><td>    omp_out = omp_in && omp_out <tr><tr>
<tr><td> ||	            <td><td>   omp_priv = 0	                <td><td>    omp_out = omp_in || omp_out <tr><tr>
<tr><td> max	            <td><td>   omp_priv = Least representable number in the reduction list item type	<td><td>    omp_out = omp_in > omp_out ? omp_in : omp_out <tr><tr>
<tr><td> min	            <td><td>   omp_priv = Largest representable number in the reduction list item type	<td><td>    omp_out = omp_in < omp_out ? omp_in : omp_out <td><tr><table>

The following example shows the reduction ```+``` operation over the variable ```sum```.

```
int sum=0;
#pragma omp parallel reduction(+:sum)
{
    int idThread = omp_get_thread_num();
    sum += idThread;    
}
printf("The sum of all thread ids is: %d\n", sum);       
```



---

### **3.2 Work-sharing constructs**

A work-sharing construct delegates the execution of the corresponding region among the threads within its designated thread team. Threads execute portions of the parallel region. 

### **3.2.1 \#pragma omp for**

The ```omp for``` directive informs the compiler to distribute loop iterations within the team of threads that reaches this constructor. The syntax is ```#pragma omp for clauses```, where the clauses are optional and will be discussed next.

A simple example can be seen below, where the number of iterations ```N``` will be divided among the threads that are created in the parallel directive. In this scenario, each created thread will be responsible for executing a different set of iterations.

```
#pragma omp parallel
{
    #pragma omp for
    for(int i = 0; i < N; i++){
        \* loop operations in parallel *\
    }
}

```

The ```pragma omp for``` directive can be combined with the ```pragma omp parallel```. In this scenario, the following code has the very same effect as the previous one.

```
#pragma omp parallel for
for(int i = 0; i < N; i++){
    \* loop operations in parallel *\
}

```

#### Exercise 4: Applying the Work-sharing constructor for the addVectors code.

In this exercise, you will modify the [here](src/addVectors/addVectors.c) application so that the iterations of the loop are distributed among the threads in the parallel region. For that, do the following steps:
1. In the terminal, go to the folder addVectors: ```cd src/addVectors/```
2. Clean the folder with ```make clean```
3. After editing and saving the code, compile: ```make```
4. To run: ```make run```
5. What is the output? Are the threads computing different indices of each array?
6. Change the number of threads. What happens? 


#### **3.2.1.1 schedule(type) clause**


#### **3.2.1.2 ordered clause**


#### **3.2.1.3 reduction(operator: list) clause**


#### **3.2.1.4 collapse(n) clause**

