/*
 * File: makePyramid_2D.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 31-Oct-2019 17:59:21
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "makePyramid_2D.h"
#include "makePyramid_2D_emxutil.h"
#include "conv2.h"
#include "padarray.h"

/* Function Definitions */

/*
 * pyramid = makePyramid( image, level_number, blur_radius=0 );
 *
 *  Make a pyramid of image as described in [Bouguet02]: "Pyramidal Implementation
 *  of the Lucas Kanade Feature Tracker: Description of the algorithm",
 *  Jean-Yves Bouguet, 2002.
 *
 *  INPUT:
 *  - 'image' should be a 2D array (i.e. gray) with format double or single
 *  - 'level_number' is the number of level of the output pyramid (pyr)
 *  - 'blur_radius', convolute pyramid images by a blur filter with this radius
 *
 *  OUTPUT:
 *  - pyramid(i).img   is image of pyramid at level i (starting at 1, not 0 as in [Bouguet02])
 *  - pyramid(i).gradX is the x gradient of image pyramid(i).img
 *  - pyramid(i).gradY is the y gradient of image pyramid(i).img
 *
 *  See also: private/pyrLK, computeKLT
 * Arguments    : const emxArray_real_T *img
 *                double level
 *                double blur
 *                const double winSize[3]
 *                emxArray_struct0_T *pyr
 * Return Type  : void
 */
void makePyramid_2D(const emxArray_real_T *img, double level, double blur, const
                    double winSize[3], emxArray_struct0_T *pyr)
{
  int r;
  unsigned int uv0[2];
  unsigned int uv1[2];
  struct0_T a;
  unsigned int uv2[2];
  int aidx;
  int i;
  emxArray_real_T *ind0_x;
  emxArray_real_T *ind0_y;
  emxArray_real_T *ind1_x;
  emxArray_real_T *ind1_y;
  emxArray_real_T *ind2_x;
  emxArray_real_T *ind2_y;
  emxArray_real_T *C;
  emxArray_real_T *b_C;
  emxArray_real_T *b_pyr;
  emxArray_real_T *b_ind2_x;
  emxArray_real_T *c_pyr;
  double c_ind2_x;
  double b_winSize[2];
  int cidx;
  int firstRowA;
  int cEnd;
  int cEnd1;
  int ma;
  int na;
  int lastColB;
  int firstRowB;
  int lastRowB;
  int lastColA;
  int k;
  int iC;
  int iA;
  int iB;
  int b_i;
  int c_i;
  int a_length;
  (void)blur;
  for (r = 0; r < 2; r++) {
    uv0[r] = (unsigned int)img->size[r];
  }

  for (r = 0; r < 2; r++) {
    uv1[r] = (unsigned int)img->size[r];
  }

  for (r = 0; r < 2; r++) {
    uv2[r] = (unsigned int)img->size[r];
  }

  emxInitStruct_struct0_T(&a);
  r = a.img->size[0] * a.img->size[1];
  a.img->size[0] = (int)uv0[0];
  a.img->size[1] = (int)uv0[1];
  emxEnsureCapacity_real_T(a.img, r);
  aidx = (int)uv0[0] * (int)uv0[1];
  for (r = 0; r < aidx; r++) {
    a.img->data[r] = 1.0;
  }

  r = a.gradX->size[0] * a.gradX->size[1];
  a.gradX->size[0] = (int)uv1[0];
  a.gradX->size[1] = (int)uv1[1];
  emxEnsureCapacity_real_T(a.gradX, r);
  aidx = (int)uv1[0] * (int)uv1[1];
  for (r = 0; r < aidx; r++) {
    a.gradX->data[r] = 1.0;
  }

  r = a.gradY->size[0] * a.gradY->size[1];
  a.gradY->size[0] = (int)uv2[0];
  a.gradY->size[1] = (int)uv2[1];
  emxEnsureCapacity_real_T(a.gradY, r);
  aidx = (int)uv2[0] * (int)uv2[1];
  for (r = 0; r < aidx; r++) {
    a.gradY->data[r] = 1.0;
  }

  r = pyr->size[0] * pyr->size[1];
  pyr->size[0] = 1;
  pyr->size[1] = (int)level;
  emxEnsureCapacity_struct0_T(pyr, r);
  aidx = (int)level;
  for (r = 0; r < aidx; r++) {
    emxCopyStruct_struct0_T(&pyr->data[r], &a);
  }

  emxFreeStruct_struct0_T(&a);

  /*  if nargin>2 && blur>0 */
  /*      filter = 1; */
  /*      F = conv2(double([1 2 1]),double([1 2 1]'))/16; */
  /*      for i=1:blur */
  /*          filter = conv2(double(filter),double(F),'same'); */
  /*      end */
  /*  else */
  /*      filter = []; */
  /*  end */
  i = 0;
  emxInit_real_T(&ind0_x, 2);
  emxInit_real_T(&ind0_y, 2);
  emxInit_real_T(&ind1_x, 2);
  emxInit_real_T(&ind1_y, 2);
  emxInit_real_T(&ind2_x, 2);
  emxInit_real_T(&ind2_y, 2);
  emxInit_real_T(&C, 2);
  emxInit_real_T(&b_C, 2);
  emxInit_real_T(&b_pyr, 2);
  emxInit_real_T(&b_ind2_x, 2);
  emxInit_real_T1(&c_pyr, 1);
  while (i <= (int)level - 1) {
    /*  compute pyramid */
    if (1.0 + (double)i == 1.0) {
      aidx = img->size[0] * img->size[1] - 1;
      r = pyr->data[0].img->size[0] * pyr->data[0].img->size[1];
      pyr->data[0].img->size[0] = img->size[0];
      emxEnsureCapacity_real_T(pyr->data[0].img, r);
      r = pyr->data[0].img->size[0] * pyr->data[0].img->size[1];
      pyr->data[0].img->size[1] = img->size[1];
      emxEnsureCapacity_real_T(pyr->data[0].img, r);
      for (r = 0; r <= aidx; r++) {
        pyr->data[0].img->data[r] = img->data[r];
      }
    } else {
      /*  img_0 = pyr(i-1).img; */
      if (pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] - 1 < 1) {
        r = ind0_x->size[0] * ind0_x->size[1];
        ind0_x->size[0] = 1;
        ind0_x->size[1] = 0;
        emxEnsureCapacity_real_T(ind0_x, r);
      } else {
        c_ind2_x = (double)pyr->data[(int)((1.0 + (double)i) - 1.0) - 1]
          .img->size[0] - 1.0;
        r = ind0_x->size[0] * ind0_x->size[1];
        ind0_x->size[0] = 1;
        ind0_x->size[1] = (int)floor((c_ind2_x - 1.0) / 2.0) + 1;
        emxEnsureCapacity_real_T(ind0_x, r);
        aidx = (int)floor((c_ind2_x - 1.0) / 2.0);
        for (r = 0; r <= aidx; r++) {
          ind0_x->data[ind0_x->size[0] * r] = 1.0 + 2.0 * (double)r;
        }
      }

      if (pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[1] - 1 < 1) {
        r = ind0_y->size[0] * ind0_y->size[1];
        ind0_y->size[0] = 1;
        ind0_y->size[1] = 0;
        emxEnsureCapacity_real_T(ind0_y, r);
      } else {
        c_ind2_x = (double)pyr->data[(int)((1.0 + (double)i) - 1.0) - 1]
          .img->size[1] - 1.0;
        r = ind0_y->size[0] * ind0_y->size[1];
        ind0_y->size[0] = 1;
        ind0_y->size[1] = (int)floor((c_ind2_x - 1.0) / 2.0) + 1;
        emxEnsureCapacity_real_T(ind0_y, r);
        aidx = (int)floor((c_ind2_x - 1.0) / 2.0);
        for (r = 0; r <= aidx; r++) {
          ind0_y->data[ind0_y->size[0] * r] = 1.0 + 2.0 * (double)r;
        }
      }

      if (pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] < 2) {
        r = ind1_x->size[0] * ind1_x->size[1];
        ind1_x->size[0] = 1;
        ind1_x->size[1] = 0;
        emxEnsureCapacity_real_T(ind1_x, r);
      } else {
        r = pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0];
        cidx = ind1_x->size[0] * ind1_x->size[1];
        ind1_x->size[0] = 1;
        ind1_x->size[1] = (int)floor(((double)r - 2.0) / 2.0) + 1;
        emxEnsureCapacity_real_T(ind1_x, cidx);
        aidx = (int)floor(((double)r - 2.0) / 2.0);
        for (r = 0; r <= aidx; r++) {
          ind1_x->data[ind1_x->size[0] * r] = 2.0 + 2.0 * (double)r;
        }
      }

      if (pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[1] < 2) {
        r = ind1_y->size[0] * ind1_y->size[1];
        ind1_y->size[0] = 1;
        ind1_y->size[1] = 0;
        emxEnsureCapacity_real_T(ind1_y, r);
      } else {
        r = pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[1];
        cidx = ind1_y->size[0] * ind1_y->size[1];
        ind1_y->size[0] = 1;
        ind1_y->size[1] = (int)floor(((double)r - 2.0) / 2.0) + 1;
        emxEnsureCapacity_real_T(ind1_y, cidx);
        aidx = (int)floor(((double)r - 2.0) / 2.0);
        for (r = 0; r <= aidx; r++) {
          ind1_y->data[ind1_y->size[0] * r] = 2.0 + 2.0 * (double)r;
        }
      }

      if (pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] < 3) {
        r = ind2_x->size[0] * ind2_x->size[1];
        ind2_x->size[0] = 1;
        ind2_x->size[1] = 0;
        emxEnsureCapacity_real_T(ind2_x, r);
      } else {
        r = pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0];
        cidx = ind2_x->size[0] * ind2_x->size[1];
        ind2_x->size[0] = 1;
        ind2_x->size[1] = (int)floor(((double)r - 3.0) / 2.0) + 1;
        emxEnsureCapacity_real_T(ind2_x, cidx);
        aidx = (int)floor(((double)r - 3.0) / 2.0);
        for (r = 0; r <= aidx; r++) {
          ind2_x->data[ind2_x->size[0] * r] = 3.0 + 2.0 * (double)r;
        }
      }

      if (pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[1] < 3) {
        r = ind2_y->size[0] * ind2_y->size[1];
        ind2_y->size[0] = 1;
        ind2_y->size[1] = 0;
        emxEnsureCapacity_real_T(ind2_y, r);
      } else {
        r = pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[1];
        cidx = ind2_y->size[0] * ind2_y->size[1];
        ind2_y->size[0] = 1;
        ind2_y->size[1] = (int)floor(((double)r - 3.0) / 2.0) + 1;
        emxEnsureCapacity_real_T(ind2_y, cidx);
        aidx = (int)floor(((double)r - 3.0) / 2.0);
        for (r = 0; r <= aidx; r++) {
          ind2_y->data[ind2_y->size[0] * r] = 3.0 + 2.0 * (double)r;
        }
      }

      if (ind2_x->size[1] < ind1_x->size[1]) {
        firstRowA = ind2_x->size[1] - 1;
        c_ind2_x = ind2_x->data[firstRowA];
        r = b_ind2_x->size[0] * b_ind2_x->size[1];
        b_ind2_x->size[0] = 1;
        b_ind2_x->size[1] = ind2_x->size[1] + 1;
        emxEnsureCapacity_real_T(b_ind2_x, r);
        aidx = ind2_x->size[1];
        for (r = 0; r < aidx; r++) {
          b_ind2_x->data[b_ind2_x->size[0] * r] = ind2_x->data[ind2_x->size[0] *
            r];
        }

        b_ind2_x->data[b_ind2_x->size[0] * ind2_x->size[1]] = c_ind2_x;
        r = ind2_x->size[0] * ind2_x->size[1];
        ind2_x->size[0] = 1;
        ind2_x->size[1] = b_ind2_x->size[1];
        emxEnsureCapacity_real_T(ind2_x, r);
        aidx = b_ind2_x->size[1];
        for (r = 0; r < aidx; r++) {
          ind2_x->data[ind2_x->size[0] * r] = b_ind2_x->data[b_ind2_x->size[0] *
            r];
        }
      }

      if (ind2_y->size[1] < ind1_y->size[1]) {
        firstRowA = ind2_y->size[1] - 1;
        c_ind2_x = ind2_y->data[firstRowA];
        r = b_ind2_x->size[0] * b_ind2_x->size[1];
        b_ind2_x->size[0] = 1;
        b_ind2_x->size[1] = ind2_y->size[1] + 1;
        emxEnsureCapacity_real_T(b_ind2_x, r);
        aidx = ind2_y->size[1];
        for (r = 0; r < aidx; r++) {
          b_ind2_x->data[b_ind2_x->size[0] * r] = ind2_y->data[ind2_y->size[0] *
            r];
        }

        b_ind2_x->data[b_ind2_x->size[0] * ind2_y->size[1]] = c_ind2_x;
        r = ind2_y->size[0] * ind2_y->size[1];
        ind2_y->size[0] = 1;
        ind2_y->size[1] = b_ind2_x->size[1];
        emxEnsureCapacity_real_T(ind2_y, r);
        aidx = b_ind2_x->size[1];
        for (r = 0; r < aidx; r++) {
          ind2_y->data[ind2_y->size[0] * r] = b_ind2_x->data[b_ind2_x->size[0] *
            r];
        }
      }

      r = b_pyr->size[0] * b_pyr->size[1];
      b_pyr->size[0] = ind1_x->size[1];
      b_pyr->size[1] = ind1_y->size[1];
      emxEnsureCapacity_real_T(b_pyr, r);
      aidx = ind1_y->size[1];
      for (r = 0; r < aidx; r++) {
        firstRowA = ind1_x->size[1];
        for (cidx = 0; cidx < firstRowA; cidx++) {
          b_pyr->data[cidx + b_pyr->size[0] * r] = pyr->data[(int)((1.0 +
            (double)i) - 1.0) - 1].img->data[((int)ind1_x->data[ind1_x->size[0] *
            cidx] + pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] *
            ((int)ind1_y->data[ind1_y->size[0] * r] - 1)) - 1];
        }
      }

      aidx = b_pyr->size[0] * b_pyr->size[1] - 1;
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      pyr->data[i].img->size[0] = b_pyr->size[0];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      pyr->data[i].img->size[1] = b_pyr->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      for (r = 0; r <= aidx; r++) {
        pyr->data[i].img->data[r] = 0.25 * b_pyr->data[r];
      }

      r = b_pyr->size[0] * b_pyr->size[1];
      b_pyr->size[0] = ind0_x->size[1];
      b_pyr->size[1] = ind1_y->size[1];
      emxEnsureCapacity_real_T(b_pyr, r);
      aidx = ind1_y->size[1];
      for (r = 0; r < aidx; r++) {
        firstRowA = ind0_x->size[1];
        for (cidx = 0; cidx < firstRowA; cidx++) {
          b_pyr->data[cidx + b_pyr->size[0] * r] = pyr->data[(int)((1.0 +
            (double)i) - 1.0) - 1].img->data[((int)ind0_x->data[ind0_x->size[0] *
            cidx] + pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] *
            ((int)ind1_y->data[ind1_y->size[0] * r] - 1)) - 1];
        }
      }

      aidx = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = c_pyr->size[0];
      c_pyr->size[0] = aidx;
      emxEnsureCapacity_real_T1(c_pyr, r);
      for (r = 0; r < aidx; r++) {
        c_pyr->data[r] = pyr->data[i].img->data[r] + 0.125 * b_pyr->data[r];
      }

      aidx = c_pyr->size[0];
      for (r = 0; r < aidx; r++) {
        pyr->data[i].img->data[r] = c_pyr->data[r];
      }

      r = b_pyr->size[0] * b_pyr->size[1];
      b_pyr->size[0] = ind1_x->size[1];
      b_pyr->size[1] = ind0_y->size[1];
      emxEnsureCapacity_real_T(b_pyr, r);
      aidx = ind0_y->size[1];
      for (r = 0; r < aidx; r++) {
        firstRowA = ind1_x->size[1];
        for (cidx = 0; cidx < firstRowA; cidx++) {
          b_pyr->data[cidx + b_pyr->size[0] * r] = pyr->data[(int)((1.0 +
            (double)i) - 1.0) - 1].img->data[((int)ind1_x->data[ind1_x->size[0] *
            cidx] + pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] *
            ((int)ind0_y->data[ind0_y->size[0] * r] - 1)) - 1];
        }
      }

      aidx = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = c_pyr->size[0];
      c_pyr->size[0] = aidx;
      emxEnsureCapacity_real_T1(c_pyr, r);
      for (r = 0; r < aidx; r++) {
        c_pyr->data[r] = pyr->data[i].img->data[r] + 0.125 * b_pyr->data[r];
      }

      aidx = c_pyr->size[0];
      for (r = 0; r < aidx; r++) {
        pyr->data[i].img->data[r] = c_pyr->data[r];
      }

      r = b_pyr->size[0] * b_pyr->size[1];
      b_pyr->size[0] = ind2_x->size[1];
      b_pyr->size[1] = ind1_y->size[1];
      emxEnsureCapacity_real_T(b_pyr, r);
      aidx = ind1_y->size[1];
      for (r = 0; r < aidx; r++) {
        firstRowA = ind2_x->size[1];
        for (cidx = 0; cidx < firstRowA; cidx++) {
          b_pyr->data[cidx + b_pyr->size[0] * r] = pyr->data[(int)((1.0 +
            (double)i) - 1.0) - 1].img->data[((int)ind2_x->data[ind2_x->size[0] *
            cidx] + pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] *
            ((int)ind1_y->data[ind1_y->size[0] * r] - 1)) - 1];
        }
      }

      aidx = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = c_pyr->size[0];
      c_pyr->size[0] = aidx;
      emxEnsureCapacity_real_T1(c_pyr, r);
      for (r = 0; r < aidx; r++) {
        c_pyr->data[r] = pyr->data[i].img->data[r] + 0.125 * b_pyr->data[r];
      }

      aidx = c_pyr->size[0];
      for (r = 0; r < aidx; r++) {
        pyr->data[i].img->data[r] = c_pyr->data[r];
      }

      r = b_pyr->size[0] * b_pyr->size[1];
      b_pyr->size[0] = ind1_x->size[1];
      b_pyr->size[1] = ind2_y->size[1];
      emxEnsureCapacity_real_T(b_pyr, r);
      aidx = ind2_y->size[1];
      for (r = 0; r < aidx; r++) {
        firstRowA = ind1_x->size[1];
        for (cidx = 0; cidx < firstRowA; cidx++) {
          b_pyr->data[cidx + b_pyr->size[0] * r] = pyr->data[(int)((1.0 +
            (double)i) - 1.0) - 1].img->data[((int)ind1_x->data[ind1_x->size[0] *
            cidx] + pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] *
            ((int)ind2_y->data[ind2_y->size[0] * r] - 1)) - 1];
        }
      }

      aidx = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = c_pyr->size[0];
      c_pyr->size[0] = aidx;
      emxEnsureCapacity_real_T1(c_pyr, r);
      for (r = 0; r < aidx; r++) {
        c_pyr->data[r] = pyr->data[i].img->data[r] + 0.125 * b_pyr->data[r];
      }

      aidx = c_pyr->size[0];
      for (r = 0; r < aidx; r++) {
        pyr->data[i].img->data[r] = c_pyr->data[r];
      }

      r = b_pyr->size[0] * b_pyr->size[1];
      b_pyr->size[0] = ind0_x->size[1];
      b_pyr->size[1] = ind0_y->size[1];
      emxEnsureCapacity_real_T(b_pyr, r);
      aidx = ind0_y->size[1];
      for (r = 0; r < aidx; r++) {
        firstRowA = ind0_x->size[1];
        for (cidx = 0; cidx < firstRowA; cidx++) {
          b_pyr->data[cidx + b_pyr->size[0] * r] = pyr->data[(int)((1.0 +
            (double)i) - 1.0) - 1].img->data[((int)ind0_x->data[ind0_x->size[0] *
            cidx] + pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] *
            ((int)ind0_y->data[ind0_y->size[0] * r] - 1)) - 1];
        }
      }

      aidx = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = c_pyr->size[0];
      c_pyr->size[0] = aidx;
      emxEnsureCapacity_real_T1(c_pyr, r);
      for (r = 0; r < aidx; r++) {
        c_pyr->data[r] = pyr->data[i].img->data[r] + 0.0625 * b_pyr->data[r];
      }

      aidx = c_pyr->size[0];
      for (r = 0; r < aidx; r++) {
        pyr->data[i].img->data[r] = c_pyr->data[r];
      }

      r = b_pyr->size[0] * b_pyr->size[1];
      b_pyr->size[0] = ind2_x->size[1];
      b_pyr->size[1] = ind0_y->size[1];
      emxEnsureCapacity_real_T(b_pyr, r);
      aidx = ind0_y->size[1];
      for (r = 0; r < aidx; r++) {
        firstRowA = ind2_x->size[1];
        for (cidx = 0; cidx < firstRowA; cidx++) {
          b_pyr->data[cidx + b_pyr->size[0] * r] = pyr->data[(int)((1.0 +
            (double)i) - 1.0) - 1].img->data[((int)ind2_x->data[ind2_x->size[0] *
            cidx] + pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] *
            ((int)ind0_y->data[ind0_y->size[0] * r] - 1)) - 1];
        }
      }

      aidx = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = c_pyr->size[0];
      c_pyr->size[0] = aidx;
      emxEnsureCapacity_real_T1(c_pyr, r);
      for (r = 0; r < aidx; r++) {
        c_pyr->data[r] = pyr->data[i].img->data[r] + 0.0625 * b_pyr->data[r];
      }

      aidx = c_pyr->size[0];
      for (r = 0; r < aidx; r++) {
        pyr->data[i].img->data[r] = c_pyr->data[r];
      }

      r = b_pyr->size[0] * b_pyr->size[1];
      b_pyr->size[0] = ind2_x->size[1];
      b_pyr->size[1] = ind2_y->size[1];
      emxEnsureCapacity_real_T(b_pyr, r);
      aidx = ind2_y->size[1];
      for (r = 0; r < aidx; r++) {
        firstRowA = ind2_x->size[1];
        for (cidx = 0; cidx < firstRowA; cidx++) {
          b_pyr->data[cidx + b_pyr->size[0] * r] = pyr->data[(int)((1.0 +
            (double)i) - 1.0) - 1].img->data[((int)ind2_x->data[ind2_x->size[0] *
            cidx] + pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] *
            ((int)ind2_y->data[ind2_y->size[0] * r] - 1)) - 1];
        }
      }

      aidx = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = c_pyr->size[0];
      c_pyr->size[0] = aidx;
      emxEnsureCapacity_real_T1(c_pyr, r);
      for (r = 0; r < aidx; r++) {
        c_pyr->data[r] = pyr->data[i].img->data[r] + 0.0625 * b_pyr->data[r];
      }

      aidx = c_pyr->size[0];
      for (r = 0; r < aidx; r++) {
        pyr->data[i].img->data[r] = c_pyr->data[r];
      }

      r = b_pyr->size[0] * b_pyr->size[1];
      b_pyr->size[0] = ind0_x->size[1];
      b_pyr->size[1] = ind2_y->size[1];
      emxEnsureCapacity_real_T(b_pyr, r);
      aidx = ind2_y->size[1];
      for (r = 0; r < aidx; r++) {
        firstRowA = ind0_x->size[1];
        for (cidx = 0; cidx < firstRowA; cidx++) {
          b_pyr->data[cidx + b_pyr->size[0] * r] = pyr->data[(int)((1.0 +
            (double)i) - 1.0) - 1].img->data[((int)ind0_x->data[ind0_x->size[0] *
            cidx] + pyr->data[(int)((1.0 + (double)i) - 1.0) - 1].img->size[0] *
            ((int)ind2_y->data[ind2_y->size[0] * r] - 1)) - 1];
        }
      }

      aidx = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
      emxEnsureCapacity_real_T(pyr->data[i].img, r);
      r = c_pyr->size[0];
      c_pyr->size[0] = aidx;
      emxEnsureCapacity_real_T1(c_pyr, r);
      for (r = 0; r < aidx; r++) {
        c_pyr->data[r] = pyr->data[i].img->data[r] + 0.0625 * b_pyr->data[r];
      }

      aidx = c_pyr->size[0];
      for (r = 0; r < aidx; r++) {
        pyr->data[i].img->data[r] = c_pyr->data[r];
      }
    }

    /*  blur images */
    /*      if ~isempty(filter) */
    /*          pyr(i).img = conv2(double(pyr(i).img),double(filter),'same'); */
    /*      end */
    /*  compute gradient */
    conv2(pyr->data[i].img, pyr->data[i].gradX);
    r = b_pyr->size[0] * b_pyr->size[1];
    b_pyr->size[0] = pyr->data[i].img->size[0];
    emxEnsureCapacity_real_T(b_pyr, r);
    r = b_pyr->size[0] * b_pyr->size[1];
    b_pyr->size[1] = pyr->data[i].img->size[1];
    emxEnsureCapacity_real_T(b_pyr, r);
    aidx = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
    for (r = 0; r < aidx; r++) {
      b_pyr->data[r] = pyr->data[i].img->data[r];
    }

    firstRowA = pyr->data[i].img->size[0];
    aidx = pyr->data[i].img->size[1];
    r = pyr->data[i].gradY->size[0] * pyr->data[i].gradY->size[1];
    pyr->data[i].gradY->size[0] = firstRowA;
    pyr->data[i].gradY->size[1] = aidx;
    emxEnsureCapacity_real_T(pyr->data[i].gradY, r);
    for (r = 0; r < aidx; r++) {
      for (cidx = 0; cidx < firstRowA; cidx++) {
        pyr->data[i].gradY->data[cidx + pyr->data[i].gradY->size[0] * r] = 0.0;
      }
    }

    if ((b_pyr->size[0] == 0) || (b_pyr->size[1] == 0) || ((pyr->data[i]
          .gradY->size[0] == 0) || (pyr->data[i].gradY->size[1] == 0))) {
    } else {
      r = C->size[0] * C->size[1];
      C->size[0] = pyr->data[i].gradY->size[0];
      emxEnsureCapacity_real_T(C, r);
      r = C->size[0] * C->size[1];
      C->size[1] = pyr->data[i].gradY->size[1];
      emxEnsureCapacity_real_T(C, r);
      aidx = pyr->data[i].gradY->size[0] * pyr->data[i].gradY->size[1];
      for (r = 0; r < aidx; r++) {
        C->data[r] = pyr->data[i].gradY->data[r];
      }

      cEnd = pyr->data[i].gradY->size[1] - 1;
      r = b_C->size[0] * b_C->size[1];
      b_C->size[0] = pyr->data[i].gradY->size[0];
      emxEnsureCapacity_real_T(b_C, r);
      r = b_C->size[0] * b_C->size[1];
      b_C->size[1] = pyr->data[i].gradY->size[1];
      emxEnsureCapacity_real_T(b_C, r);
      aidx = pyr->data[i].gradY->size[0] * pyr->data[i].gradY->size[1];
      for (r = 0; r < aidx; r++) {
        b_C->data[r] = pyr->data[i].gradY->data[r];
      }

      cEnd1 = pyr->data[i].gradY->size[0];
      ma = b_pyr->size[0];
      na = b_pyr->size[1] - 1;
      if (1 <= C->size[1] - 1) {
        lastColB = 1;
      } else {
        lastColB = C->size[1];
      }

      if (b_pyr->size[0] < 1) {
        firstRowB = 2;
      } else {
        firstRowB = 0;
      }

      if (3 <= b_C->size[0]) {
        lastRowB = 2;
      } else {
        lastRowB = b_C->size[0];
      }

      firstRowA = 0;
      while (firstRowA <= lastColB - 1) {
        if (na < cEnd) {
          lastColA = na;
        } else {
          lastColA = cEnd;
        }

        for (k = 0; k <= lastColA; k++) {
          if (k > 0) {
            firstRowA = k;
          } else {
            firstRowA = 0;
          }

          iC = firstRowA * cEnd1;
          iA = k * ma;
          iB = firstRowB;
          for (b_i = firstRowB; b_i <= lastRowB; b_i++) {
            firstRowA = (b_i < 1);
            if (b_i + ma <= cEnd1) {
              c_i = ma;
            } else {
              c_i = (cEnd1 - b_i) + 1;
            }

            a_length = c_i - firstRowA;
            aidx = iA + firstRowA;
            cidx = iC;
            for (r = 1; r <= a_length; r++) {
              pyr->data[i].gradY->data[cidx] += (1.0 + -(double)iB) *
                b_pyr->data[aidx];
              aidx++;
              cidx++;
            }

            iB++;
            if (b_i >= 1) {
              iC++;
            }
          }
        }

        firstRowA = 1;
      }
    }

    i++;
  }

  emxFree_real_T(&c_pyr);
  emxFree_real_T(&b_ind2_x);
  emxFree_real_T(&b_C);
  emxFree_real_T(&C);
  emxFree_real_T(&ind2_y);
  emxFree_real_T(&ind2_x);
  emxFree_real_T(&ind1_y);
  emxFree_real_T(&ind1_x);
  emxFree_real_T(&ind0_y);
  emxFree_real_T(&ind0_x);
  for (i = 0; i < (int)level; i++) {
    b_winSize[0] = winSize[i];
    b_winSize[1] = winSize[i];
    r = b_pyr->size[0] * b_pyr->size[1];
    b_pyr->size[0] = pyr->data[i].gradX->size[0];
    emxEnsureCapacity_real_T(b_pyr, r);
    r = b_pyr->size[0] * b_pyr->size[1];
    b_pyr->size[1] = pyr->data[i].gradX->size[1];
    emxEnsureCapacity_real_T(b_pyr, r);
    aidx = pyr->data[i].gradX->size[0] * pyr->data[i].gradX->size[1];
    for (r = 0; r < aidx; r++) {
      b_pyr->data[r] = pyr->data[i].gradX->data[r];
    }

    padarray(b_pyr, b_winSize, pyr->data[i].gradX);
    b_winSize[0] = winSize[i];
    b_winSize[1] = winSize[i];
    r = b_pyr->size[0] * b_pyr->size[1];
    b_pyr->size[0] = pyr->data[i].gradY->size[0];
    emxEnsureCapacity_real_T(b_pyr, r);
    r = b_pyr->size[0] * b_pyr->size[1];
    b_pyr->size[1] = pyr->data[i].gradY->size[1];
    emxEnsureCapacity_real_T(b_pyr, r);
    aidx = pyr->data[i].gradY->size[0] * pyr->data[i].gradY->size[1];
    for (r = 0; r < aidx; r++) {
      b_pyr->data[r] = pyr->data[i].gradY->data[r];
    }

    padarray(b_pyr, b_winSize, pyr->data[i].gradY);
    b_winSize[0] = winSize[i];
    b_winSize[1] = winSize[i];
    r = b_pyr->size[0] * b_pyr->size[1];
    b_pyr->size[0] = pyr->data[i].img->size[0];
    emxEnsureCapacity_real_T(b_pyr, r);
    r = b_pyr->size[0] * b_pyr->size[1];
    b_pyr->size[1] = pyr->data[i].img->size[1];
    emxEnsureCapacity_real_T(b_pyr, r);
    aidx = pyr->data[i].img->size[0] * pyr->data[i].img->size[1];
    for (r = 0; r < aidx; r++) {
      b_pyr->data[r] = pyr->data[i].img->data[r];
    }

    padarray(b_pyr, b_winSize, pyr->data[i].img);
  }

  emxFree_real_T(&b_pyr);
}

/*
 * File trailer for makePyramid_2D.c
 *
 * [EOF]
 */
