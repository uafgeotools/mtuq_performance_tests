#!/usr/bin/env python

import numpy as np
import time


def get_synthetics(greens, mt):
    return np.dot(greens, mt)


try:
    from numba import jit
    @jit(nopython=True)
    def get_synthetics_numba(greens, mt):
        return np.dot(greens, mt)
    _numba = True
except:
    print 'numba not installed'
    _numba = False



if __name__=='__main__':


    # number of components
    NC = 2

    # number of stations
    NS = 20

    # number of time samples
    NT = 950

    # number of Green's functions per component
    NF = 6

    # number of time shift groups
    NG = 2

    # number of depths
    ND = 1

    # number of moment tensors
    NM = 5000

    # length of padding
    NP = 201

    # length of padded records
    NTP = NT + NP


    print '\nHow long does it take to generate 50,000 sets of synthetics in Python?\n'


    # using numpy, 1D numpy array to hold synthetics:\n

    greens = np.random.rand(NC*NS*NTP, NF)
    synthetics = np.random.rand(NC*NS*NTP)
    mt = np.random.rand(NM, NF)

    start_time = time.time()

    for _i in range(NM):
        get_synthetics(greens, mt[_i, :])


    _elapsed_time = time.time() - start_time

    print 'Using 1D numpy array to hold synthetics:\n  %f sec\n' % (10.*_elapsed_time)



    # using numpy, 2D numpy array to hold synthetics:\n

    greens = np.random.rand(NC*NS,NTP,NF)
    synthetics = np.random.rand(NC*NS,NTP)
    mt = np.random.rand(NM, NF)

    start_time = time.time()

    for _i in range(NM):
        get_synthetics(greens, mt[_i, :])


    _elapsed_time = time.time() - start_time


    print 'Using 2D numpy array to hold synthetics:\n  %f sec\n' % (10.*_elapsed_time)



    # using numpy, 3D numpy array to hold synthetics:\n

    greens = np.random.rand(NC,NS,NTP,NF)
    synthetics = np.random.rand(NC,NS,NTP)
    mt = np.random.rand(NM, NF)

    start_time = time.time()

    for _i in range(NM):
        get_synthetics(greens, mt[_i, :])


    _elapsed_time = time.time() - start_time

    print 'Using 3D numpy array to hold synthetics:\n  %f sec\n' % (10.*_elapsed_time)



    if not _numba:
        sys.exit()


    # using numpy, numba, 1D numpy array to hold synthetics:\n

    greens = np.random.rand(NC*NS*NTP, NF)
    synthetics = np.random.rand(NC*NS*NTP)
    mt = np.random.rand(NM, NF)

    start_time = time.time()

    for _i in range(NM):
        get_synthetics_numba(greens, mt[_i, :])


    _elapsed_time = time.time() - start_time

    print 'Using numba + 1D numpy array to hold synthetics:\n  %f sec\n' % (10.*_elapsed_time)

