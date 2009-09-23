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
#include "otbInputViewGUI.h"

#include <FL/fl_ask.H>

#include "base/ossimFilename.h"
#include "base/ossimDirectory.h"
#include "otbMacro.h"
#include "itkExceptionObject.h"



namespace otb
{


void
InputViewGUI
::BuildInputInterface()
{

//assert(m_Model) assert(m_Controller)

  // to count the number of Fl_Input_Choice to display
  unsigned int cpt =0;
  // if there are several Fl_Input_Choice to draw
  unsigned int height = 40;
  unsigned int i =0;
  InputDataDescriptorMapType lInputDataMap = m_Model->GetModuleInputsByInstanceId(m_ModuleInstanceId);
  InputDataDescriptorMapType::const_iterator it_in;

     // loop on the requiered input data of the module : m_ModuleInstanceId
     for (it_in = lInputDataMap.begin();it_in != lInputDataMap.end();it_in++)
      {


        Fl_Input_Choice *inputChoice;

        // create Input Widgets considering the needed inputs 
        inputChoice = new Fl_Input_Choice( 200,30+cpt* height, 250, 25, it_in->second.GetDataDescription().c_str() );

        /// TODO : center the widget...
        //        inputChoice->resizable(gScrollInput);

        // we check if there are convenient outputs in the modules
        std::vector<std::string> moduleInstances = m_Model->GetAvailableModuleInstanceIds();
        for(i=0;i<moduleInstances.size();i++)
        {
          // look after all the outputs of each instance of module
          OutputDataDescriptorMapType lOutputDataMap = m_Model->GetModuleOutputsByInstanceId(moduleInstances[i]);
          OutputDataDescriptorMapType::const_iterator it_out;
          for(it_out=lOutputDataMap.begin();it_out!=lOutputDataMap.end();it_out++)
          {
            // if the type is ok, we can add the label in the Fl_Input_Choice
            if(it_in->second.GetDataType() == it_out->second.GetDataType())
            {
              inputChoice->add(it_out->second.GetDataDescription().c_str());
            }
          }
        }

        gScrollInput->add(inputChoice);
        cpt++;
      }

}

// **        Callbacks         ** //

void 
InputViewGUI
::Ok()
{

// Connect 

// Start()
  //m_Model->StartModuleByInstanceId(event.GetInstanceId());
  //wInputWindow->hide();
  std::cout<< "Ok" <<std::endl;

}

void 
InputViewGUI
::Cancel()
{
 // wInputWindow->hide();
}

void 
InputViewGUI
::Show()
{
  wInputWindow->show();
}

} // end namespace otb
