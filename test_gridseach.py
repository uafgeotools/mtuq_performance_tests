
import os
import time
import multiprocessing as mp
import numpy as np
import lib



def display_result(results):
    print(results.argmin(),results.min())



def timer(fn, name, nmt=1000):
    print "\n"

    # measure function execution speed
    pass
    
    # display result
    pass

    

if __name__ == "__main__":
    timer(examples.gridsearch1, "Grid Search 1", nmt=32000)
    timer(examples.gridsearch2, "Grid Search 2", nmt=32000)

