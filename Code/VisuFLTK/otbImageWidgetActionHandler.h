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
#ifndef __otbImageWidgetActionHandler_h
#define __otbImageWidgetActionHandler_h

#include "itkObject.h"
#include "itkObjectFactory.h"

namespace otb
{
/** \class ImageWidgetActionHandler
*   \brief Base class for widget action handler.
*   This class is a base class for all image widget action handlers.
*   To implement a new action handler, derive this class and implement
*   the HandleWidget*() methods. Then register an instance of your
*   handler in the ImageWidgetController.
*
*   \sa ImageWidgetController
*   \sa ImageWidget
*  \ingroup Visualization
 */

class ImageWidgetActionHandler
  : public itk::Object
{
public:
  /** Standard class typedefs */
  typedef ImageWidgetActionHandler      Self;
  typedef itk::Object                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory */
  itkNewMacro(Self);

  /** Runtime information */
  itkTypeMacro(ImageWidgetActionHandler, Object);

  /** Handle widget event
   * \param widgetId The id of the moved widget
   * \param event The event
   * \return true if the event is handled
   */
  virtual bool HandleWidgetEvent(const std::string& itkNotUsed(widgetId), int itkNotUsed(event))
  {
    return false;
  }

  /** Handle widget move
   * \param widgetId The id of the moved widget
   * \param x new x location
   * \param y new y location
   * \return true if the event is handled
   */
  virtual bool HandleWidgetMove(const std::string& itkNotUsed(widgetId), int itkNotUsed(x), int itkNotUsed(y))
  {
    return false;
  }

  /** Handle widget resize
    * \param widgetId The id of the resized widget
    * \param w new width
    * \param h new height
    * \return true if the event is handled
    */
  virtual bool HandleWidgetResize(const std::string& itkNotUsed(widgetId), int itkNotUsed(w), int itkNotUsed(h))
  {
    return false;
  }

  /** IsActive Accessors */
  itkSetMacro(IsActive, bool);
  itkGetMacro(IsActive, bool);
  itkBooleanMacro(IsActive);

protected:
  /** Constructor */
  ImageWidgetActionHandler(){m_IsActive = true; }
  /** Destructor */
  virtual ~ImageWidgetActionHandler(){}
  /** Printself method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {
    Superclass::PrintSelf(os, indent);
  }

private:
  ImageWidgetActionHandler(const Self&);    // purposely not implemented
  void operator =(const Self&); // purposely not implemented

  /** The handler is active or not */
  bool m_IsActive;

}; // end class
} // end namespace otb
#endif
