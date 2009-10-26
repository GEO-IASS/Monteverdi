/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
See OTBCopyright.txt for details.


    This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE,  See the above copyright notices for more information.

=========================================================================*/

// this file defines the otbCommonTest for the test driver
// and all it expects is that you have a function called RegisterTests
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif
#include <iostream>
#include "otbTestMain.h"

void RegisterTests()
{
  REGISTER_TEST(otbSpeckleFilteringApplication);
  REGISTER_TEST(otbSpeckleFilteringModuleTest);
  REGISTER_TEST(otbReaderModuleTest);
  REGISTER_TEST(otbOrthorectificationModuleTest);
  REGISTER_TEST(otbOrthorectificationSingleImageModuleTest);
  REGISTER_TEST(otbFeatureExtractionModuleTest);
  REGISTER_TEST(otbFeatureExtractionModuleApplication);
  REGISTER_TEST(otbSupervisedClassificationModuleTest);
  REGISTER_TEST(otbWriterModuleTest);
  REGISTER_TEST(otbReaderWriterModuleTest);
  REGISTER_TEST(otbViewerModuleTest);
  REGISTER_TEST(otbWriterMVCModuleTest);
  REGISTER_TEST(otbWriterMVCModuleTest2);
  REGISTER_TEST(otbPanSharpeningModuleTest);
  REGISTER_TEST(otbProjectionModuleTest);
  REGISTER_TEST(otbExtractROIModuleTest);
  REGISTER_TEST(otbExtractROIVectorImageModuleTest);
  REGISTER_TEST(otbHomologousPointExtractionModuleTest);
  REGISTER_TEST(otbConcatenateModuleTest);
  REGISTER_TEST(otbAlgebraModuleTest);
  REGISTER_TEST(otbChangeDetectionModuleTest);
  REGISTER_TEST(otbGCPToSensorModelModuleTest);
  REGISTER_TEST(otbThresholdModuleTestNew);
  REGISTER_TEST(otbThresholdModuleTest);
}
