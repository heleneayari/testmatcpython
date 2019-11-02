/*
 * File: padarray.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 31-Oct-2019 17:59:21
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "makePyramid_2D.h"
#include "padarray.h"
#include "makePyramid_2D_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *varargin_1
 *                const double varargin_2[2]
 *                emxArray_real_T *b
 * Return Type  : void
 */
void padarray(const emxArray_real_T *varargin_1, const double varargin_2[2],
              emxArray_real_T *b)
{
  int i0;
  double sizeB[2];
  int j;
  int i;
  int i1;
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    for (i0 = 0; i0 < 2; i0++) {
      sizeB[i0] = (double)varargin_1->size[i0] + 2.0 * varargin_2[i0];
    }

    i0 = b->size[0] * b->size[1];
    b->size[0] = (int)sizeB[0];
    b->size[1] = (int)sizeB[1];
    emxEnsureCapacity_real_T(b, i0);
    j = (int)sizeB[0] * (int)sizeB[1];
    for (i0 = 0; i0 < j; i0++) {
      b->data[i0] = 0.0;
    }
  } else {
    for (i0 = 0; i0 < 2; i0++) {
      sizeB[i0] = (double)varargin_1->size[i0] + 2.0 * varargin_2[i0];
    }

    i0 = b->size[0] * b->size[1];
    b->size[0] = (int)sizeB[0];
    b->size[1] = (int)sizeB[1];
    emxEnsureCapacity_real_T(b, i0);
    for (j = 0; j < (int)varargin_2[1]; j++) {
      i0 = b->size[0];
      for (i = 0; i < i0; i++) {
        b->data[i + b->size[0] * j] = 0.0;
      }
    }

    i0 = b->size[1];
    for (j = varargin_1->size[1] + (int)varargin_2[1]; j < i0; j++) {
      i1 = b->size[0];
      for (i = 0; i < i1; i++) {
        b->data[i + b->size[0] * j] = 0.0;
      }
    }

    for (j = 0; j < varargin_1->size[1]; j++) {
      for (i = 0; i < (int)varargin_2[0]; i++) {
        b->data[i + b->size[0] * (j + (int)varargin_2[1])] = 0.0;
      }
    }

    for (j = 0; j < varargin_1->size[1]; j++) {
      i0 = b->size[0];
      for (i = (int)varargin_2[0] + varargin_1->size[0]; i < i0; i++) {
        b->data[i + b->size[0] * (j + (int)varargin_2[1])] = 0.0;
      }
    }

    for (j = 0; j < varargin_1->size[1]; j++) {
      for (i = 0; i < varargin_1->size[0]; i++) {
        b->data[(i + (int)varargin_2[0]) + b->size[0] * (j + (int)varargin_2[1])]
          = varargin_1->data[i + varargin_1->size[0] * j];
      }
    }
  }
}

/*
 * File trailer for padarray.c
 *
 * [EOF]
 */
