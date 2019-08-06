
import numpy as np
import gridsearch1, gridsearch2

from copy import deepcopy
from mtuq.util import example_data as examples


class mtuq_bw(object):
    def __init__(self, npts_per_axis=10):

        self.data_list = deepcopy(examples.data_bw)
        self.greens_list = deepcopy(examples.greens_bw)

        self.data = examples.data_bw.as_array()
        self.greens = examples.greens_bw.as_array()
        self.origin = examples.origin

        self.mt = examples.DoubleCoupleGridRegular(
            npts_per_axis=npts_per_axis,
            magnitude=4.5)

        self.process_data = examples.process_bw
        self.misfit = examples.misfit_bw


class mtuq_sw(object):
    def __init__(self, npts_per_axis=10):

        self.data_list = deepcopy(examples.data_sw)
        self.greens_list = deepcopy(examples.greens_sw)

        self.data = examples.data_sw.as_array()
        self.greens = examples.greens_sw.as_array()
        self.origin = examples.origin

        self.mt = examples.DoubleCoupleGridRegular(
            npts_per_axis=npts_per_axis, 
            magnitude=4.5)

        self.process_data = examples.process_sw
        self.misfit = examples.misfit_sw


class mockup(object):
    """ structure that holds sample data
    """
    def __init__(self, nc, ns, nt, ngf, nmt):
        self.nc = nc
        self.ns = ns
        self.nt = nt 
        self.ngf = ngf
        self.nmt = nmt
        self.allocate()

    def allocate(self):
        self.data  = np.random.rand((self.nc,self.ns,self.nt))
        self.greens  = np.random.rand((self.ngf,self.nc,self.ns,self.nt))
        self.mt  = np.random.rand((self.nmt,self.ngf))

    def copy(self):
        return deepcopy(self)


class mockup_bw(mockup):
    """ structure that holds sample data
    """
    def __init__(self, nmt=1000):
        self.nc = 2
        self.ns = 20
        self.nt = 750
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
        self.ngf = 6
        self.nmt = nmt
        self.allocate()


def run_gridsearch(w):
    examples.grid_search(w.data_list, w.greens_list, w.misfit, w.origin, w.mt, verbose=False)


def run_gridsearch1(w):
    gridsearch1.gridsearch(w.data, w.greens, w.mt)


def run_gridsearch2(w):
    gridsearch2.gridsearch(w.data, w.greens, w.mt)


