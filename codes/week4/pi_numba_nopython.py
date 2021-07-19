#pi_numba.py
import time
from numba import jit

@jit(nopython=True)
def loop(num_steps):
    step = 1.0/num_steps
    sum = 0
    for i in range(num_steps):
        x= (i+0.5)*step
        sum = sum + 4.0/(1.0+x*x)
    return sum

def Pi(num_steps):
    begin = time.time()
    sum = loop(num_steps)
    pi = sum/num_steps
    end = time.time()
    elapsed = end-begin
    print("(Before compilation) Pi with %d steps is %f in %f secs" %(num_steps, pi, elapsed))

    begin = time.time()
    sum = loop(num_steps)
    pi = sum/num_steps
    end = time.time()
    elapsed = end-begin
    print("(After compilation) Pi with %d steps is %f in %f secs" %(num_steps, pi, elapsed))

if __name__ == '__main__':
    Pi(100000000)
