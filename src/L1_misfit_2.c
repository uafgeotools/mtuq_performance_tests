
#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>

// Forward function declaration.
static PyObject *misfit(PyObject *self, PyObject *args); 

// Boilerplate: method list.
static PyMethodDef methods[] = {
  { "misfit", misfit, METH_VARARGS, "Doc string."},
  { NULL, NULL, 0, NULL } /* Sentinel */
};

// Boilerplate: Module initialization.
PyMODINIT_FUNC initL1_misfit_2(void) {
  (void) Py_InitModule("L1_misfit_2", methods);
  import_array();
}

/*****************************************************************************
 array access macros
 *****************************************************************************/
#define data(i0,i1,i2) (*(npy_float64*)((PyArray_DATA(data) +                \
                                (i0) * PyArray_STRIDES(data)[0] +            \
                                (i1) * PyArray_STRIDES(data)[1] +            \
                                (i2) * PyArray_STRIDES(data)[2] )))

#define greens(i0,i1) (*(npy_float64*)((PyArray_DATA(greens) +               \
                                (i0) * PyArray_STRIDES(greens)[0] +          \
                                (i1) * PyArray_STRIDES(greens)[3] )))

#define mt(i0,i1) (*(npy_float64*)((PyArray_DATA(mt) +                       \
                                (i0) * PyArray_STRIDES(mt)[0] +              \
                                (i1) * PyArray_STRIDES(mt)[1] )))


#define synthetics(i1) (*(npy_float64*)((PyArray_DATA(synthetics) +          \
                                (i1) * PyArray_STRIDES(synthetics)[2] )))


/*****************************************************************************
 misfit
 *****************************************************************************/
static PyObject *misfit(PyObject *self, PyObject *args) {

  PyArrayObject *data, *greens, *mt;
  npy_int64 NC, NS, NT, NGF, NMT;
  npy_int64 i0,i1,i2,i3,k0,k1,i;




  // parse arguments
  if (!PyArg_ParseTuple(args, "O!O!O!",
                        &PyArray_Type, &data,
                        &PyArray_Type, &greens,
                        &PyArray_Type, &mt)) {
    return NULL;
  }

  NC = PyArray_SHAPE(data)[0];
  NS = PyArray_SHAPE(data)[1];
  NT = PyArray_SHAPE(data)[2];
  NGF = PyArray_SHAPE(greens)[1];
  NMT = PyArray_SHAPE(mt)[0];

  printf("number of components:  %d\n", NC);
  printf("number of stations:  %d\n", NS);
  printf("number of time samples:  %d\n", NT);
  printf("number of Green's functions:  %d\n", NGF);
  printf("number of moment tensors:  %d\n", NMT);

  printf("greens,0 %d\n", (int) PyArray_STRIDES(greens)[0]);
  printf("greens,1 %d\n", (int) PyArray_STRIDES(greens)[1]);
  printf("greens,2 %d\n", (int) PyArray_STRIDES(greens)[2]);
  printf("greens,3 %d\n", (int) PyArray_STRIDES(greens)[3]);

  int nd = 3;
  npy_intp dims[] = {NC,NS,NT};
  PyObject *synthetics = PyArray_SimpleNew(nd, dims, NPY_DOUBLE);

  printf("synthetics,0 %d\n", (int) PyArray_STRIDES(synthetics)[0]);
  printf("synthetics,1 %d\n", (int) PyArray_STRIDES(synthetics)[1]);
  printf("synthetics,2 %d\n", (int) PyArray_STRIDES(synthetics)[2]);

    npy_float64 mti;


  for(i = 0;  i<NMT; ++i) {
    for (i1=0; i1<NC*NS*NT; i1++) {
        synthetics(i1) = (npy_float64) 0.;
    }

    for (i0=0; i0<NGF; i0++) {
    mti = mt(i, i0);
    for (i1=0; i1<NC*NS*NT; i1++) {
        synthetics(i1) += greens(i0,i1) * mti;
    }
    }


  }

  Py_RETURN_NONE;
}

