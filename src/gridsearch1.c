
#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>

// Forward function declaration.
static PyObject *grid_search1(PyObject *self, PyObject *args); 

// Boilerplate: method list.
static PyMethodDef methods[] = {
  { "grid_search1", grid_search1, METH_VARARGS, "Doc string."},
  { NULL, NULL, 0, NULL } /* Sentinel */
};

// Boilerplate: Module initialization.
PyMODINIT_FUNC initgrid_search1(void) {
  (void) Py_InitModule("grid_search1", methods);
  import_array();
}

/*****************************************************************************
 array access macros
 *****************************************************************************/
#define greens(x0) (*(npy_float64*)((PyArray_DATA(greens) +                \
                                (x0) * PyArray_STRIDES(greens)[0])))

#define mt(x0) (*(npy_float64*)((PyArray_DATA(mt) +                \
                                (x0) * PyArray_STRIDES(mt)[0])))

/*****************************************************************************
 get_synthetics
 *****************************************************************************/
static inline void get_synthetics(
                             npy_int64 NC,
                             npy_int64 NS,
                             npy_int64 NTP,
                             npy_int64 NF,
                             PyArrayObject *greens,
                             npy_float64 *synthetics,
                             PyArrayObject *mt) {
    npy_int64 i, j;
  
    for (j=0 ; j<NC*NS*NTP; j++) {
        synthetics[j] = 0.;
    }

    for (i=0 ; i<NF; i++) {
        for (j=0 ; j<NC*NS*NTP; j++) {
            synthetics[j] += greens(i*NC*NS*NTP + j) * mt(i);
        }
    }

  
}

/*****************************************************************************
 grid_search1
 *****************************************************************************/
static PyObject *grid_search1(PyObject *self, PyObject *args) {

  npy_int64 NC, NS, NTP, NF, NM;
  PyArrayObject *data, *greens, *mt;
  npy_int64 i;


  // parse arguments
  if (!PyArg_ParseTuple(args, "lllllO!O!O!",
                        &NC,
                        &NS,
                        &NTP,
                        &NF,
                        &NM,
                        &PyArray_Type, &data,
                        &PyArray_Type, &greens,
                        &PyArray_Type, &mt)) {
    return NULL;
  }


  // ultimately, we want to use 
  // PyObject *PyArray_SimpleNew(int nd, npy_intp* dims, int typenum)
  npy_float64 *synthetics;
  synthetics = (npy_float64 *) malloc(NC*NS*NTP);

  for(i = 0;  i<NM; ++i) {
    get_synthetics(NC, NS, NTP, NF, greens, synthetics, mt);
  }

  Py_RETURN_NONE;
}
