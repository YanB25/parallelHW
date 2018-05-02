all: cacheLineOptimize.out NoneCacheLineOptimize.out
cacheLineOptimize.out: test.cpp
	g++ test.cpp -o $@ -std=c++11 -fopenmp -D cacheOptimize
NoneCacheLineOptimize.out: test.cpp
	g++ test.cpp -o $@ -std=c++11 -fopenmp -D NoneCacheOptimize



run_c:
	./cacheLineOptimize.out 2>&1 | tee log_cache
run_nc:
	./NoneCacheLineOptimize.out 2>&1 | tee log_noneCache

clean:
	find . -name "*.out" -delete