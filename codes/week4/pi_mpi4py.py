#pi_mpi4py.py
import time
from mpi4py import MPI

def loop(num_steps, begin, end):
    step = 1.0/num_steps
    sum = 0
    for i in range(begin, end):
        x= (i+0.5)*step
        sum = sum + 4.0/(1.0+x*x)
    return sum

def Pi(num_steps):
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    begin = time.time()
    num_steps_chunk = num_steps/size
    local_sum = loop(num_steps, ..., ...)
    #print("local sum of processor %d is %f" %(rank, local_sum))
    sum = ...
    end = time.time()

    if rank == 0:
        pi = sum/num_steps
        elapsed = end-begin
        print("Pi with %d steps is %f in %f secs" %(num_steps, pi, elapsed))

if __name__ == '__main__':
    Pi(100000000)
