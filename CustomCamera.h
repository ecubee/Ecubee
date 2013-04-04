#include <osgGA/CameraManipulator>

#define CAMERA_DISTANCE		60.0
#define CAMERA_BEGIN_POS	osg::Vec3(0.0, 0.0, CAMERA_DISTANCE);


class CustomCamera : public osgGA::CameraManipulator	{
	public:
		CustomCamera(osg::Camera* cam) : _cam(cam), _xAngle(0), _yAngle(0) {}
		virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
		virtual void setByInverseMatrix( const osg::Matrixd &matrix );
		virtual void setByMatrix( const osg::Matrixd &matrix );
		virtual osg::Matrixd getInverseMatrix() const;
		virtual osg::Matrixd getMatrix() const;
		void setXAngle(const float ang);
		void setYAngle(const float ang);
		virtual ~CustomCamera() {};
	protected:
		osg::ref_ptr<osg::Camera> _cam;
		float _xAngle;
		float _yAngle;
};