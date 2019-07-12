
import os
import time
import multiprocessing as mp
import numpy as np
import lib



def display_error(fn, name, steps=1000, dt=1e-3, bodies=101, threads=1):
    # compare the result to the pure python result 
    w1 = lib.World(10, threads=threads, dt=dt)
    w2 = w1.copy()
    lib.evolve(w1, 1024)
    fn(w2, 1024)
    def f(name):
        wA = w1
        wB = w2
        dvmax = eval("np.absolute(wA.{0} - wB.{0}).max()".format(name))
        print("    max(delta {0}): {1:2.2}".format(name, dvmax))
    f("r")
    f("v")
    f("F")



def timer(fn, name, steps=1000, dt=1e-3, bodies=101, threads=1):
    print "\n"

    # measure function execution speed
    w = lib.World(bodies, threads=threads, dt=dt)
    t0 = time.time()
    fn(w, steps)
    t1 = time.time()
    print "{0} ({1}): {2} steps/sec".format(
        name, threads, int(steps / (t1 - t0)))
    
    # compare the result to the pure python result 
    display_error(fn, name, steps=1000, dt=1e-3, bodies=101, threads=1):

    

if __name__ == "__main__":
    timer(lib.evolve, "Python", steps=1000)
    timer(lib.evolve_c_simple1, "C Simple 1", steps=32000)
    timer(lib.evolve_c_simple2, "C Simple 2", steps=32000)
    
