import time

def Pi(num_steps):
    begin = time.time()
    step = 1.0/num_steps
    sum = 0
    for i in range(num_steps):
        x= (i+0.5)*step
        sum = sum + 4.0/(1.0+x*x)
        pi = step * sum
    end = time.time()
    elapsed = end-begin
    print("Pi with %d steps is %f in %f secs" %(num_steps, pi, elapsed))

if __name__ == '__main__':
    Pi(100000000)

