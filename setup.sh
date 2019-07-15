#!/bin/bash

rm examples/*.so
python ./setup.py build_ext --inplace

