
import numpy as np
import gridsearch1, gridsearch2

from copy import deepcopy
from mtuq.util import example_data as examples


class mtuq_bw(object):
    def __init__(self, npts_per_axis=10):
        self.data = deepcopy(examples.data_bw)
        self.greens = deepcopy(examples.greens_bw)

        self.origin = deepcopy(examples.origin)

        self.mt = examples.DoubleCoupleGridRegular(
            npts_per_axis=npts_per_axis,
            magnitude=4.5)

        self.process_data = examples.process_bw
        self.misfit = examples.misfit_bw


class mtuq_sw(object):
    def __init__(self, npts_per_axis=10):
        self.data = deepcopy(examples.data_sw)
        self.greens = deepcopy(examples.greens_sw)

        self.origin = deepcopy(examples.origin)

        self.mt = examples.DoubleCoupleGridRegular(
            npts_per_axis=npts_per_axis, 
            magnitude=4.5)

        self.process_data = examples.process_sw
        self.misfit = examples.misfit_sw


class mockup(object):
    """ structure that holds sample data
    """
    def __init__(self, nc, ns, nt, npad, ngf, nmt):
        self.nc = nc
        self.ns = ns
        self.nt = nt 
        self.npad = npad
        self.ngf = ngf
        self.nmt = nmt
        self.allocate()

    def allocate(self):
        self.data  = np.random.rand((self.nc,self.ns,self.nt))
        self.greens  = np.random.rand((self.ngf,self.nc,self.ns,self.nt))
        self.mt  = np.random.rand((self.nmt,self.ngf))

        self.data_data = np.random.rand((self.nc))
        self.greens_data = np.random.rand((self.nc, self.ngf, self.npad))
        self.greens_greens = np.random.rand((self.nc, self.npad, self.ngf, self.ngf))

    def copy(self):
        return deepcopy(self)


class mockup_bw(mockup):
    """ structure that holds sample data
    """
    def __init__(self, nmt=1000):
        self.nc = 2
        self.ns = 20
        self.nt = 750
        self.npad = 201
        self.npad1 = (self.npad-1)/2
        self.npad2 = (self.npad-1)/2
        self.ngf = 6
        self.nmt = nmt
        self.allocate()


class mockup_sw(mockup):
    """ structure that holds sample data
    """
    def __init__(self, nmt=1000):
        self.nc = 3
        self.ns = 20
        self.nt = 7500
        self.npad = 2001.
        self.ngf = 6
        self.nmt = nmt
        self.allocate()


def run_mtuq(mtuq, optimization_level=1):
    mtuq.misfit(mtuq.data, mtuq.greens, mtuq.misfit, mtuq.origin, mtuq.mt, verbose=False, optimization_level=optimization_level)


def run_mockup_L1(misfit, mockup):
    misfit(mockup.data, mockup.greens, mockup.mt)

def run_mockup_L2(misfit, mockup):
    misfit(mockup.data, mockup.greens, mockup.mt,
    mockup.data_data, mockup.greens_data, mockup.greens_greens
    mockup.npad1, mockup.npad2)



