
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
PyMODINIT_FUNC initL2_misfit_1(void) {
  (void) Py_InitModule("L2_misfit_1", methods);
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

#define data_data(i0,i1) (*(npy_float64*)((PyArray_DATA(data_data) +          \
                                (i0) * PyArray_STRIDES(data_data)[0] +        \
                                (i1) * PyArray_STRIDES(data_data)[1] )))

#define greens_data(i0,i1,i2,i3) (*(npy_float64*)((PyArray_DATA(greens_data) +\
                                (i0) * PyArray_STRIDES(greens_data)[0] +      \
                                (i1) * PyArray_STRIDES(greens_data)[1] +      \
                                (i2) * PyArray_STRIDES(greens_data)[2] +      \
                                (i3) * PyArray_STRIDES(greens_data)[3] )))

#define greens_greens(i0,i1,i2,i3,i4) (*(npy_float64*)((PyArray_DATA(greens_greens) + \
                                (i0) * PyArray_STRIDES(greens_greens)[0] +   \
                                (i1) * PyArray_STRIDES(greens_greens)[1] +   \
                                (i2) * PyArray_STRIDES(greens_greens)[2] +   \
                                (i3) * PyArray_STRIDES(greens_greens)[3] +   \
                                (i4) * PyArray_STRIDES(greens_greens)[4] )))

#define sources(i0,i1) (*(npy_float64*)((PyArray_DATA(sources) +             \
                                (i0) * PyArray_STRIDES(sources)[0] +         \
                                (i1) * PyArray_STRIDES(sources)[1] )))



/*****************************************************************************
 misfit
 *****************************************************************************/
static PyObject *misfit(PyObject *self, PyObject *args) {

  PyArrayObject *data, *greens, *sources;
  PyArrayObject *data_data, *greens_data, *greens_greens;
  npy_int64 NCOMPS, NSTATIONS, NPTS, NGREENS, NSOURCES;
  npy_int64 Npad1, Npad2;
  int verbose;

  int npts_shift;
  npy_float64 dt;
  npy_float64 sum_misfit, _misfit;
  int i,j1,j2,k,k1,k2,it;




  // parse arguments
  if (!PyArg_ParseTuple(args, "O!O!O!O!O!O!iii",
                        &PyArray_Type, &data,
                        &PyArray_Type, &greens,
                        &PyArray_Type, &sources,
                        &PyArray_Type, &data_data,
                        &PyArray_Type, &greens_data,
                        &PyArray_Type, &greens_greens,
                        &Npad1,
                        &Npad2,
                        &verbose)) {
    return NULL;
  }

  NCOMPS = PyArray_SHAPE(data)[0];
  NSTATIONS = PyArray_SHAPE(data)[1];
  NPTS = PyArray_SHAPE(data)[2];
  NGREENS = PyArray_SHAPE(greens)[2];
  NSOURCES = PyArray_SHAPE(sources)[0];

  // temporary array
  //int nd = 1;
  //npy_intp dims[] = {Npad1+Npad2+1};
  //PyObject *corr_sum = PyArray_SimpleNew(nd, dims, NPY_DOUBLE);

  // output array
  int nd = 1;
  npy_intp dims[] = {NSOURCES};
  PyObject *results = PyArray_SimpleNew(nd, dims, NPY_DOUBLE);

  if (verbose>1) {
    printf("number of components:  %d\n", NCOMPS);
    printf("number of stations:  %d\n", NSTATIONS);
    printf("number of time samples:  %d\n", NPTS);
    printf("number of Green's functions:  %d\n", NGREENS);
    printf("number of moment tensors:  %d\n", NSOURCES);
  }


  for(i=0; i<NSOURCES; ++i) {

    sum_misfit = 0.;

    for (j1=0; j1<NCOMPS; j1++) {
      for (j2=0; j2<NSTATIONS; j2++) {
        //
        // calculate npts_shift
        //
        //for (it=0; it<Npad1+Npad2+1; it++) {
        //    corr_sum(it) = 0.;
        //}
        //for (k=0; k<NGREENS; k++) {
        //  for (it=0; it<Npad1+Npad2+1; it++) {
        //      corr_sum(it) = greens_data(j1,j2,it,k) * sources(i,k);
        //  }
        //}
        //npts_shift = argmax(corr_sum, npts);
        npts_shift = Npad1 + 1;


        //
        // calculate L2 norm using ||s - d||^2 = s^2 + d^2 - 2sd
        //
        _misfit = 0.;

        // ss
        for (k1=0; k1<NGREENS; k1++) {
          for (k2=0; k2<k1; k2++) {
            _misfit += sources(i, k1) * sources(i, k2) *
                greens_greens(j1,j2,npts_shift,k1,k2);
          }
        }

        // dd
        _misfit += data_data(j1,j2);

        // sd
        for (k=0; k<NGREENS; k++) {
          _misfit -= 2.*greens_data(j1,j2,npts_shift,k); 
        }

        //if (norm=="L2") {
            sum_misfit += _misfit*dt;
        //}
        //else if (norm=="hybrid") {
        //    sum_misfit += sqrt(_misfit*dt);
        //}

      }
    }
    //results[i] = sum_misfit;
  }



  Py_RETURN_NONE;
}

