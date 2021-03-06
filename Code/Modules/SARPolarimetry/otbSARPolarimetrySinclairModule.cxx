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
#include "otbSARPolarimetrySinclairModule.h"

#include "otbFltkFilterWatcher.h"
#include "otbMsgReporter.h"

namespace otb
{
/** Constructor */
  SARPolarimetrySinclairModule::SARPolarimetrySinclairModule()
{
  // First, do constructor stuffs
  // Input images
  m_HHImage = ComplexImageType::New();
  m_HVImage = ComplexImageType::New();
  m_VHImage = ComplexImageType::New();
  m_VVImage = ComplexImageType::New();

  // Filters
  m_SinclairToReciprocalCovarianceMatrixFilter = SinclairToReciprocalCovarianceMatrixFilterType::New();
  m_SinclairToReciprocalCircularCovarianceMatrixFilter = SinclairToReciprocalCircularCovarianceMatrixFilterType::New();
  m_SinclairToReciprocalCoherencyMatrixFilter = SinclairToReciprocalCoherencyMatrixFilterType::New();

  m_SinclairToCovarianceMatrixFilter = SinclairToCovarianceMatrixFilterType::New();
  m_SinclairToCircularCovarianceMatrixFilter = SinclairToCircularCovarianceMatrixFilterType::New();
  m_SinclairToCoherencyMatrixFilter = SinclairToCoherencyMatrixFilterType::New();
  m_SinclairToMuellerMatrixFilter = SinclairToMuellerMatrixFilterType::New();

  // Add inputs
  this->AddInputDescriptor<ComplexImageType>("HHImage", "HH Image (mono channel complex image)");
  this->AddInputDescriptor<ComplexImageType>("HVImage", "HV Image (mono channel complex image used for reciprocal process)");
  this->AddInputDescriptor<ComplexImageType>("VHImage", "VH Image (mono channel complex image, optional)", true, false);
  this->AddInputDescriptor<ComplexImageType>("VVImage", "VV Image (mono channel complex image)");
}

/** Destructor */
SARPolarimetrySinclairModule::~SARPolarimetrySinclairModule()
{}

/** PrintSelf method */
void SARPolarimetrySinclairModule::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  // Call superclass implementation
  Superclass::PrintSelf(os, indent);
}

/** The custom run command */
void SARPolarimetrySinclairModule::Run()
{
  // While the viewer is shown, it is busy
  this->BusyOn();

  this->BuildGUI();
  this->CheckInputs();
  this->InitChecks();

  this->Show();
  
}

/** Check inputs configuration. */
void SARPolarimetrySinclairModule::CheckInputs()
{
  m_HHImage = this->GetInputData<ComplexImageType>("HHImage");
  m_HVImage = this->GetInputData<ComplexImageType>("HVImage");
  m_VHImage = this->GetInputData<ComplexImageType>("VHImage");
  m_VVImage = this->GetInputData<ComplexImageType>("VVImage");
  
  if( m_HHImage.IsNull() || m_HVImage.IsNull() || m_VVImage.IsNull() )
    {
      MsgReporter::GetInstance()->SendError("Invalid Inputs. HH, HV, VH and VV has all to be set.");
      this->Quit();
    }
}
  
  
/** Check/uncheck all */
void SARPolarimetrySinclairModule::InitChecks()
{
  // The CheckInputs methods insures that both HH, VH, HV and VV are set or not
  if(m_VHImage.IsNull())
    {
      rb_CirCov->deactivate();
      rb_Coh->deactivate();
      rb_Cov->deactivate();
      rb_Mue->deactivate();
    }
}
  
void SARPolarimetrySinclairModule::Ok()
{
  this->ClearOutputDescriptors();
  bool hasOutput = false;

  if( rb_CirCov->value() )
    {
      m_SinclairToCircularCovarianceMatrixFilter->SetInputHH(m_HHImage);
      m_SinclairToCircularCovarianceMatrixFilter->SetInputHV(m_HVImage);
      m_SinclairToCircularCovarianceMatrixFilter->SetInputVH(m_VHImage);
      m_SinclairToCircularCovarianceMatrixFilter->SetInputVV(m_VVImage);
      this->AddOutputDescriptor(m_SinclairToCircularCovarianceMatrixFilter->GetOutput(), "SinclairToCircularCovarianceMatrixFilter",
                                "Sinclair to circular covariance image");
      hasOutput = true;
    }
  if( rb_Coh->value() )
    {
      m_SinclairToCoherencyMatrixFilter->SetInputHH(m_HHImage);
      m_SinclairToCoherencyMatrixFilter->SetInputHV(m_HVImage);
      m_SinclairToCoherencyMatrixFilter->SetInputVH(m_VHImage);
      m_SinclairToCoherencyMatrixFilter->SetInputVV(m_VVImage);
      this->AddOutputDescriptor(m_SinclairToCoherencyMatrixFilter->GetOutput(), "SinclairToCoherencyMatrixFilter",
                                "Sinclair to coherency image");
      hasOutput = true;
    }
  if( rb_Cov->value() )
    {
      m_SinclairToCovarianceMatrixFilter->SetInputHH(m_HHImage);
      m_SinclairToCovarianceMatrixFilter->SetInputHV(m_HVImage);
      m_SinclairToCovarianceMatrixFilter->SetInputVH(m_VHImage);
      m_SinclairToCovarianceMatrixFilter->SetInputVV(m_VVImage);
      this->AddOutputDescriptor(m_SinclairToCovarianceMatrixFilter->GetOutput(), "SinclairToCovarianceMatrixFilter",
                                "Sinclair to covariance image");
      hasOutput = true;
    }
  if( rb_Mue->value() )
    {
      m_SinclairToMuellerMatrixFilter->SetInputHH(m_HHImage);
      m_SinclairToMuellerMatrixFilter->SetInputHV(m_HVImage);
      m_SinclairToMuellerMatrixFilter->SetInputVH(m_VHImage);
      m_SinclairToMuellerMatrixFilter->SetInputVV(m_VVImage);
      this->AddOutputDescriptor(m_SinclairToMuellerMatrixFilter->GetOutput(), "SinclairToMuellerMatrixFilter",
                                "Sinclair to Mueller image");
      hasOutput = true;
    }
  // SinclairToReciprocalCoherencyMatrixFilter
  if( rb_RecCoh->value() )
    {
      m_SinclairToReciprocalCoherencyMatrixFilter->SetInputHH( m_HHImage );
      m_SinclairToReciprocalCoherencyMatrixFilter->SetInputHV_VH( m_HVImage );
      m_SinclairToReciprocalCoherencyMatrixFilter-> SetInputVV( m_VVImage );
      this->AddOutputDescriptor(m_SinclairToReciprocalCoherencyMatrixFilter->GetOutput(), "SinclairToReciprocalCoherencyImage",
                                "Sinclair to reciprocal coherency image");
      hasOutput = true;
    }
  // SinclairToReciprocalCircularCovarianceMatrixFilter
  if( rb_RecCirCoh->value() )
    {
      m_SinclairToReciprocalCircularCovarianceMatrixFilter->SetInputHH( m_HHImage );
      m_SinclairToReciprocalCircularCovarianceMatrixFilter->SetInputHV_VH( m_HVImage );
      m_SinclairToReciprocalCircularCovarianceMatrixFilter->SetInputVV( m_VVImage );
      this->AddOutputDescriptor(m_SinclairToReciprocalCircularCovarianceMatrixFilter->GetOutput(), "SinclairToReciprocalCircularCovariance",
                                "Sinclair to reciprocal circular covariance");
      hasOutput = true;
    }
  // SinclairToReciprocalCovarianceMatrixFilter
  if( rb_RecCov->value() )
    {
      m_SinclairToReciprocalCovarianceMatrixFilter->SetInputHH( m_HHImage );
      m_SinclairToReciprocalCovarianceMatrixFilter->SetInputHV_VH( m_HVImage );
      m_SinclairToReciprocalCovarianceMatrixFilter->SetInputVV( m_VVImage );
      this->AddOutputDescriptor(m_SinclairToReciprocalCovarianceMatrixFilter->GetOutput(), "SinclairToReciprocalCovariance",
                                "Sinclair to reciprocal covariance");
      hasOutput = true;
    }
  
  if( hasOutput )
    {
      this->NotifyOutputsChange();
    }
  else
    {
      MsgReporter::GetInstance()->SendWarning( "No process selected." );
    }
  
  this->Hide();
  // Once module is closed, it is no longer busy
  this->BusyOff();
}
  
void SARPolarimetrySinclairModule::Quit()
{
  // 1First, clear any previous output
  this->ClearOutputDescriptors();
  this->Hide();
  // Once module is closed, it is no longer busy
  this->BusyOff();
}
  
void SARPolarimetrySinclairModule::CheckAll(bool val)
{
  rb_CirCov->value(val);
  rb_Coh->value(val);
  rb_Cov->value(val);
  rb_RecCoh->value(val);
  rb_Mue->value(val);
  rb_RecCirCoh->value(val);
  rb_RecCov->value(val);
}

} // End namespace otb
