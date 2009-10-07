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

#ifndef __otbHomologousPointExtractionModuleController_h
#define __otbHomologousPointExtractionModuleController_h

#include "otbHomologousPointExtractionModuleControllerInterface.h"
#include "otbHomologousPointExtractionModuleView.h"

#include "otbImageWidgetController.h"
// Handlers list
#include "otbWidgetResizingActionHandler.h"
#include "otbChangeExtractRegionActionHandler.h"
#include "otbPixelDescriptionActionHandler.h"
#include "otbChangeScaledExtractRegionActionHandler.h"
#include "otbChangeScaleActionHandler.h"
#include "otbMouseClickActionHandler.h"
#include "otbPixelDescriptionActionHandler.h"
#include "otbPixelDescriptionModel.h"
#include "otbPixelDescriptionView.h"

namespace otb
{
class ITK_EXPORT HomologousPointExtractionModuleController
      : public HomologousPointExtractionModuleControllerInterface
{
public:
  /** Standard class typedefs */
  typedef HomologousPointExtractionModuleController          Self;
  typedef HomologousPointExtractionModuleControllerInterface Superclass;
  typedef itk::SmartPointer<Self>          Pointer;
  typedef itk::SmartPointer<const Self>    ConstPointer;

  /** Standard type macros */
  itkTypeMacro(HomologousPointExtractionModuleController,Superclass);
  itkNewMacro(Self);


  /** Widgets controller and action handlers */
  typedef HomologousPointExtractionModuleView::ImageViewType           ImageViewType;
  typedef HomologousPointExtractionModuleModel::VisualizationModelType VisualizationModelType;
  typedef HomologousPointExtractionModuleModel::VectorImageType        VectorImageType;
  typedef VectorImageType::IndexType                                   IndexType;
  typedef VectorImageType::PixelType                                   PixelType;
  typedef HomologousPointExtractionModuleModel::RGBImageType           RGBImageType;


  /** Handlers */
  typedef ImageWidgetController                                                        WidgetsControllerType;
  typedef WidgetResizingActionHandler<VisualizationModelType,ImageViewType>            ResizingHandlerType;
  typedef ChangeExtractRegionActionHandler<VisualizationModelType,ImageViewType>       ChangeRegionHandlerType;
  typedef ChangeScaledExtractRegionActionHandler<VisualizationModelType,ImageViewType> ChangeScaledRegionHandlerType;
  typedef ChangeScaleActionHandler<VisualizationModelType,ImageViewType>               ChangeScaleHandlerType;

  typedef PixelDescriptionModel<RGBImageType>                                          PixelDescriptionModelType;
  typedef PixelDescriptionActionHandler<PixelDescriptionModelType, ImageViewType>      PixelDescriptionActionHandlerType;
  typedef PixelDescriptionView<PixelDescriptionModelType>                              PixelDescriptionViewType;
  typedef PixelDescriptionViewType::Pointer                                            PixelDescriptionViewPointerType;
  


  void SetModel(ModelType* model);

  /** Set the pointer to the view */
  void SetView(HomologousPointExtractionModuleView * view);

  /** Get the widgets controller */
  itkGetObjectMacro(FirstWidgetsController,WidgetsControllerType);
  itkGetObjectMacro(SecondWidgetsController,WidgetsControllerType);

  virtual void SetFirstInputImage(HomologousPointExtractionModuleModel::VectorImageType* image)
  {
    m_Model->SetFirstInputImage(image);
  }
  virtual void SetSecondInputImage(HomologousPointExtractionModuleModel::VectorImageType* image)
  {
    m_Model->SetSecondInputImage(image);
  }

  /** Link module and pixel descriptor action handlers. */
  virtual void LinkPixelDescriptors(); 
  virtual void AddPoints( int x1, int y1, int x2, int y2 );

protected:
  /** Constructor */
  HomologousPointExtractionModuleController();
  /** Destructor */
  virtual ~HomologousPointExtractionModuleController();


private:
  HomologousPointExtractionModuleController(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** Pointer to the view */
  HomologousPointExtractionModuleView * m_View;

  /** The instance of the model */
  ModelType * m_Model;


  /** Widgets controller */
  WidgetsControllerType::Pointer             m_FirstWidgetsController;
  WidgetsControllerType::Pointer             m_SecondWidgetsController;

  /** Action handlers */
  ResizingHandlerType::Pointer               m_FirstResizingHandler;
  ChangeRegionHandlerType::Pointer           m_FirstChangeRegionHandler;
  ChangeScaledRegionHandlerType::Pointer     m_FirstChangeScaledRegionHandler;
  ChangeScaleHandlerType::Pointer            m_FirstChangeScaleHandler;

  ResizingHandlerType::Pointer               m_SecondResizingHandler;
  ChangeRegionHandlerType::Pointer           m_SecondChangeRegionHandler;
  ChangeScaledRegionHandlerType::Pointer     m_SecondChangeScaledRegionHandler;
  ChangeScaleHandlerType::Pointer            m_SecondChangeScaleHandler;

  PixelDescriptionActionHandlerType::Pointer m_FirstPixelActionHandler;
  PixelDescriptionModelType::Pointer         m_FirstPixelModel;
  PixelDescriptionViewType::Pointer          m_FirstPixelView;
  PixelDescriptionActionHandlerType::Pointer m_SecondPixelActionHandler;
  PixelDescriptionModelType::Pointer         m_SecondPixelModel;
  PixelDescriptionViewType::Pointer          m_SecondPixelView;

  bool m_ImageReady;

};
} //end namespace otb

#endif