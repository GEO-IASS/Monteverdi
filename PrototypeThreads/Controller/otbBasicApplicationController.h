#ifndef __otbBasicApplicationController_h
#define __otbBasicApplicationController_h

#include "otbBasicApplicationControllerInterface.h"
#include "otbBasicApplicationView.h"

#include "otbImageWidgetController.h"
#include "otbWidgetResizingActionHandler.h"
#include "otbChangeExtractRegionActionHandler.h"
#include "otbPixelDescriptionActionHandler.h"
#include "otbMouseClickActionHandler.h"
#include "itkMultiThreader.h"

namespace otb
{
class ITK_EXPORT BasicApplicationController
      : public BasicApplicationControllerInterface
{
public:
  /** Standard class typedefs */
  typedef BasicApplicationController          Self;
  typedef BasicApplicationControllerInterface Superclass;
  typedef itk::SmartPointer<Self>          Pointer;
  typedef itk::SmartPointer<const Self>    ConstPointer;

  /** Standard type macros */
  itkTypeMacro(BasicApplicationController,Superclass);
  itkNewMacro(Self);


  /** Widgets controller and action handlers */
  typedef BasicApplicationView::ImageViewType              ImageViewType;
  typedef BasicApplicationModel::VisualizationModelType    VisualizationModelType;

  typedef ImageWidgetController                                     WidgetsControllerType;
  typedef WidgetResizingActionHandler
    <VisualizationModelType,ImageViewType>                          ResizingHandlerType;
  typedef ChangeExtractRegionActionHandler
      <VisualizationModelType,ImageViewType>                        ChangeRegionHandlerType;

  /** Set the pointer to the view */
  void SetView(BasicApplicationView * view);

  /** Get the widgets controller */
  itkGetObjectMacro(WidgetsController,WidgetsControllerType);


  /** User action */
  virtual void OpenImage( const char * filename );
  virtual void RunLoop();

  bool IsModelUpdating()
  {
    return m_Model->IsUpdating();
  }
protected:
  /** Constructor */
  BasicApplicationController();
  /** Destructor */
  virtual ~BasicApplicationController();

  static ITK_THREAD_RETURN_TYPE ThreadFunction(void*);

private:
  BasicApplicationController(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** Pointer to the view */
  BasicApplicationView * m_View;

  /** Widgets controller */
  WidgetsControllerType::Pointer             m_WidgetsController;

  /** Action handlers */
  ResizingHandlerType::Pointer               m_ResizingHandler;
  ChangeRegionHandlerType::Pointer           m_ChangeRegionHandler;

  itk::MultiThreader::Pointer m_Threader;

};
} //end namespace otb

#endif
