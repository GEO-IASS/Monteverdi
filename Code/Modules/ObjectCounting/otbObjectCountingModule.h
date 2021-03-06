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
#ifndef __otbObjectCountingModule_h
#define __otbObjectCountingModule_h

#include "otbEventsListener.h"

// include the base class
#include "otbModule.h"

// the MVC classes
#include "otbObjectCountingController.h"
#include "otbObjectCountingModel.h"
#include "otbObjectCountingViewGUI.h"

// include the OTB/ITK elements
#include "otbVectorImage.h"
#include "otbImage.h"
#include "otbTypeManager.h"

namespace otb
{
/** \class ObjectCountingModule
 *
 *  \brief This is the ObjectCounting module, which allows to perform
 *  ObjectCounting filtering, segmentation and clustering.
 *
 *
 */

class ITK_ABI_EXPORT ObjectCountingModule
//   : public Module, public ListenerBase
  : public Module, public EventsListener<std::string>
{
public:
  /** Standard class typedefs */
  typedef ObjectCountingModule          Self;
  typedef Module                        Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** New macro */
  itkNewMacro(Self);

  /** Type macro */
  itkTypeMacro(ObjectCountingModule, Module);

  /** Data typedefs */
  /// Dataset
  typedef TypeManager::Floating_Point_Image       FloatingImageType;
  typedef TypeManager::Floating_Point_VectorImage FloatingVectorImageType;
  typedef TypeManager::Labeled_Short_Image        LabelImageType;

  /** MVC typedefs */
  typedef otb::ObjectCountingController ControllerType;
  typedef otb::ObjectCountingModel      ModelType;
  typedef otb::ObjectCountingViewGUI    ViewType;

  /** Dataset*/
  typedef ModelType::LabeledImageType LabeledImageType;
  typedef ModelType::ImageType        ImageType;

protected:
  /** Constructor */
  ObjectCountingModule();

  /** Destructor */
  virtual ~ObjectCountingModule();

  /** Notify Monteverdi application that featureExtraction has a result */
  void Notify(const std::string& event);

  /** PrintSelf method */
  virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

  /** The custom run command */
  virtual void Run();

  /** Show the Module GUI */
  virtual bool CanShow(){return true; }

  /** Show the Module GUI */
  virtual void Show()
  {
    m_View->Show();
  }

  /** Hide the Module GUI */
  virtual void Hide()
  {
    m_View->Hide();
  }

private:
  ObjectCountingModule(const Self&); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  ControllerType::Pointer m_Controller;
  ViewType::Pointer       m_View;
  ModelType::Pointer      m_Model;
};

} // End namespace otb

#endif
