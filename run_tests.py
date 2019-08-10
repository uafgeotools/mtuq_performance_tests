#!/usr/bin/env python

import os
import time
import numpy as np

from examples import mockup_sw, mockup_bw, mtuq_sw, mtuq_bw,\
    L1_misfit_1, L2_misfit_1,\
    run_mockup_L1, run_mockup_L2


def display_result(results):
    print(results.argmin(),results.min())



def timer(wrapper, misfit, data):
    # measure function execution speed
    start_time = time.time()
    wrapper(misfit, data)
    elapsed_time = time.time() - start_time
    return elapsed_time
    
    

if __name__ == "__main__":
    #t0 = timer(run_mtuq, mtuq_bw(npts_per_axis=20))
    #print 'elapsed time: %f' % t0

    #t1 = timer(run_mockup_L1, L1_misfit_1.misfit, mockup_bw(nmt=8000))
    #print 'elapsed time: %f' % t1
    #print '%.1fx faster than pure python' % (t0/t1)

    #t2 = timer(run_mockup_L1, L1_misfit_2.misfit, mockup_bw(nmt=8000))
    #print 'elapsed time: %f' % t2
    #print '%.1fx faster than pure python' % (t0/t2)


    #t0 = timer(run_mtuq, mtuq_sw(npts_per_axis=10))
    #print 'elapsed time: %f' % t0

    #t1 = timer(run_mockup_L2, L2_misfit_1.misfit, mockup_sw(nmt=1000))
    #print 'elapsed time: %f' % t1
    #print '%.1fx faster than pure python' % (t0/t1)

    #t2 = timer(run_mockup_L2, L2_misfit_2.misfit, mockup_sw(nmt=1000))
    #print 'elapsed time: %f' % t2
    #print '%.1fx faster than pure python' % (t0/t2)

    mockup_sw(nmt=1000)

    t2 = timer(run_mockup_L2, L2_misfit_1.misfit, mockup_sw(nmt=1000))
    print 'elapsed time: %f' % t2
    #print '%.1fx faster than pure python' % (t0/t2)

