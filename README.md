

##Requirement

- Qt5
- VTK6
- ITK4


##Main files
- TrackerBase.h

	This file define a base class for tracker device
	and transform structure. If you have some new 
	device, please inhert this class and implement
	the virtual funciton. Other tracking class will 
	call virtual functions in this class.

- vtkTracking3D.h/.cxx

	This function implement the main function of tracking 
	view. Most functions have very detail description.

- QtWrapvtkTracking3D.h

	This class wrap the vtkTracking3D class to qt. This class
	emit a reslice index when timer in vtkTracking3D invoke a 
	callback.


- vtkTrackingMarkCapture.h/.hxx

	This class is used for capturing marker in view and position
	returned from tracker device.

- vtkTrackingRegistration
	This class is used for registering the view coordinate and
	tracking device coordinate. It returns a transform.
	There are 2 method implemented in this file:
	1. ICP Registration method
	2. LandMarkRegistration method.
	It is recommanded to use LandmarkRegistration method.









