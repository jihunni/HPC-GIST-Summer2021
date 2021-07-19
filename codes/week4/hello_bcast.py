#hello_bcast.py
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

if rank == 0:
    data = {'key1' : [7, 2.72, 2+3j],
            'key2' : ( 'abc', 'xyz')}
else:
    data = None
print("Before Bcast: Proc %d has %s" %(rank, data))
data = comm.bcast(data, root=0)
print("After Bcast: Proc %d has %s" %(rank, data))

