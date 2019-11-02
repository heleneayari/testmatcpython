/*
 * File: makePyramid_2D_emxAPI.h
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 31-Oct-2019 17:59:21
 */

#ifndef MAKEPYRAMID_2D_EMXAPI_H
#define MAKEPYRAMID_2D_EMXAPI_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "makePyramid_2D_types.h"

/* Function Declarations */
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);
extern emxArray_struct0_T *emxCreateND_struct0_T(int numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
  numDimensions, int *size);
extern emxArray_struct0_T *emxCreateWrapperND_struct0_T(struct0_T *data, int
  numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);
extern emxArray_struct0_T *emxCreateWrapper_struct0_T(struct0_T *data, int rows,
  int cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern emxArray_struct0_T *emxCreate_struct0_T(int rows, int cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void emxDestroyArray_struct0_T(emxArray_struct0_T *emxArray);
extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInitArray_struct0_T(emxArray_struct0_T **pEmxArray, int
  numDimensions);

#endif

/*
 * File trailer for makePyramid_2D_emxAPI.h
 *
 * [EOF]
 */
