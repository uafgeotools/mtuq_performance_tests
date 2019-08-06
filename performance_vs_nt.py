
import os
import time
import numpy as np

from examples.gridsearch import mockup, mockup_sw, mockup_bw, mtuq_sw, mtuq_bw, run_gridsearch, run_gridsearch1, run_gridsearch2


def display_result(results):
    print(results.argmin(),results.min())



def timer(grid_search, problem, name, nmt=1000):
    print '\n%s' % name
    # measure function execution speed
    start_time = time.time()
    grid_search(problem)
    elapsed_time = time.time() - start_time
    return elapsed_time


def irange(*args):
    return range(*[int(arg) for arg in args])
    
    

if __name__ == "__main__":
    nc,ns,ngf,nmt = 3,20,6,1000

    for nt in irange(2e4,1e5,2e4):
        t = timer(run_gridsearch1, mockup(nc, ns, nt, ngf, nmt), "nt = %d" %nt)
        print 'evaluations per second: %.1e' %  (nt/t)


