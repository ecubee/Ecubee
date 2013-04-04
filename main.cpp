#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgUtil/Optimizer>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include "communicator.h"
#include "dimensions.h"

osg::ref_ptr<osgViewer::Viewer> CreateWindows(osg::ref_ptr<osgViewer::Viewer> viewer);
osg::ref_ptr<osg::Geode> createBox(const osg::Vec3& center,float width,float height,float depth);

#define FRAMERATE	30

int main(int argc, char * argv[])	{
	osg::ref_ptr<osg::ShapeDrawable> shape1 = new osg::ShapeDrawable;
	shape1->setShape( new osg::Box(osg::Vec3(-6.0f, 0.0f, 0.0f),
	4.0f, 8.0f, 1.0f) );
	shape1->setColor( osg::Vec4(1.0f, 0.0f, 0.0f, 0.0f) );
	osg::ref_ptr<osg::ShapeDrawable> shape2 = new osg::ShapeDrawable;
	shape2->setShape( new osg::Cylinder(osg::Vec3(6.0f, 0.0f, 0.0f),
	1.0f, 6.0f) );
	shape2->setColor( osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) );
	osg::ref_ptr<osg::ShapeDrawable> shape3 = new osg::ShapeDrawable;
	shape3->setShape( new osg::Cone(osg::Vec3(0.0f, 0.0f, 0.0f),
	2.0f, 10.0f) );
	shape3->setColor( osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) );

	osg::ref_ptr<osg::Geode> Box = createBox(osg::Vec3(0.0f,0.0f,0.0f),BOX_WIDTH,BOX_HEIGHT,BOX_DEPTH);
	
	osg::ref_ptr<osg::Geode> Shapes = new osg::Geode;
	Shapes->addDrawable( shape1.get() );
	Shapes->addDrawable( shape2.get() );
	Shapes->addDrawable( shape3.get() );

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild( Box.get() );
	root->addChild( Shapes.get() );

	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());
	
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->setSceneData( root.get() );

	viewer = CreateWindows(viewer);
	viewer->realize();
	
	// start communicator thread
	CommunicatorThread *commThread = new CommunicatorThread((CustomCamera *) viewer->getCameraManipulator());
	commThread->start();
	
	// calculate frametime
	double minFrameTime = 1.0 / FRAMERATE;

	// fixed framerate
	while (!viewer->done()) {
		osg::Timer_t startFrame = osg::Timer::instance()->tick();
		viewer->frame();
		osg::Timer_t endFrame = osg::Timer::instance()->tick();

		// wait until next frame is ready to be rendered
		double frameTime = osg::Timer::instance()->delta_s(startFrame, endFrame);
		if (frameTime < minFrameTime)
			OpenThreads::Thread::microSleep(1000000.0 * (minFrameTime - frameTime));
	}
	
	commThread->stop();
	
	return 0;
}
