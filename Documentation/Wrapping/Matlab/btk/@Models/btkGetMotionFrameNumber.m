function mfn = btkGetMotionFrameNumber(h) %#ok
%BTKGETMOTIONFRAMENUMBER Returns the number of frames in the model's motion.
% 
%  MFN = BTKGETMOTIONFRAMENUMBER(H) returns the number of frames in the model's motion.
%  The model is represented by the handle H, obtained by the use of a btk* function.

%  Author: A. Barré
%  Copyright 2009-2010 Biomechanical ToolKit (BTK).

% The following comment, MATLAB compiler pragma, is necessary to avoid 
% compiling this M-file instead of linking against the MEX-file.  Don't remove.
%# mex

error(generatemsgid('NotSupported'),'MEX file for BTKGETMOTIONFRAMENUMBER not found');

% [EOF] btkGetMotionFrameNumber.m
