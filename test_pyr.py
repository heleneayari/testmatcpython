# -*- coding: utf-8 -*-
"""
Created on Sat Nov  2 01:53:13 2019

@author: hayari
"""

import ctypes
import numpy
import imageio
import pyrAPI as pyr
import visvis as vv


# set the directory for the c .so

LIBTEST = 'C:\Users\hayari\Documents\python/'

# load the .so (dynamic library) using ctypes
EMX = ctypes.cdll.LoadLibrary(LIBTEST + 'mypyr.so')
init = EMX. makePyramid_2D_initialize()
print '\nInitialize...\n'
data_in = imageio.imread(LIBTEST + 'test.tif')
#data_in =data_in.astype(float)
pyr.TestEmxAPI

pyr.TestEmxAPI(data_in)
tata=np.array(titi.gradX)
#vv.imshow(np.array(titi.gradX))
   
