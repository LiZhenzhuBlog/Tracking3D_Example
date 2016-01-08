
#include "vtkTracking3D.h"
#include "QinStyle.h"


#include "vtkSmartPointer.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRendererCollection.h"
#include "vtkActorCollection.h"

#include "vtkSTLReader.h"


#include "vtkSphereSource.h"
#include "vtkConeSource.h"
#include "vtkCylinderSource.h"

#include "vtkTrackingRegistration.h"
#include "vtkTrackingMarkCapture.h"
/*
Test Function for tracking device
*/
void TestTrackingDevice()
{
	vtkSmartPointer<vtkSphereSource> sphere =
		vtkSmartPointer<vtkSphereSource>::New();
	sphere->SetCenter(0, 0, 0);
	sphere->SetRadius(50);
	sphere->Update();
	vtkSmartPointer<vtkConeSource> cone =
		vtkSmartPointer<vtkConeSource>::New();
	cone->SetHeight(80);
	cone->SetRadius(50);
	cone->Update();
	vtkSmartPointer<vtkCylinderSource> cylinder =
		vtkSmartPointer<vtkCylinderSource>::New();
	cylinder->SetHeight(80);
	cylinder->SetRadius(60);
	cylinder->Update();

	vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName("E:/QinShuoTShape.stl");
	reader->Update();


	auto track = vtkSmartPointer<vtkTracking3D>::New();


	track->AddPolySource(sphere->GetOutput());
	track->AddPolySource(cone->GetOutput());
	track->AddPolySource(cylinder->GetOutput());

	//auto win1 = vtkSmartPointer<vtkRenderWindow>::New();
	//track->SetWindow(win1);
	auto interactorx = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera >::New();
	track->SetInteractorStyle(style);
	track->SetInteractor(interactorx);
	track->InstallPipeline();

	track->m_tracker->ConfigureTracker();
	Sleep(20);

	track->m_tracker->StartTracking();

	Sleep(20);

	track->ConnectObjectTracker(0, 0);
	track->ConnectObjectTracker(1, 1);
	track->ConnectObjectTracker(2, 2);

	track->GetRenderWindow()->Render();
	track->GetInteractor()->Start();

}

void TestRegistration()
{
	auto reg1 = vtkSmartPointer <vtkTrackingICPRegistration > ::New();
	auto reg2 = vtkSmartPointer<vtkTrackingLandMarkRegistration>::New();

	auto src_points = vtkSmartPointer<vtkPoints>::New();
	auto dst_points = vtkSmartPointer<vtkPoints>::New();

	float v1[9][3] = {
		{ 0, 0, 0 },
		{ 1, 0, 0 },
		{ 1, 1, 0 },
		{ 1, 1, 1 },
		{ 0, 1, 0 },
		{ 0, 1, 1 },
		{ 0, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 } };

	float vv1[9][3] ={
	{ 0 + 10, 0 + 10, 0 + 10 },
	{ 1 + 10, 0 + 10, 0 + 10 },
	{ 1 + 10, 1 + 10, 0 + 10 },
	{ 1 + 10, 1 + 10, 1 + 10 },
	{ 0 + 10, 1 + 10, 0 + 10 },
	{ 0 + 10, 1 + 10, 1 + 10 },
	{ 0 + 10, 1 + 10, 1 + 10 },
	{ 0 + 10, 0 + 10, 1 + 10 },
	{ 1 + 10, 1 + 10, 1 + 10 }
	};

	for (size_t i = 0; i < 9; i++)
	{
		src_points->InsertNextPoint(v1[i]);
	}
	for (size_t i = 0; i < 9; i++)
	{
		dst_points->InsertNextPoint(vv1[i]);
	}

	reg1->SetSourcePoints(src_points);
	reg1->SetTargetPoints(dst_points);
	reg1->GenerateTransform();
	auto res1 = reg1->GetTransformMatrix();

	reg2->SetSourcePoints(src_points);
	reg2->SetTargetPoints(dst_points);
	reg2->GenerateTransform();
	auto res2 = reg2->GetTransformMatrix();

	std::cout << "\nres1:" << std::endl;
	for (int i = 0; i < 4 ; i++)
	{
		for (int j = 0; j < 4 ; j++)
			std::cout << res1->GetElement(i,j)<<",";
		std::cout << std::endl;
	}
	std::cout << "\nres2:" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << res2->GetElement(i, j) << ",";
		std::cout << std::endl;
	}
}

void TestTrackingMarkFunction()
{
	
	auto track = new PloarisVicraConfiguration ;
	
	auto mark = vtkSmartPointer< vtkTrackingMarkCapture<PloarisVicraConfiguration> >::New();
	
	mark->SetTracker(track);
	mark->SetToolIndex(1);
	mark->SetReferIndex(2);

	track->ConfigureTracker();
	track->StartTracking();
	
	while (getchar()!='q')
	{
		mark->GetNextMarker();
	}

	track->StopTracking();
}


int main(int argc, char** argv)
{
	TestTrackingMarkFunction();

	return 0;
}

