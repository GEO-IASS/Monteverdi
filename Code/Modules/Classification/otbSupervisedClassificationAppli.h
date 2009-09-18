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
#ifndef __otbSupervisedClassificationAppli_h
#define __otbSupervisedClassificationAppli_h

// Disabling deprecation warning
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#endif
#include "otbSupervisedClassificationAppliGUI.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "otbVectorImage.h"
#include "otbClassificationViewer.h"
#include "otbSVMImageClassificationFilter.h"
#include "otbSVMSampleListModelEstimator.h"
#include "otbChangeLabelImageFilter.h"
#include "otbClass.h"
#include "otbVectorData.h"
#include "otbVectorDataFileReader.h"
#include "otbVectorDataFileWriter.h"
#include "itkPreOrderTreeIterator.h"
#include "itkVariableSizeMatrix.h"
#include "otbPersistentVectorizationImageFilter.h"
#include "itkListSample.h"
#include "otbSVMClassifier.h"

namespace otb
{
/** \class SupervisedClassificationAppli
 * \brief
 *
 * Use FLTK gui.
 *
 */
class ITK_EXPORT SupervisedClassificationAppli
      : public itk::ProcessObject, public SupervisedClassificationAppliGUI
{
public:
  /** Standard class typedefs */
  typedef SupervisedClassificationAppli      Self;
  typedef itk::ProcessObject                 Superclass;
  typedef itk::SmartPointer<Self>            Pointer;
  typedef itk::SmartPointer<const Self>      ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(SupervisedClassificationAppli,itk::ProcessObject);

  /// Template pixel type
  typedef double         InputPixelType;
  typedef unsigned short LabeledPixelType;
  typedef unsigned char ColorPixelType;

  /// Image widget
  typedef ClassificationViewer<InputPixelType,LabeledPixelType>           ImageViewerType;
  typedef  ImageViewerType::Pointer                                       ImageViewerPointerType;
  typedef  ImageViewerType::FormListType                                  FormListType;
  typedef  ImageViewerType::PolygonType                                   PolygonType;
  typedef  ImageViewerType::PolygonListType                               PolygonListType;
  typedef  ImageViewerType::FullWidgetType                                FullWidgetType;
  typedef  FullWidgetType::Pointer                                        FullWidgetPointerType;
  typedef  ImageViewerType::ScrollWidgetType                              ScrollWidgetType;
  typedef  ScrollWidgetType::Pointer                                      ScrollWidgetPointerType;
  typedef  PolygonListType::Pointer                                       PolygonListPointerType;

  /// Image Type and related typedefs
  typedef  FullWidgetType::ImageType                                      ImageType;
  typedef  FullWidgetType::OverlayImageType                               OverlayImageType;
  typedef  OverlayImageType::Pointer                                      OverlayImagePointerType;
  typedef otb::Image<LabeledPixelType,2>                                  LabeledImageType;
  typedef  ImageType::Pointer                                             ImagePointerType;
  typedef  ImageType::ConstPointer                                        ImageConstPointerType;
  typedef  ImageType::RegionType                                          RegionType;
  typedef  ImageType::SizeType                                            SizeType;
  typedef  ImageType::IndexType                                           IndexType;
  typedef  ImageType::OffsetType                                          OffsetType;
  typedef  ImageType::PixelType                                           PixelType;
  typedef  FullWidgetType::ColorType                                      ColorType;
  typedef otb::Class<LabeledPixelType,ColorType>                          ClassType;
  typedef  ClassType::Pointer                                             ClassPointerType;
  typedef std::vector<ClassPointerType>                                   ClassesMapType;

  /// Classification typedefs
  typedef otb::SVMImageClassificationFilter<ImageType,LabeledImageType>   ClassificationFilterType;
  typedef  ClassificationFilterType::ModelType                            ModelType;
  typedef  ModelType::Pointer                                             ModelPointerType;
  typedef itk::VariableLengthVector<InputPixelType>                       SampleType;
  typedef itk::Statistics::ListSample<SampleType>                                 ListSampleType;
  typedef itk::FixedArray<LabeledPixelType,1>                                     TrainingSampleType;
  typedef itk::Statistics::ListSample<TrainingSampleType>                         TrainingListSampleType;
  typedef otb::SVMSampleListModelEstimator<ListSampleType,TrainingListSampleType> EstimatorType;
  typedef otb::ChangeLabelImageFilter<LabeledImageType,OverlayImageType>          ChangeLabelFilterType;
  typedef otb::PersistentVectorizationImageFilter<LabeledImageType,PolygonType>   VectorizationFilterType;
  typedef  EstimatorType::Pointer                                         EstimatorPointerType;
  typedef  ClassificationFilterType::Pointer                              ClassificationFilterPointerType;
  typedef  ChangeLabelFilterType::Pointer                                 ChangeLabelFilterPointerType;
  typedef  VectorizationFilterType::Pointer                               VectorizationFilterPointerType;
  typedef otb::SVMClassifier<ListSampleType,LabeledPixelType>             ClassifierType;
  typedef itk::VariableSizeMatrix<double>                                 ConfusionMatrixType;
  typedef  ListSampleType::Pointer                                        ListSamplePointerType;
  typedef  TrainingListSampleType::Pointer                                TrainingListSamplePointerType;


  /** Vector data handling */
  typedef  VectorData<double,2,short unsigned int>                        VectorDataType;
  typedef  VectorDataType::Pointer                                        VectorDataPointerType;
  typedef  VectorDataFileReader<VectorDataType>                           VectorDataFileReaderType;
  typedef  VectorDataFileReaderType::Pointer                              VectorDataFileReaderPointerType;
  typedef  VectorDataFileWriter<VectorDataType>                           VectorDataFileWriterType;
  typedef  VectorDataFileWriterType::Pointer                              VectorDataFileWriterPointerType;
  typedef  VectorDataType::DataNodeType                                   DataNodeType;
  typedef  DataNodeType::Pointer                                          DataNodePointerType;
  typedef  VectorDataType::DataTreeType                                   DataTreeType;
  typedef  DataTreeType::Pointer                                          DataTreePointerType;
  typedef  itk::PreOrderTreeIterator<DataTreeType>                        TreeIteratorType;

  itkSetObjectMacro(InputImage,ImageType);
  itkGetMacro(Output,OverlayImageType::Pointer);
  itkSetStringMacro(ModelFileName);
  itkSetStringMacro(ROIsImageFileName);

  /** Main methods */

  virtual void Show(void);
  virtual void Build(void);
  virtual void ReInitButtons(void);
  virtual void Update(void);
  virtual void LoadImage();
  virtual void LoadSVMModel();
  virtual void LoadROIsImage();
  virtual void AddClass();


protected:
  /** Constructor */
  SupervisedClassificationAppli();

  /** destructor */
  ~SupervisedClassificationAppli();

  /** File selection Callbacks */

  virtual void SaveClassifAsVectorData();
  virtual void OpenSVMModel();
  virtual void SaveSVMModel();
  virtual void ImportVectorData();
  virtual void ExportVectorData();
  virtual void ExportAllVectorData();
  virtual void ImportROIsImage();

  /** Setup Callbacks */

  virtual void SVMSetup();
  virtual void SVMSetupOk();
  virtual void SVMSetupCancel();
  virtual void VisualisationSetup();
  virtual void VisualisationSetupOk();
  virtual void VisualisationSetupCancel();
  virtual void GrayscaleSet();
  virtual void RGBSet();
  virtual void ComplexSet();

  /** Class edition callbacks */

  virtual void ClassSelected();
  virtual void RemoveClass();
  virtual void ChangeClassName();
  virtual void ChangeClassNameOk();
  virtual void ChangeClassColor();
  virtual void TrainingSetSelected();
  virtual void ValidationSetSelected();

  /** ROI edition callbacks */

  virtual void EndPolygon();
  virtual void ClearROIs();
  virtual void EraseLastPoint();
  virtual void EraseLastROI();
  virtual void UsePolygon();
  virtual void ChangeTrainingSetOpacity();

  /** Focus */
  virtual void ROIFocus();

  /** Classification callbacks */
  virtual void Learn();
  virtual void SaveOutputResults();
  virtual void Validate();
  virtual void SetupClassification();

  /** Application callbacks*/
  virtual void QuitCallback();

  /** Other methods */
  virtual void UpdateClassInfo();
  virtual void UpdateImageInfo();
  virtual ClassPointerType GetSelectedClass();
  virtual int GetSelectedROI();
  virtual void GenerateTrainingSamplesFromROIs();
  virtual void GenerateValidationSamplesFromROIs();
  virtual void JointlyGenerateTrainingAndValidationSamplesFromROIs();
  virtual void ResetClassification();
  virtual void ShowResults();
  virtual void ShowImage();

private:
  SupervisedClassificationAppli(const Self&); // purposely not implemented
  void operator=(const Self&); // purposely not implemented

  /// Input Image 
  ImageType::Pointer           m_InputImage;
  /// Output Classified image  
  OverlayImageType::Pointer    m_Output;
  /// Model filename
  std::string m_ModelFileName;
  /// Training ROIs filename
  std::string m_ROIsImageFileName;
  /// Path history
  std::string m_LastPath;
  /// Image viewer
  ImageViewerPointerType m_ImageViewer;
  ///  Result viewer
  ImageViewerPointerType m_ResultViewer;
  /// Classification filter
  ClassificationFilterPointerType m_ClassificationFilter;
  /// Change label filter
  ChangeLabelFilterPointerType m_ChangeLabelFilter;
  /// Vectorization filter
  VectorizationFilterPointerType m_VectorizationFilter;
  /// SVM Estimator
  EstimatorPointerType m_Estimator;
  /// SVM model
  ModelPointerType m_Model;
  /// Class map
  ClassesMapType m_ClassesMap;
  /// Current Label
  LabeledPixelType m_CurrentLabel;
  /// Training set
  PolygonListPointerType m_TrainingSet;
  /// Validation set
  PolygonListPointerType m_ValidationSet;

  /// Learning sample list
  ListSamplePointerType m_TrainingListSample;
  /// Learning label sample list
  TrainingListSamplePointerType m_TrainingListLabelSample;
  /// Validation Sample list
  ListSamplePointerType m_ValidationListSample;
  /// Validation label sample list
  TrainingListSamplePointerType m_ValidationListLabelSample;
};

} // end namespace otb


#endif
