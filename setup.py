#!/usr/bin/env python

from distutils.core import setup, Extension
import numpy

setup(
      ext_modules = [
          Extension(
              'examples.L1_misfit_1', ['src/L1_misfit_1.c'],
              include_dirs=[numpy.get_include()],
              extra_compile_args=["-Ofast", "-march=native"]),
          Extension(
              'examples.L1_misfit_2', ['src/L1_misfit_2.c'],
              include_dirs=[numpy.get_include()],
              extra_compile_args=["-Ofast", "-march=native"]),
          Extension(
              'examples.L2_misfit_1', ['src/L2_misfit_1.c'],
              include_dirs=[numpy.get_include()],
              extra_compile_args=["-Ofast", "-march=native"]),
      ], 
      
)
