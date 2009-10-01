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
#ifndef __otbReaderModule_h
#define __otbReaderModule_h

// include the base class
#include "otbModule.h"

// include the GUI
#include "otbReaderModuleGUI.h"

// include the OTB elements
#include "otbVectorImage.h"
#include "otbImageFileReader.h"

#include "otbObjectList.h"
#include "otbMultiToMonoChannelExtractROI.h"
#include "otbVectorImageToAmplitudeImageFilter.h"

#include "otbVectorData.h"
#include "otbVectorDataFileReader.h"

namespace otb
{
/** \class ReaderModule
 *  \brief 
 *
 *  \sa DataObjectWrapper, DataDescriptor, DataDescriptor
 */

class ITK_EXPORT ReaderModule
  : public Module, public ReaderModuleGUI
{
public:
  /** Standard class typedefs */
  typedef ReaderModule                 Self;
  typedef Module                        Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** New macro */
  itkNewMacro(Self);

  /** Type macro */
  itkTypeMacro(ReaderModule,Module);

  /** OTB typedefs */
  /// Dataset
  typedef VectorImage<double,2>         FloatingVectorImageType;
  typedef Image<double,2>               FloatingImageType;
  typedef VectorData<double>            VectorType;
  /// Readers
  typedef ImageFileReader<FloatingVectorImageType>    FPVReaderType;
  typedef VectorDataFileReader<VectorType> VectorReaderType;

  /// Extract ROIs
  typedef MultiToMonoChannelExtractROI<double,double> ExtractROIImageFilterType;
  typedef ObjectList<ExtractROIImageFilterType>       ExtractROIImageFilterListType;
  
  // Amplitude filter
  typedef VectorImageToAmplitudeImageFilter<FloatingVectorImageType,FloatingImageType> AmplitudeFilterType;

protected:
  /** Constructor */
  ReaderModule();
  /** Destructor */
  virtual ~ReaderModule();
  /** PrintSelf method */
  virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

  /** The custom run command */
  virtual void Run();

  /** Callbacks */
  virtual void OpenDataSet();
  virtual void Browse();
  virtual void Cancel();

private:
  ReaderModule(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  FPVReaderType::Pointer m_FPVReader;
  VectorReaderType::Pointer m_VectorReader;
  AmplitudeFilterType::Pointer m_AmplitudeFilter;
  ExtractROIImageFilterListType::Pointer m_ExtractROIFilterList;
};


} // End namespace otb

#endif
