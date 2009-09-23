/*=========================================================================

Program:   ORFEO Toolbox
Language:  C++
Date:      $Date$
Version:   $Revision$


Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
See OTBCopyright.txt for details.


This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __otbAsynchronousModel_H
#define __otbAsynchronousModel_H


#include "otbAsynchronousProcessBase.h"
#include "otbAsynchronousProcess.h"

namespace otb
{
namespace Process
{

class AsynchronousModel : public AsynchronousProcessBase
{
 public:

  AsynchronousModel();
  virtual ~AsynchronousModel();
  

 protected: 
  virtual void Run(void * t);

 private:
  //std::vector<AsynchronousProcess> m_ProcessList;
  AsynchronousProcess * m_Process1;
  AsynchronousProcess * m_Process2;
};

} // namespace Model
} // namespace otb

#endif
