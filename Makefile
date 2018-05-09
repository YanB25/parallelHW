all: cacheLineOptimize.out NoneCacheLineOptimize.out dummy.out
cacheLineOptimize.out: matrix.cpp
	g++ $^ -o $@ -std=c++11 -fopenmp -D cacheOptimize
NoneCacheLineOptimize.out: matrix.cpp
	g++ $^ -o $@ -std=c++11 -fopenmp -D NoneCacheOptimize
dummy.out : schedule.cpp
	g++ $^ -o $@ -std=c++11 -fopenmp


run_c:
	./cacheLineOptimize.out 2>&1 | tee log/log_cache
run_nc:
	./NoneCacheLineOptimize.out 2>&1 | tee log/log_noneCache
run_dummy:
	./dummy.out 2>&1 | tee log/log_dummy
clean:
	find . -name "*.out" -delete