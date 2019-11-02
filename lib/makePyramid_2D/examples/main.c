/*
 * File: main.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 31-Oct-2019 17:59:21
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "rt_nonfinite.h"
#include "makePyramid_2D.h"
#include "main.h"
#include "makePyramid_2D_terminate.h"
#include "makePyramid_2D_emxAPI.h"
#include "makePyramid_2D_initialize.h"

/* Function Declarations */
static void argInit_3x1_real_T(double result[3]);
static double argInit_real_T(void);
static emxArray_real_T *c_argInit_UnboundedxUnbounded_r(void);
static void main_makePyramid_2D(void);

/* Function Definitions */

/*
 * Arguments    : double result[3]
 * Return Type  : void
 */
static void argInit_3x1_real_T(double result[3])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 3; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : emxArray_real_T *
 */
static emxArray_real_T *c_argInit_UnboundedxUnbounded_r(void)
{
  emxArray_real_T *result;
  static int iv0[2] = { 2, 2 };

  int idx0;
  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_real_T(2, iv0);

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result->data[idx0 + result->size[0] * idx1] = argInit_real_T();
    }
  }

  return result;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_makePyramid_2D(void)
{
  emxArray_struct0_T *pyr;
  emxArray_real_T *img;
  double dv0[3];
  emxInitArray_struct0_T(&pyr, 2);

  /* Initialize function 'makePyramid_2D' input arguments. */
  /* Initialize function input argument 'img'. */
  img = c_argInit_UnboundedxUnbounded_r();

  /* Initialize function input argument 'winSize'. */
  /* Call the entry-point 'makePyramid_2D'. */
  argInit_3x1_real_T(dv0);
  makePyramid_2D(img, argInit_real_T(), argInit_real_T(), dv0, pyr);
  emxDestroyArray_struct0_T(pyr);
  emxDestroyArray_real_T(img);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  makePyramid_2D_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_makePyramid_2D();

  /* Terminate the application.
     You do not need to do this more than one time. */
  makePyramid_2D_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
