/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009, Arnaud Barré
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "btkMEXObjectHandle.h"
#include "btkMEXGetPoints.h"

#include <btkAcquisition.h>
#include <btkPoint.h>
#include <btkConvert.h>

// btkSetPoint(h, i, values, residual, mask)
// btkSetPoint(h, label, values, residual, mask)
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if(nrhs < 3)
    mexErrMsgTxt("Minimum of three inputs required.");
  if (nlhs > 2)
   mexErrMsgTxt("Too many output arguments.");

  int vn = 0, mn = 0, rn = 0;

  if (!mxIsChar(prhs[1]) && (!mxIsNumeric(prhs[1]) || mxIsEmpty(prhs[1]) || mxIsComplex(prhs[1]) || (mxGetNumberOfElements(prhs[1]) != 1)))
    mexErrMsgTxt("Point's index must be a non-empty string or an integer.");
  if (!mxIsNumeric(prhs[2]) || mxIsEmpty(prhs[2]) || mxIsComplex(prhs[2]) || (mxGetN(prhs[2]) != 3))
    mexErrMsgTxt("Point's values must have a second dimension equals to 3.");
  vn = mxGetM(prhs[2]);
  if (nrhs >= 4)
  {
     if (!mxIsNumeric(prhs[3]) || mxIsEmpty(prhs[3]) || mxIsComplex(prhs[3]) || (mxGetN(prhs[3]) != 1))
    mexErrMsgTxt("Point's residual must have a second dimension equals to 1.");
    rn = mxGetM(prhs[3]);
  }
  if (nrhs >= 5)
  {
     if (!mxIsNumeric(prhs[4]) || mxIsEmpty(prhs[4]) || mxIsComplex(prhs[4]) || (mxGetN(prhs[4]) != 1))
    mexErrMsgTxt("Point's mask must have a second dimension equals to 1.");
    mn = mxGetM(prhs[4]);
  }
  if (((rn != vn) && (rn != 0)) || ((mn != vn) && (mn != 0)))
    mexErrMsgTxt("Point's data have not the same number of frames.");

  btk::Acquisition::Pointer acq = btk_MOH_get_object<btk::Acquisition>(prhs[0]);

  if (vn != acq->GetPointFrameNumber())
    mexErrMsgTxt("Frame number mismatching.");

  btk::Point::Pointer point;
  if (mxIsChar(prhs[1]))
  {
    int strlen = (mxGetM(prhs[1]) * mxGetN(prhs[1]) * sizeof(mxChar)) + 1;
    char* label = (char*)mxMalloc(strlen);
    mxGetString(prhs[1], label, strlen);
    btk::Acquisition::PointIterator itPoint = acq->FindPoint(label);
    if (itPoint == acq->EndPoint())
    {
      std::string err = "No point with label: '" + std::string(label) + "'.";
      mexErrMsgTxt(err.c_str());
    }
    point = *itPoint;
    mxFree(label);
  }
  else
  {
    int idx = static_cast<int>(mxGetScalar(prhs[1])) - 1;
    if ((idx < 0) || (idx > acq->GetPointNumber()))
      mexErrMsgTxt("Point's index out of range.");
    point = acq->GetPoint(idx);
  }

  memcpy(point->GetValues().data(), mxGetPr(prhs[2]) , mxGetNumberOfElements(prhs[2]) * sizeof(double));
  if (nrhs >= 4)
    memcpy(point->GetResiduals().data(), mxGetPr(prhs[3]) , mxGetNumberOfElements(prhs[3]) * sizeof(double)); 
  if (nrhs >= 5)
    memcpy(point->GetMasks().data(), mxGetPr(prhs[4]) , mxGetNumberOfElements(prhs[4]) * sizeof(double));

  // Return updated points
  btkMEXGetPoints(acq, nlhs, plhs);
};

