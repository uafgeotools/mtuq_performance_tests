
import os
import time
import numpy as np

from examples.gridsearch import mockup_sw, mockup_bw, mtuq_sw, mtuq_bw, run_gridsearch, run_gridsearch1, run_gridsearch2


def display_result(results):
    print(results.argmin(),results.min())



def timer(grid_search, problem, name, nmt=1000):
    print '\n%s' % name
    # measure function execution speed
    start_time = time.time()
    grid_search(problem)
    elapsed_time = time.time() - start_time
    return elapsed_time
    
    

if __name__ == "__main__":
    t0 = timer(run_gridsearch, mtuq_sw(npts_per_axis=20), "Pure python grid search")
    print 'elapsed time: %f' % t0

    t1 = timer(run_gridsearch1, mockup_bw(nmt=8000), "Python/C grid search 1")
    print 'elapsed time: %f' % t1
    print '%.1fx faster than pure python' % (t0/t1)

    t2 = timer(run_gridsearch2, mockup_bw(nmt=8000), "Python/C grid search 2")
    print 'elapsed time: %f' % t2
    print '%.1fx faster than pure python' % (t0/t2)


    t0 = timer(run_gridsearch, mtuq_bw(npts_per_axis=10), "Pure python grid search")
    print 'elapsed time: %f' % t0

    t1 = timer(run_gridsearch1, mockup_sw(nmt=1000), "Python/C grid search 1")
    print 'elapsed time: %f' % t1
    print '%.1fx faster than pure python' % (t0/t1)

    t2 = timer(run_gridsearch2, mockup_sw(nmt=1000), "Python/C grid search 2")
    print 'elapsed time: %f' % t2
    print '%.1fx faster than pure python' % (t0/t2)

