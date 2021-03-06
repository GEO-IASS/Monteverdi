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

// this file defines the otbCommonTest for the test driver
// and all it expects is that you have a function called RegisterTests


#include "otbTestMain.h"

void RegisterTests()
{
  REGISTER_TEST(otbImageWidgetNew);
  REGISTER_TEST(otbImageWidget);
  REGISTER_TEST(otbImageWidgetImageDump);
  REGISTER_TEST(otbImageWidgetActionHandlerNew);
  REGISTER_TEST(otbImageWidgetControllerNew);
  REGISTER_TEST(otbImageWidgetController);
  REGISTER_TEST(otbImageLayerNew);
  REGISTER_TEST(otbStandardRenderingFunctionNew);
  REGISTER_TEST(otbRenderingImageFilterNew);
  REGISTER_TEST(otbRenderingImageFilterScalar);
  REGISTER_TEST(otbRenderingImageFilterVector);
  REGISTER_TEST(otbRenderingImageFilterVectorWithExpNegativeTransfer);
  REGISTER_TEST(otbRenderingImageFilterAmplitude);
  REGISTER_TEST(otbRenderingImageFilterPhase);
  REGISTER_TEST(otbImageLayerScalar);
  REGISTER_TEST(otbImageLayerVector);
  REGISTER_TEST(otbLayerBasedModelNew);
  REGISTER_TEST(otbImageLayerRenderingModelNew);
  REGISTER_TEST(otbImageLayerRenderingModelSingleLayer);
  REGISTER_TEST(otbImageLayerGeneratorNew);
  REGISTER_TEST(otbImageLayerGeneratorScalar);
  REGISTER_TEST(otbImageLayerGeneratorVector);
}
