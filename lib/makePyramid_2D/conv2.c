/*
 * File: conv2.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 31-Oct-2019 17:59:21
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "makePyramid_2D.h"
#include "conv2.h"
#include "makePyramid_2D_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *a
 *                emxArray_real_T *c
 * Return Type  : void
 */
void conv2(const emxArray_real_T *a, emxArray_real_T *c)
{
  boolean_T p;
  int aidx;
  emxArray_real_T *b_a;
  int lastRowA;
  emxArray_real_T *b_c;
  int a_idx_1;
  int a_idx_0;
  int ma;
  int na;
  int firstColB;
  int lastColB;
  int lastRowB;
  int iC;
  int i;
  int lastColA;
  int a_length;
  int b_i;
  int b_firstColB;
  int cidx;
  int r;
  int iA;
  int iB;
  p = (a->size[0] == 1);
  if (p) {
    emxInit_real_T1(&b_a, 1);
    lastRowA = a->size[1];
    aidx = b_a->size[0];
    b_a->size[0] = lastRowA;
    emxEnsureCapacity_real_T1(b_a, aidx);
    for (aidx = 0; aidx < lastRowA; aidx++) {
      b_a->data[aidx] = a->data[a->size[0] * aidx];
    }

    emxInit_real_T1(&b_c, 1);
    aidx = b_c->size[0];
    b_c->size[0] = b_a->size[0];
    emxEnsureCapacity_real_T1(b_c, aidx);
    lastRowA = b_a->size[0];
    for (aidx = 0; aidx < lastRowA; aidx++) {
      b_c->data[aidx] = 0.0;
    }

    p = (b_a->size[0] == 0);
    if (!p) {
      lastRowA = b_a->size[0];
      ma = b_a->size[0];
      if (b_a->size[0] < 1) {
        aidx = 2;
      } else {
        aidx = 0;
      }

      if (3 <= b_a->size[0]) {
        lastRowB = 2;
      } else {
        lastRowB = b_a->size[0];
      }

      iC = 0;
      for (i = aidx; i <= lastRowB; i++) {
        lastColA = (i < 1);
        if (i + ma <= lastRowA) {
          b_i = ma;
        } else {
          b_i = (lastRowA - i) + 1;
        }

        a_length = b_i - lastColA;
        cidx = iC;
        for (r = 1; r <= a_length; r++) {
          b_c->data[cidx] += (1.0 + -(double)aidx) * b_a->data[lastColA];
          lastColA++;
          cidx++;
        }

        aidx++;
        if (i >= 1) {
          iC++;
        }
      }
    }

    emxFree_real_T(&b_a);
    aidx = c->size[0] * c->size[1];
    c->size[0] = 1;
    c->size[1] = b_c->size[0];
    emxEnsureCapacity_real_T(c, aidx);
    lastRowA = b_c->size[0];
    for (aidx = 0; aidx < lastRowA; aidx++) {
      c->data[c->size[0] * aidx] = b_c->data[aidx];
    }

    emxFree_real_T(&b_c);
  } else {
    aidx = c->size[0] * c->size[1];
    c->size[0] = a->size[0];
    c->size[1] = a->size[1];
    emxEnsureCapacity_real_T(c, aidx);
    lastRowA = a->size[0] * a->size[1];
    for (aidx = 0; aidx < lastRowA; aidx++) {
      c->data[aidx] = 0.0;
    }

    p = ((a->size[0] == 0) || (a->size[1] == 0));
    if (!p) {
      a_idx_1 = a->size[1];
      a_idx_0 = a->size[0];
      ma = a->size[0];
      na = a->size[1] - 1;
      if (a->size[1] < 1) {
        firstColB = 2;
      } else {
        firstColB = 0;
      }

      aidx = a->size[1];
      if (3 <= aidx) {
        lastColB = 2;
      } else {
        lastColB = a->size[1];
      }

      lastRowA = a->size[0];
      if (1 <= lastRowA - 1) {
        lastRowB = 1;
      } else {
        lastRowB = a->size[0];
      }

      while (firstColB <= lastColB) {
        if (firstColB + na < a_idx_1) {
          lastColA = na;
        } else {
          lastColA = a_idx_1 - firstColB;
        }

        for (a_length = (firstColB < 1); a_length <= lastColA; a_length++) {
          if (firstColB + a_length > 1) {
            b_firstColB = (firstColB + a_length) - 1;
          } else {
            b_firstColB = 0;
          }

          iC = b_firstColB * a_idx_0;
          iA = a_length * ma;
          iB = firstColB;
          i = 0;
          while (i <= lastRowB - 1) {
            if (ma <= a_idx_0 - 1) {
              lastRowA = ma;
            } else {
              lastRowA = a_idx_0;
            }

            aidx = iA;
            cidx = iC;
            for (r = 1; r <= lastRowA; r++) {
              c->data[cidx] += (1.0 + -(double)iB) * a->data[aidx];
              aidx++;
              cidx++;
            }

            iB++;
            iC++;
            i = 1;
          }
        }

        firstColB++;
      }
    }
  }
}

/*
 * File trailer for conv2.c
 *
 * [EOF]
 */
