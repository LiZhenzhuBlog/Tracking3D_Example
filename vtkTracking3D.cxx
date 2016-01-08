/*
Author: QIN Shuo
Date: 2015/12/29
Organization: RC-MIC (CUHK)
Description:
tracking 3d object
*/






#include "vtkTracking3D.h"


vtkStandardNewMacro(vtkTracking3D); //New() function
vtkTracking3D::vtkTracking3D()
{
	m_interval = 100;
	m_CurrentRenderer = vtkSmartPointer<vtkRenderer>::New();
	m_RendererCollection = vtkSmartPointer<vtkRendererCollection>::New();
	m_RenderWindow = vtkSmartPointer< vtkRenderWindow >::New();
	m_ActorCollection = vtkSmartPointer < vtkActorCollection >::New();
	//m_ActorCollection = m_CurrentRenderer->GetActors();
	m_PropCollection = vtkSmartPointer < vtkPropCollection > ::New();
	m_PropCollection = m_CurrentRenderer->GetViewProps();
	
	m_Interactor = vtkSmartPointer < vtkRenderWindowInteractor >::New();
	m_InteractorStyle = vtkSmartPointer < vtkInteractorStyleImage > ::New();
	m_InteractCallBack = vtkSmartPointer<vtkCallbackCommand> ::New();
	m_TimerCallBack = vtkSmartPointer<vtkCallbackCommand>::New();

	m_tracker = new TrackerType;

}
vtkTracking3D::~vtkTracking3D()
{
	delete m_tracker; //There is error if I use static_cast
}

// Please be noted that:
//   m_ActorCollection is used to manage actors but no view function
//   if you want to remove an actor from view, you must remove from
//   renderer
//   All manipulation of the actors will take effect only from renderer
// The following functions implement the management of actor list
int vtkTracking3D::AddObject(vtkSmartPointer< vtkActor > act)
{
	m_ActorCollection->AddItem(act);
	m_CurrentRenderer->AddActor(act);
	return 0;
}

int vtkTracking3D::AddPolySource(vtkSmartPointer<vtkPolyData> poly)
{
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(poly);
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	this->AddObject(actor);
	return 1;
}


/*
Description:
	Link index of actor and tracking tool
	Linkage of tool and actor is checked in callback, 
	be free to use it anywhere
Input:
	obj_index:   actor index
	too_index:   tool index

Return:
	0: success
	1: fail, actor index out of range
	2: fail, tool index out of range
Note: 
	Index count from 0
*/
int vtkTracking3D::ConnectObjectTracker(int obj_index, int tool_index)
{
	if (obj_index >= m_ActorCollection->GetNumberOfItems())
	{
		std::cout << "actor index out of range" << std::endl;
		return 1;
	}
	if (m_tracker->GetToolValidation(tool_index) != 0)
	{
		std::cout << "tool index out of range" << std::endl;
		return 2;
	}
	m_Obj_Tool_Map[obj_index] = tool_index;
	return 0;
}

/*
Description:
	Disconnect actor and tracking tool by index
Input:
	obj_index:   actor index
Return:
	0: success
	1: fail, actor index out of range
	2: Not connected
Note:
	Index count from 0
*/
int vtkTracking3D::DisConnectObjectTracker(int obj_index)
{
	if (obj_index >= m_ActorCollection->GetNumberOfItems())
	{
		std::cout << "actor index out of range" << std::endl;
		return 1;
	}
	auto it = m_Obj_Tool_Map.find(obj_index);
	if (it!=m_Obj_Tool_Map.end())
	{
		m_Obj_Tool_Map.erase(it);
		return 0;
	}
	else
	{
		std::cout << "no connection" << std::endl;
		return 2;
	}
}

//get vtkactor pointer from a vtkActorCollection 
vtkActor* vtkTracking3D::GetActorPointer(vtkPropCollection* collection, int index)
{
	if (collection->GetNumberOfItems()>0 && collection->GetNumberOfItems() >= index)
	{
		return static_cast<vtkActor*>(collection->GetItemAsObject(index));
	}
	else
		return NULL;
}

// index start from 0
int vtkTracking3D :: SetOpacity(int index, float opacity) 
{
	if (m_ActorCollection->GetNumberOfItems() > 0 && m_ActorCollection->GetNumberOfItems()>=index)
	{
		//static_cast<vtkActor*>(m_ActorCollection->GetItemAsObject(index))->GetProperty()->SetOpacity(opacity);
		GetActorPointer(m_ActorCollection, index)->GetProperty()->SetOpacity(opacity);
		return 0;
	}
	else
		return 1;
}
int vtkTracking3D::SetColor(int index, double r, double g, double b)
{
	if (m_ActorCollection->GetNumberOfItems() > 0 && m_ActorCollection->GetNumberOfItems() >= index)
	{
		//static_cast<vtkActor*>(m_ActorCollection->GetItemAsObject(index))->GetProperty()->SetOpacity(opacity);
		GetActorPointer(m_ActorCollection, index)->GetProperty()->SetColor(r,g,b);
		return 0;
	}
	else
		return 1;
}
int vtkTracking3D::SetColor(int index, double* rgb)
{
	if (m_ActorCollection->GetNumberOfItems() > 0 && m_ActorCollection->GetNumberOfItems() >= index)
	{
		//static_cast<vtkActor*>(m_ActorCollection->GetItemAsObject(index))->GetProperty()->SetOpacity(opacity);
		GetActorPointer(m_ActorCollection, index)->GetProperty()->SetColor(rgb);
		return 0;
	}
	else
		return 1;
}

/*

*/
int vtkTracking3D::SetTransform(int index, QIN_Transform_Type* trans)
{

	if (m_ActorCollection->GetNumberOfItems() > 0 && m_ActorCollection->GetNumberOfItems() >= index)
	{
		// construct transform
		m_Transform->Translate(trans->x, trans->y, trans->z);
		m_Transform->RotateWXYZ(trans->q0, trans->qx, trans->qy, trans->qz);

		//static_cast<vtkActor*>(m_ActorCollection->GetItemAsObject(index))->GetProperty()->SetOpacity(opacity);
		//GetActorPointer(m_ActorCollection, index)->SetUserTransform(m_Transform);
		//
		GetActorPointer(m_ActorCollection, index)->SetPosition(trans->x, trans->y, trans->z);
		GetActorPointer(m_ActorCollection, index)->SetOrientation(trans->qx, trans->qy, trans->qz);
		//GetActorPointer(m_ActorCollection, index)->SetOrientation();
		return 0;
	}
	else
		return 1;

}

/*

*/
int vtkTracking3D::RemoveObject(int index)
{
	m_CurrentRenderer->RemoveActor(GetActorPointer(m_ActorCollection,index));
	m_ActorCollection->RemoveItem(index);
	return 0;
}
int vtkTracking3D::RemoveObject(vtkActor* obj)
{
	m_ActorCollection->RemoveItem(obj);
	m_CurrentRenderer->RemoveActor(obj);
	return 0;
}

void vtkTracking3D::SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> inct)
{
	this->m_Interactor = inct;
}



//Note: when you assign a new renderwindow, the interactor
//      and actor collection or other property will be reset
//      to the new window
void vtkTracking3D::SetWindow(vtkSmartPointer<vtkRenderWindow> win)
{
	m_RenderWindow = win;
}

vtkSmartPointer<vtkRenderWindow> vtkTracking3D::GetRenderWindow()
{
	return m_RenderWindow;
}
vtkSmartPointer<vtkRenderWindowInteractor> vtkTracking3D::GetInteractor()
{
	return m_Interactor;
}


void vtkTracking3D::SetInteractorStyle( vtkInteractorStyle* style)
{
	m_InteractorStyle = style;
	m_Interactor->SetInteractorStyle(style);
}

// install / reinstall the visiualizaiton pipeline here
// must be done if any of the visi-pipline is modified
int vtkTracking3D::InstallPipeline()
{
	m_RenderWindow->AddRenderer(m_CurrentRenderer);
	m_RenderWindow->SetInteractor(m_Interactor);
	m_Interactor->SetInteractorStyle(m_InteractorStyle);
	m_Interactor->Initialize();  //this line is very important to start timer

	//register callbacks
	m_InteractCallBack->SetClientData(this);
	m_InteractCallBack->SetCallback(KeypressCallbackFunction);
	m_TimerCallBack->SetClientData(this);
	m_TimerCallBack->SetCallback(TimerCallbackFunction);
	m_Interactor->AddObserver(vtkCommand::KeyPressEvent, m_InteractCallBack);
	m_Interactor->AddObserver(vtkCommand::TimerEvent, m_TimerCallBack);
	//
	m_Transform = vtkSmartPointer<vtkTransform>::New();
	m_Transform->PostMultiply(); //this is the key line

	m_CurrentRenderer->ResetCamera();

	return 1;
}
void vtkTracking3D::RefreshView()
{
	m_RenderWindow->Render();
}

void vtkTracking3D::StartTracking()
{
	m_TimerID = m_Interactor->CreateRepeatingTimer(m_interval);
}
void vtkTracking3D::StopTracking()
{
	m_Interactor->DestroyTimer(m_TimerID);
}

void KeypressCallbackFunction(vtkObject* caller,long unsigned int eventId,void* clientData,void* callData)
{
	vtkSmartPointer<vtkTracking3D> tracking = static_cast<vtkTracking3D*> (clientData);
	
	vtkRenderWindowInteractor *iren =
		static_cast<vtkRenderWindowInteractor*>(caller);

	std::string key = iren->GetKeySym();
	
	//add actor
	if (key == "a")
	{
		tracking->StartTracking();
	}
	//remove actor
	else if (key == "b")
	{
		tracking->StopTracking();
	}
	//change color
	else if (key == "c")
	{
		tracking->SetColor(1,0.5,0.6,0.8);
	}
	//transform actor
	else if (key == "d")
	{

	}
	//chagne opacity
	else if (key == "x")
	{
		tracking->SetOpacity(1,0.3);
	}
	tracking->GetRenderWindow()->Render();
}


/*

*/
void TimerCallbackFunction(
	vtkObject* caller,
	long unsigned int eventId,
	void* clientData,
	void* callData
	)
{
	vtkSmartPointer<vtkTracking3D> tracking = static_cast<vtkTracking3D*> (clientData);
	
	for (auto it = tracking->m_Obj_Tool_Map.begin(); it != tracking->m_Obj_Tool_Map.end(); ++it)
	{
		//QIN_Transform_Type trans;
		QIN_Transform_Type* temp;
		//memset(&trans, 0, sizeof(QIN_Transform_Type));
		temp = tracking->m_tracker->GetTransform(it->second);
		if (temp != NULL)
		{
			//memcpy(&trans, temp, sizeof(QIN_Transform_Type));
			tracking->SetTransform(it->second, temp);
			std::cout <<it->first<<":"<< temp->x<< " " << temp->y<< " " << temp->z<< std::endl;
		}
		else
		{
			std::cout << "transform invalid" << std::endl;
		}
	}
	tracking->GetRenderWindow()->Render();
}
