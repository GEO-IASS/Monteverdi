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
#ifndef __otbMonteverdiViewGUI_h
#define __otbMonteverdiViewGUI_h


// Disabling deprecation warning
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#endif
#include "otbMonteverdiViewGroup.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Group.H>
#include <FLU/Flu_Tree_Browser.h>

#include "otbMonteverdiModel.h"
#include "otbMonteverdiControllerInterface.h"


#include "itkObject.h"


namespace otb
{
/** \class MonteverdiViewGUI
 *
 */
class MonteverdiViewGUI
  : public MonteverdiViewGroup, public itk::Object, public EventsListener<MonteverdiEvent>
{
public:

  /** Standard class typedefs */
  typedef MonteverdiViewGUI             Self;
  typedef itk::Object                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Standard type macros */
  itkNewMacro(Self);
  itkTypeMacro(MonteverdiViewGUI,itk::Object);

  typedef MonteverdiModel                                 MonteverdiModelType;
  typedef MonteverdiControllerInterface::Pointer          MonteverdiControllerInterfacePointerType;
  typedef MonteverdiModelType::ModuleDescriptorMapType    ModuleDescriptorMapType;
  typedef MonteverdiModelType::ModuleMapType              ModuleMapType;

  typedef Module::OutputDataDescriptorMapType             OutputDataDescriptorMapType;
  typedef Module::InputDataDescriptorMapType              InputDataDescriptorMapType;



  /** Inner class to represent the content of a node */
  class NodeDescriptor
  {
    friend class MonteverdiViewGUI;
  public:
  void SetModuleInstanceId(std::string id){ m_ModuleInstanceId = id; }
  void SetOutputKey(std::string id){ m_OutputKey = id; }
  const std::string GetOutputKey(){return m_OutputKey;}
  const std::string GetModuleInstanceId(){return m_ModuleInstanceId;}
  protected:
    // key to identify the module instance
    std::string m_ModuleInstanceId;
    // key to identify the output
    std::string m_OutputKey;
  };


  /** Set the controller */
  itkGetObjectMacro(MonteverdiController,MonteverdiControllerInterface);
  itkSetObjectMacro(MonteverdiController,MonteverdiControllerInterface);


  /** Event from the model */
  virtual void Notify(const MonteverdiEvent & event);

  void UpdateTree(const std::string & instanceId);
  void Show();
  void InitWidgets();


  /** Constructor */
  MonteverdiViewGUI();

protected:

  /** Destructor */
  virtual ~MonteverdiViewGUI();

  void BuildMenus();
  void BuildTree();
  void BuildInputsGUI(const std::string & modulekey);
  void CreateModuleByKey(const char * modulekey);
  void Quit();
  void Help();


  /** Callbacks */
  static void GenericCallback(Fl_Menu_* w, void* v);
  static void HelpCallback(Fl_Menu_ *, void*);
  static void QuitCallback(Fl_Menu_ *, void*);



  typedef std::pair<Self *,std::string> CallbackParameterType;





private:

  MonteverdiViewGUI(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented


  /** Pointer to the model */
  MonteverdiModel::Pointer m_MonteverdiModel;
  /** Pointer to the controller */
  MonteverdiControllerInterface::Pointer m_MonteverdiController;

  std::vector<CallbackParameterType *> m_vector_param;

  Flu_Tree_Browser        *m_Tree;

};
}//end namespace otb

#endif
