#include <osgViewer/Viewer>
#include "dimensions.h"
#include "CustomCamera.h"

osg::ref_ptr<osgViewer::Viewer> CreateWindows(osg::ref_ptr<osgViewer::Viewer> viewer)	{
	osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
    if (!wsi) 
    {
        OSG_NOTICE<<"Error, no WindowSystemInterface available, cannot create windows."<<std::endl;
        return(0);
    }
    
    unsigned int width, height;
    wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);

    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->screenNum = 0;
    traits->x = 0;
    traits->y = 0;
    traits->width = width;
    traits->height = height;
    traits->windowDecoration = false;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;

    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
    if (gc.valid())
    {
        OSG_INFO<<"  GraphicsWindow has been created successfully."<<std::endl;
    }
	else
	{
		OSG_NOTICE<<"  GraphicsWindow has not been created successfully."<<std::endl;
	}

	osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
	camera->setGraphicsContext(gc.get());
	camera->setViewport(new osg::Viewport(0,0, width, height));
	// GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
	// camera->setDrawBuffer(buffer);
	// camera->setReadBuffer(buffer);
	// camera->setClearMask( GL_DEPTH_BUFFER_BIT );

	//osg::Vec3 c = viewer->getSceneData()->getBound().center();
	//float r = viewer->getSceneData()->getBound().radius();
	//r = r * 5;
	float r = 10;
	osg::Vec3 c = osg::Vec3(0.0, 0.0, 0.0);
	
	osg::Vec3d center;
	osg::Vec3d eye;
	osg::Vec3d up;
	center.set(c.x(), c.y(), c.z());
	
	
	#ifdef BART
		eye.set(center.x(), center.y(), center.z() + r);
		up.set(0.0,1.0,0.0);
		osg::Matrixd DisplayCorrection = osg::Matrixd::rotate(osg::PI*(0), osg::Z_AXIS);
		double bottomtop = 4.0 - 0.5;
		double leftright = 5.0 - 0.5;
		double nearfar = 5.0;
	#endif
	
	#ifdef GERTJAN
		eye.set(center.x(), center.y(), center.z() + r);
		up.set(0.0,1.0,0.0);
		osg::Matrixd DisplayCorrection = osg::Matrixd::rotate(osg::PI*(1), osg::Z_AXIS);
		double bottomtop = 4.0 - 0.5;
		double leftright = 5.0 - 0.5;
		double nearfar = 4.0;
	#endif
	
	#ifdef MARTIJN
		eye.set(center.x(), center.y(), center.z() + r);
		up.set(0.0,1.0,0.0);
		osg::Matrixd DisplayCorrection = osg::Matrixd::rotate(osg::PI*(-0.5), osg::Z_AXIS);
		double bottomtop = 4.0 - 0.5;
		double leftright = 5.0 - 0.5;
		double nearfar = 5.0;
	#endif
	
	viewer->setCameraManipulator(new CustomCamera(viewer->getCamera()) );
	camera->setViewMatrixAsLookAt(eye, center, up);
	camera->setProjectionMatrixAsFrustum(-leftright, leftright, -bottomtop, bottomtop, r - nearfar, r + nearfar);	
	
	return(viewer);
}