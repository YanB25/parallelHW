all: build/cacheLineOptimize.out build/NoneCacheLineOptimize.out build/dummy.out
build/cacheLineOptimize.out: matrix.cpp
	g++ $^ -o $@ -std=c++11 -fopenmp -D cacheOptimize
build/NoneCacheLineOptimize.out: matrix.cpp
	g++ $^ -o $@ -std=c++11 -fopenmp -D NoneCacheOptimize
build/dummy.out : schedule.cpp
	g++ $^ -o $@ -std=c++11 -fopenmp


run_c:
	./build/cacheLineOptimize.out 2>&1 | tee log/cache.log
run_nc:
	./build/NoneCacheLineOptimize.out 2>&1 | tee log/noneCache.log
run_dummy:
	./build/dummy.out 2>&1 | tee log/dummy.log
clean:
	find . -name "*.out" -delete
clean_LOG:
	find . -name ".log" -delete