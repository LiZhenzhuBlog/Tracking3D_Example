/*
Author: QIN Shuo
Date: 2015/12/29
Organization: RC-MIC (CUHK)
Description:
	registration function in tracking
*/


#include "vtkTrackingRegistration.h"

//============== Base Class ================//
// cannot instantiate abstract class
//vtkStandardNewMacro(vtkTrackingRegistrationBase);
vtkTrackingRegistrationBase::vtkTrackingRegistrationBase()
{
	src_Points = vtkSmartPointer<vtkPoints>::New();
	target_Points = vtkSmartPointer<vtkPoints>::New();
	transform_matrix = vtkSmartPointer<vtkMatrix4x4>::New();
}
vtkTrackingRegistrationBase::~vtkTrackingRegistrationBase()
{
}

void vtkTrackingRegistrationBase::SetSourcePoints(vtkPoints* input)
{
	src_Points = input;
}

void vtkTrackingRegistrationBase::SetTargetPoints(vtkPoints* input)
{
	target_Points = input;
}

vtkSmartPointer<vtkMatrix4x4> vtkTrackingRegistrationBase::GetTransformMatrix()
{
	return transform_matrix;
}


//===================== ICP Registration====================//

vtkStandardNewMacro(vtkTrackingICPRegistration)
vtkTrackingICPRegistration::vtkTrackingICPRegistration()
{
	m_icp = vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	max_steps = 50;
}
vtkTrackingICPRegistration::~vtkTrackingICPRegistration()
{}
void vtkTrackingICPRegistration::GenerateTransform()
{
	auto source_poly = vtkSmartPointer<vtkPolyData>::New();
	auto target_poly = vtkSmartPointer<vtkPolyData>::New();

	//convert point to polydata first
	source_poly->SetPoints(src_Points);
	target_poly->SetPoints(target_Points);

	//to accerlate calculation: convert to vertex
	auto source_vertex = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	source_vertex->SetInputData(source_poly);
	source_vertex->Update();
	auto target_vertex = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	target_vertex->SetInputData(target_poly);
	target_vertex->Update();

	m_icp->SetSource(source_vertex->GetOutput());
	m_icp->SetTarget(target_vertex->GetOutput());
	m_icp->SetMeanDistanceModeToRMS();
	m_icp->GetLandmarkTransform()->SetModeToRigidBody();
	m_icp->CheckMeanDistanceOn();
	m_icp->StartByMatchingCentroidsOn();
	m_icp->SetMaximumNumberOfIterations(max_steps);
	m_icp->SetMaximumMeanDistance(0.0000001);
	m_icp->SetMaximumNumberOfLandmarks(src_Points->GetNumberOfPoints());
	m_icp->GetLandmarkTransform()->SetModeToRigidBody();
	m_icp->Modified();
	m_icp->Update();

	transform_matrix = m_icp->GetMatrix();
}


//========================Land Mark Registration=========================//

vtkStandardNewMacro(vtkTrackingLandMarkRegistration)
vtkTrackingLandMarkRegistration::vtkTrackingLandMarkRegistration()
{
	m_landmarkTransform = vtkSmartPointer<vtkLandmarkTransform>::New();
}
vtkTrackingLandMarkRegistration::~vtkTrackingLandMarkRegistration()
{}
void vtkTrackingLandMarkRegistration::GenerateTransform()
{
	m_landmarkTransform->SetSourceLandmarks(src_Points);
	m_landmarkTransform->SetTargetLandmarks(target_Points);
	m_landmarkTransform->SetModeToRigidBody();
	m_landmarkTransform->Update(); //should this be here?

	transform_matrix = m_landmarkTransform->GetMatrix();
}





