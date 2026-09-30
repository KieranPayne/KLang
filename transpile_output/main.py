import time
def fib(x):
    if x < 2:
        return 1
    return fib(x-2) + fib(x-1)
start_time = time.time()
print(fib(40))
print(time.time() - start_time)
