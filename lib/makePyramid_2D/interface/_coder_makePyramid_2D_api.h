/*
 * File: _coder_makePyramid_2D_api.h
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 31-Oct-2019 17:59:21
 */

#ifndef _CODER_MAKEPYRAMID_2D_API_H
#define _CODER_MAKEPYRAMID_2D_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_makePyramid_2D_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

#ifndef typedef_struct0_T
#define typedef_struct0_T

typedef struct {
  emxArray_real_T *img;
  emxArray_real_T *gradX;
  emxArray_real_T *gradY;
} struct0_T;

#endif                                 /*typedef_struct0_T*/

#ifndef typedef_emxArray_struct0_T
#define typedef_emxArray_struct0_T

typedef struct {
  struct0_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
} emxArray_struct0_T;

#endif                                 /*typedef_emxArray_struct0_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void makePyramid_2D(emxArray_real_T *img, real_T level, real_T blur,
  real_T winSize[3], emxArray_struct0_T *pyr);
extern void makePyramid_2D_api(const mxArray * const prhs[4], int32_T nlhs,
  const mxArray *plhs[1]);
extern void makePyramid_2D_atexit(void);
extern void makePyramid_2D_initialize(void);
extern void makePyramid_2D_terminate(void);
extern void makePyramid_2D_xil_terminate(void);

#endif

/*
 * File trailer for _coder_makePyramid_2D_api.h
 *
 * [EOF]
 */
