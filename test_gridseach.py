
import os
import time
import numpy as np

from examples.gridsearch import World, run_gridsearch1, run_gridsearch2


def display_result(results):
    print(results.argmin(),results.min())



def timer(fn, name, nmt=1000):
    w = World()
    print "\n"

    # measure function execution speed
    fn(w)
    
    # display result
    pass

    

if __name__ == "__main__":
    #timer(run_gridsearch1, "Grid Search 1", nmt=32000)
    timer(run_gridsearch2, "Grid Search 2", nmt=32000)

