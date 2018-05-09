# 分布式与并行 实验报告#2
16337269 颜彬
## hw1
> Consider a simple loop that calls a function dummy containing a programmable delay. All invocations of the function are independent of the others. Partition this loop across four threas using static, dynamic and guided scheduling. Use different parameters for static and guided scheduling. Document the result of this experiment as the delay when the dummy function becomes large.
### 运行方法
``` sh
$ make
$ make run_dummy
```
### 程序介绍
在程序`dummy.out`中，定义了一个函数
```C
void dummy(double sec);
```
它的作用是延时等待`sec`秒。

程序主体部分是`for`循环，`i`为循环变量，每轮循环等待`i`秒。
如此即可产生一个每次循环时长不同的循环体。

程序并行部分的主体类似下列代码
``` C
#pragma omp parallel for schedule(static)
for (int i = 0; i < TIMES; ++i) {
    dummy(i);
}
```
### 结果展示
程序的输出如下。在`i = 0 to 20`时，
```
static schedule wall time 50.446180
guided schedule wall time 28.571732
dynamic schedule wall time 22.520642
```
可以看出`static`最慢，`guided`次之，`dynamic`最快。

## TODO: title2 here
> TODO: problem2 here

### 运行方法
``` shell
$ make
$ make run_c
# or
# $ make run_nc
```
其中`run_c`会执行经过了cache优化的矩阵乘法。`run_nc`会执行未经过cache优化的矩阵乘法。

以下展示会以`run_c`版本的代码作为例子。

### 程序介绍
并行的主体部分如下
``` C++
omp_set_dynamic(false);     // Explicitly disable dynamic teams
omp_set_num_threads(tn);
#pragma omp parallel 
{
    #pragma omp for collapse(1)
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            for (int j = 0; j < size; ++j) {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
} 
```
其中
```C++
omp_set_dynamic(false);
```
语句用于确保的确产生了n个线程用于执行下列程序（而不是被openmp优化掉）。
``` C++
omp_set_num_threads(tn);
```
语句用于设置线程数为`tn`
值得注意的是，下面两份代码是等价的。`(2)`代码完全是`(1)`代码的更简洁的写法。
``` C++
// (1)
#pragma omp parallel
{
    #pragma omp for
    for (...) {
        for (...) {
            for (...) {
                ... 
            }
        }
    }
}

// (2)
#pragma parallel omp for 
for (...) {
    for (...) {
        for (...) {
            ... 
        }
    }
}
```
其中，
``` C++
#pragma omp parallel
```
的作用是产生若干的线程。而
```C++
#pragma omp for 
```
却不会产生线程。它的作用是，把for循环拆分成不同的小任务，分配给当前存在的线程。若当前存在的线程数为1，则该语句不会有特别的作用。

程序对cache的优化在于，三个循环体的循环变量从外往内依次为`i`, `k`, `j`。下面解释这样排列循环变量的原因。

而注意到最内部的循环的语句
``` C++
R[i][j] += A[i][k] * B[k][j];
```
我们知道瓶颈不在对`R`数组的访问，而在于对`A`和`B`数组的访问。
注意到其下标索引的顺序是`i->k`, `k->j`，所以可以看出。其排序`i->k->j`可以让程序具有最高的效率。

再注意到`R[i][j]`的结果仅依赖于`A`和`B`，且`A`和`B`在程序运行的全程不会被修改。这就说明了变换`i`,`j`,`k`的相对顺序不会影响矩阵乘积的正确性。

该正确性在循环展开的讨论中也有关。

循环展开的方式是
``` C++
# pragma omp parallel for collapse(3)
```
这里的`collapse(3)`的作用是将3层for都用多线程展开（collapse)。特别地，当collpase(1)时，意味着只多线程运行外层循环。

### 结果展示
//TODO: