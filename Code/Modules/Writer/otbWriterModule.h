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
#ifndef __otbWriterModule_h
#define __otbWriterModule_h

// include the base class
#include "otbModule.h"

// include the GUI
#include "otbWriterModuleGUI.h"

// include the OTB elements
#include "otbVectorImage.h"
#include "otbImageFileWriter.h"

#include "otbVectorData.h"
#include "otbVectorDataFileWriter.h"

namespace otb
{
/** \class WriterModule
 *  \brief 
 *
 *  \sa DataObjectWrapper, DataDescriptor, DataDescriptor
 */

class ITK_EXPORT WriterModule
  : public Module, public WriterModuleGUI
{
public:
  /** Standard class typedefs */
  typedef WriterModule                 Self;
  typedef Module                        Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** New macro */
  itkNewMacro(Self);

  /** Type macro */
  itkTypeMacro(WriterModule,Module);

  /** OTB typedefs */
  /// Dataset
  typedef VectorImage<double,2>         FPVImageType;
  typedef VectorData<double>            VectorType;
  /// Writers
  typedef ImageFileWriter<FPVImageType>    FPVWriterType;
  typedef VectorDataFileWriter<VectorType> VectorWriterType;

protected:
  /** Constructor */
  WriterModule();
  /** Destructor */
  virtual ~WriterModule();
  /** PrintSelf method */
  virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

  /** Assign input by key. This method must be reimplemented in subclasses.
   *  When this method is called, key checking and data type matching
   *  is already done. */
  virtual void AssignInputByKey(const std::string & key, const DataObjectWrapper & data);

  /** The custom run command */
  virtual void Run();

  /** Callbacks */
  virtual void OpenDataSet();
  virtual void Browse();
  virtual void Cancel();

private:
  WriterModule(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  FPVWriterType::Pointer m_FPVWriter;
  VectorWriterType::Pointer m_VectorWriter;
};


} // End namespace otb

#endif