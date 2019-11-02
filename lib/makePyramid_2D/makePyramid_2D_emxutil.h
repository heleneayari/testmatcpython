/*
 * File: makePyramid_2D_emxutil.h
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 31-Oct-2019 17:59:21
 */

#ifndef MAKEPYRAMID_2D_EMXUTIL_H
#define MAKEPYRAMID_2D_EMXUTIL_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "makePyramid_2D_types.h"

/* Function Declarations */
extern void emxCopyStruct_struct0_T(struct0_T *dst, const struct0_T *src);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T1(emxArray_real_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_struct0_T(emxArray_struct0_T *emxArray, int
  oldNumel);
extern void emxFreeStruct_struct0_T(struct0_T *pStruct);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxFree_struct0_T(emxArray_struct0_T **pEmxArray);
extern void emxInitStruct_struct0_T(struct0_T *pStruct);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_real_T1(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_struct0_T(emxArray_struct0_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for makePyramid_2D_emxutil.h
 *
 * [EOF]
 */
