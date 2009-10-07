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
#include "otbCachingModule.h"
#include <FLU/Flu_File_Chooser.h>
#include <FL/Fl.H>
#include <algorithm>
#include "otbFileName.h"

namespace otb
{
/** Constructor */
CachingModule::CachingModule()
{
  // Describe inputs
  this->AddInputDescriptor<FloatingVectorImageType>("InputDataSet","Dataset to write.");
  this->AddTypeToInputDescriptor<FloatingImageType>("InputDataSet");
  this->AddTypeToInputDescriptor<CharVectorImageType>("InputDataSet");

  m_CachingPath = "Caching/";
  m_FilePath = "";
  m_Done = false;
}

/** Destructor */
CachingModule::~CachingModule()
{
  // Here we try to delete any created file if possible
  ossimFilename ofname(m_FilePath);

// try to remove the file
  if(ofname.exists())
    {
    std::cout<<"Cleaning up cache file "<<m_FilePath<<std::endl;
    ofname.remove();
    }
}

/** PrintSelf method */
void CachingModule::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  // Call superclass implementation
  Superclass::PrintSelf(os,indent);
}


void CachingModule::UpdateProgressBar( float progress )
{
  itk::OStringStream oss1, oss2;
  oss1.str("");
  oss1<<"Caching dataset  ("<<std::floor(100*progress)<<"%)";
  oss2.str("");
  oss2<<std::floor(100*progress);
  oss2<<"%";
  Fl::lock();
  pBar->value( progress );
  wCachingWindow->copy_label(oss1.str().c_str());
  pBar->copy_label( oss2.str().c_str() );
  Fl::awake();
  Fl::unlock();
}


void CachingModule::ThreadedWatch()
{
  this->BuildGUI();

  Fl::lock();
  pBar->minimum(0);
  pBar->maximum(1);
  wCachingWindow->show();
  Fl::unlock();
  float progress = 0;
  float progressOld = -1;



  while( progress != 1)
    {
    Sleep(500);
    if(m_WritingProcess.IsNotNull())
      {
      progress = m_WritingProcess->GetProgress();
      }
    float diffProg = progress - progressOld;
    
    if(diffProg > 0.01)
      {
      this->UpdateProgressBar( progress );
      progressOld = progress;
      }
    }
  
  // Wait for the reader to be set
  while(!m_Done)
    {
    Sleep(500);
    }

  Fl::lock();
  this->UpdateProgressBar( 1. );
  this->UpdateProgressBar( 0. );
   
  // Changing back label
  wCachingWindow->copy_label("Caching dataset ...");

  // Close the window
  wCachingWindow->hide();

  // Notify new outputs
  this->NotifyOutputsChange();

  Fl::unlock();
  }

void CachingModule::ThreadedRun()
{ 
  FloatingVectorImageType::Pointer vectorImage = this->GetInputData<FloatingVectorImageType>("InputDataSet");
  FloatingImageType::Pointer singleImage = this->GetInputData<FloatingImageType>("InputDataSet");
  CharVectorImageType::Pointer charVectorImage = this->GetInputData<CharVectorImageType>("InputDataSet");

  Superclass::InputDataDescriptorMapType::const_iterator inputIt = this->GetInputsMap().find("InputDataSet");

  if(inputIt == this->GetInputsMap().end())
    {
    itkExceptionMacro(<<"Could not find input with key InputDataSet");
    }

  std::string sourceId = inputIt->second.GetNthData(0).GetSourceInstanceId();
  std::string outputKey = inputIt->second.GetNthData(0).GetSourceOutputKey();

  // Create the caching dir if not already created
  ossimFilename cachingDir(m_CachingPath);
  cachingDir.createDirectory();

  // Create description
  itk::OStringStream oss;
  oss<<"Cached data from "<<sourceId<<" ("<<outputKey<<")";
  std::string description = oss.str();
  oss.str("");

  // Ensure no white spaces
  std::replace(sourceId.begin(),sourceId.end(),' ','_');
  std::replace(outputKey.begin(),outputKey.end(),' ','_');

  // Build cached file name
  oss<<m_CachingPath<<sourceId<<outputKey<<".tif";
  m_FilePath = oss.str();
  oss.str("");

  if ( charVectorImage.IsNotNull() ) 
    {
    // Writing
    CharVWriterType::Pointer charVWriter = CharVWriterType::New();
    charVWriter->SetInput(charVectorImage);
    charVWriter->SetFileName(m_FilePath);
    m_WritingProcess = charVWriter;
    charVWriter->Update();

    // Reading
    CharVReaderType::Pointer charVReader = CharVReaderType::New();
    charVReader->SetFileName(m_FilePath);
    charVReader->UpdateOutputInformation();
    m_ReadingProcess = charVReader;
    this->AddOutputDescriptor(charVReader->GetOutput(),"CachedData",description);
    }

  else if ( vectorImage.IsNotNull() ) 
    {
    // Writing
    FPVWriterType::Pointer fPVWriter = FPVWriterType::New();
    fPVWriter->SetInput(vectorImage);
    fPVWriter->SetFileName(m_FilePath);
    m_WritingProcess = fPVWriter;
    fPVWriter->Update();

    // Reading
    FPVReaderType::Pointer fPVReader = FPVReaderType::New();
    fPVReader->SetFileName(m_FilePath);
    fPVReader->UpdateOutputInformation();
    m_ReadingProcess =  fPVReader;
    this->AddOutputDescriptor(fPVReader->GetOutput(),"CachedData",description);

    }
  else if( singleImage.IsNotNull() )
    {
    // Writing
    FPWriterType::Pointer fPWriter = FPWriterType::New();
    fPWriter->SetInput(singleImage);
    fPWriter->SetFileName(m_FilePath);
    m_WritingProcess = fPWriter;
    fPWriter->Update();

    // Reading
    FPReaderType::Pointer fPReader = FPReaderType::New();
    fPReader->SetFileName(m_FilePath);
    fPReader->UpdateOutputInformation();
    m_ReadingProcess =  fPReader;
    this->AddOutputDescriptor(fPReader->GetOutput(),"CachedData",description);
    }
  else
    {
    m_Done = true;
    itkExceptionMacro(<<"Input data are NULL.");
    }

  m_Done = true;
}


} // End namespace otb


