/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009-2012, Arnaud Barré
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

#ifndef __btkAcquisitionFileIOFactory_p_h
#define __btkAcquisitionFileIOFactory_p_h

#include "btkAcquisitionFileIOHandle.h"

#define BTK_IO_REGISTER_ACQUISITION_FILE_RDRW(classname) \
  BTK_IO_REGISTER_ACQUISITION_FILE(classname, true, true)

#define BTK_IO_REGISTER_ACQUISITION_FILE_RONLY(classname) \
  BTK_IO_REGISTER_ACQUISITION_FILE(classname, true, false)

#define BTK_IO_REGISTER_ACQUISITION_FILE_WONLY(classname) \
  BTK_IO_REGISTER_ACQUISITION_FILE(classname, false, true)

#define BTK_IO_REGISTER_ACQUISITION_FILE(classname, read, write) \
  this->list.push_back(AcquisitionFileIOHandle::New(btk::AcquisitionFileIOHandleFunctorConverter<classname>::New(), read, write));
   
#define BTK_IO_ACQUISITON_FILE_FACTORY_INIT \
   AcquisitionFileIOHandles::AcquisitionFileIOHandles() \
   : list()

namespace btk
{
  class AcquisitionFileIOHandles
  {
  public:
    typedef std::list<AcquisitionFileIOHandle::Pointer>::iterator Iterator;
    typedef std::list<AcquisitionFileIOHandle::Pointer>::const_iterator ConstIterator;
    AcquisitionFileIOHandles();
    std::list<AcquisitionFileIOHandle::Pointer> list;
  };
  
  template <class T>
  class AcquisitionFileIOHandleFunctorConverter : public AcquisitionFileIOHandle::Functor
  {
  public:
    typedef SharedPtr<AcquisitionFileIOHandleFunctorConverter> Pointer;
    static Pointer New() {return Pointer(new AcquisitionFileIOHandleFunctorConverter<T>());};
    virtual AcquisitionFileIO::Pointer GetFileIO() const {return T::New();};
  private:
    AcquisitionFileIOHandleFunctorConverter() : AcquisitionFileIOHandle::Functor() {};
    AcquisitionFileIOHandleFunctorConverter(const AcquisitionFileIOHandleFunctorConverter& ); // Not implemented.
    AcquisitionFileIOHandleFunctorConverter& operator=(const AcquisitionFileIOHandleFunctorConverter& ); // Not implemented.
  };
}

#endif // __btkAcquisitionFileIOFactory_p_h