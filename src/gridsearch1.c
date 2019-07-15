
#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>

// Forward function declaration.
static PyObject *gridsearch(PyObject *self, PyObject *args); 

// Boilerplate: method list.
static PyMethodDef methods[] = {
  { "gridsearch", gridsearch, METH_VARARGS, "Doc string."},
  { NULL, NULL, 0, NULL } /* Sentinel */
};

// Boilerplate: Module initialization.
PyMODINIT_FUNC initgridsearch1(void) {
  (void) Py_InitModule("gridsearch1", methods);
  import_array();
}

/*****************************************************************************
 array access macros
 *****************************************************************************/
#define data(i0,i1,i2) (*(npy_float64*)((PyArray_DATA(data) +                \
                                (i0) * PyArray_STRIDES(data)[0] +            \
                                (i1) * PyArray_STRIDES(data)[1] +            \
                                (i2) * PyArray_STRIDES(data)[2] )))

#define greens(i0,i1,i2,i3) (*(npy_float64*)((PyArray_DATA(greens) +         \
                                (i0) * PyArray_STRIDES(greens)[0] +          \
                                (i1) * PyArray_STRIDES(greens)[1] +          \
                                (i2) * PyArray_STRIDES(greens)[2] +          \
                                (i3) * PyArray_STRIDES(greens)[3] )))

#define mt(i0,i1) (*(npy_float64*)((PyArray_DATA(mt) +                       \
                                (i0) * PyArray_STRIDES(mt)[0] +              \
                                (i1) * PyArray_STRIDES(mt)[1] )))


#define synthetics(i0,i1,i2) (*(npy_float64*)((PyArray_DATA(synthetics) +    \
                                (i0) * PyArray_STRIDES(synthetics)[0] +      \
                                (i1) * PyArray_STRIDES(synthetics)[1] +      \
                                (i2) * PyArray_STRIDES(synthetics)[2] )))


/*****************************************************************************
 get_synthetics
 *****************************************************************************/
static inline void get_synthetics(
                             PyArrayObject *greens,
                             PyArrayObject *mt,
                             PyObject *synthetics,
                             npy_int64 NC,
                             npy_int64 NS,
                             npy_int64 NT,
                             npy_int64 NGF,
                             npy_int64 i) {

    npy_int64 i0,i1,i2,i3;
    npy_float64 mti;
  
    for (i0=0; i0<NC; i0++) {
    for (i1=0; i1<NS; i1++) {
    for (i2=0; i2<NT; i2++) {
        synthetics(i0,i1,i2) = 0.;
    }
    }
    }

    for (i0=0; i0<NGF; i0++) {
    mti = mt(i, i0);
    for (i1=0; i1<NC; i1++) {
    for (i2=0; i2<NS; i2++) {
    for (i3=0; i3<NT; i3++) {
        synthetics(i1,i2,i3) += greens(i0,i1,i2,i3) * mti;
    }
    }
    }
    }

}

/*****************************************************************************
 gridsearch
 *****************************************************************************/
static PyObject *gridsearch(PyObject *self, PyObject *args) {

  PyArrayObject *data, *greens, *mt;
  npy_int64 NC, NS, NT, NGF, NMT;
  npy_int64 i;




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
  printf("\n");

  printf("number of Green's functions:  %d\n", NGF);
  printf("number of moment tensors:  %d\n", NMT);
  printf("\n");


  printf("greens,0 %d\n", (int) PyArray_STRIDES(greens)[0]);
  printf("greens,1 %d\n", (int) PyArray_STRIDES(greens)[1]);
  printf("greens,2 %d\n", (int) PyArray_STRIDES(greens)[2]);
  printf("greens,3 %d\n", (int) PyArray_STRIDES(greens)[3]);
  printf("\n");




  int nd = 3;
  npy_intp dims[] = {NC,NS,NT};
  PyObject *synthetics = PyArray_SimpleNew(nd, dims, NPY_DOUBLE);

  NC = PyArray_SHAPE(data)[0];
  NS = PyArray_SHAPE(data)[1];
  NT = PyArray_SHAPE(data)[2];

  printf("%d\n", NC);
  printf("%d\n", NS);
  printf("%d\n", NT);
  printf("\n");


    npy_int64 i0,i1,i2,i3;
    npy_float64 mti;


  for(i = 0;  i<NMT; ++i) {
    //get_synthetics(greens, mt, synthetics, NC, NS, NT, NGF, i);

    for (i0=0; i0<NC; i0++) {
    for (i1=0; i1<NS; i1++) {
    for (i2=0; i2<NT; i2++) {
        synthetics(i0,i1,i2) = 0.;
    }
    }
    }

    for (i0=0; i0<NGF; i0++) {
    mti = mt(i, i0);
    for (i1=0; i1<NC; i1++) {
    for (i2=0; i2<NS; i2++) {
    for (i3=0; i3<NT; i3++) {
        synthetics(i1,i2,i3) += greens(i0,i1,i2,i3) * mti;
    }
    }
    }
    }

  }

  Py_RETURN_NONE;
}

