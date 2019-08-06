#!/usr/bin/env python

from distutils.core import setup, Extension
import numpy

setup(
      ext_modules = [
          Extension(
              'examples.gridsearch1', ['src/gridsearch1.c'],
              include_dirs=[numpy.get_include()],
              extra_compile_args=["-Ofast", "-march=native"]),
          Extension(
              'examples.gridsearch2', ['src/gridsearch2.c'],
              include_dirs=[numpy.get_include()],
              extra_compile_args=["-Ofast", "-march=native"]),
      ], 
      
)
