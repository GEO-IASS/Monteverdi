/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.

  Some parts of this code are derived from ITK. See ITKCopyright.txt
  for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbFltkFilterWatcher.h"

namespace otb
{

FltkFilterWatcher
::FltkFilterWatcher(itk::ProcessObject* process,
                    int x, int y, int w, int h,
                    const char *comment)
  : FilterWatcherBase(process, comment),
    m_CurrentProgress(0)
{
  m_Window = new Fl_Window(x, y, w + 10, h + 10);
  m_Window->label(m_Comment.c_str());
  m_Window->begin();
  m_Progress = new Fl_Progress(5, 5, w, h);
  m_Progress->selection_color(FL_DARK_BLUE);
  m_Progress->minimum(0);
  m_Progress->maximum(1);
  m_Window->end();
}

FltkFilterWatcher
::~FltkFilterWatcher()
{
  delete m_Progress;
  delete m_Window;
}

void
FltkFilterWatcher
::StartFilter()
{
  m_Window->show();
  m_Progress->value(0);
  m_Progress->show();
  Fl::check();
}

void
FltkFilterWatcher
::ShowProgress()
{
  if (m_Process)
    {
    double progress = m_Process->GetProgress();

    // Update only at each 0.5 percent
    if (progress - m_CurrentProgress > 0.005)
      {
      m_Progress->value(progress);
      m_CurrentProgress = progress;
      Fl::check();
      }
    }
}

void
FltkFilterWatcher
::EndFilter()
{
  m_Window->hide();
}

} // end namespace otb
