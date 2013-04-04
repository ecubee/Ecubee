#include <osg/MatrixTransform>
#include <osgGA/GUIEventHandler>
#include <unistd.h>
#include "CustomCamera.h"
#include "dimensions.h"


bool CustomCamera::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )	{
	switch (ea.getEventType()) {
	case osgGA::GUIEventAdapter::FRAME:
		{
			osg::Vec3 eye, lookAt, up;
			double left, right, bottom, top, near, far;
			osg::Matrix rotateMat;

			rotateMat = osg::Matrix::rotate(_xAngle, osg::X_AXIS) * osg::Matrix::rotate(_yAngle, osg::Y_AXIS);
			eye = rotateMat * CAMERA_BEGIN_POS;
			
			#ifdef BART
				lookAt.set(eye.x(), eye.y(), 0.0);
				up.set(0.0, 1.0, 0.0);
				left = -H_SCREEN_WIDTH - eye.x();
				right = H_SCREEN_WIDTH - eye.x();
				bottom = -H_SCREEN_HEIGHT - eye.y();
				top = H_SCREEN_HEIGHT - eye.y();
				near = ((eye.z() - H_BOX_HEIGHT) > 0) ? (eye.z() - H_BOX_HEIGHT) : 0.0;
				far = eye.z() + H_BOX_HEIGHT;
			#endif
			#ifdef GERTJAN
				lookAt.set(eye.x(), 0.0, eye.z());
				up.set(0.0, 0.0, -1.0);
				bottom = -H_SCREEN_HEIGHT - GERTJAN_OFFSET + eye.z();
				top = H_SCREEN_HEIGHT - GERTJAN_OFFSET + eye.z();
				if (eye.y() < 0) {
					left = -H_SCREEN_WIDTH + eye.x();
					right = H_SCREEN_WIDTH + eye.x();
					near = ((-eye.y() - H_BOX_DEPTH) > 0) ? (-eye.y() - H_BOX_DEPTH) : 0.0;
					far = -eye.y() + H_BOX_DEPTH;
				} else {
					left = -H_SCREEN_WIDTH - eye.x();
					right = H_SCREEN_WIDTH - eye.x();
					near = ((eye.y() - H_BOX_DEPTH) > 0) ? (eye.y() - H_BOX_DEPTH) : 0.0;
					far = eye.y() + H_BOX_DEPTH;
				}
			#endif
			#ifdef MARTIJN
				lookAt.set(0.0, eye.y(), eye.z());
				left = -H_SCREEN_WIDTH - eye.z();
				right = H_SCREEN_WIDTH - eye.z();
				if (eye.x() < 0) {
					up.set(0.0, 1.0, 0.0);
					bottom = -H_SCREEN_HEIGHT - eye.y();
					top = H_SCREEN_HEIGHT - eye.y();
					near = ((-eye.x() - H_BOX_WIDTH) > 0) ? (-eye.x() - H_BOX_WIDTH) : 0.0;
					far = -eye.x() + H_BOX_WIDTH;
				} else {
					up.set(0.0, -1.0, 0.0);
					bottom = -H_SCREEN_HEIGHT + eye.y();
					top = H_SCREEN_HEIGHT + eye.y();
					near = ((eye.x() - H_BOX_WIDTH) > 0) ? (eye.x() - H_BOX_WIDTH) : 0.0;
					far = eye.x() + H_BOX_WIDTH;
				}
			#endif
			_cam->setViewMatrixAsLookAt(eye, lookAt, up);
			_cam->setProjectionMatrixAsFrustum(left, right, bottom, top, near, far);
		}
		break;
	default:
		break;
	}
	return false;
}

void CustomCamera::setXAngle(const float ang) {
	_xAngle = ang;
}

void CustomCamera::setYAngle(const float ang) {
	_yAngle = ang;
}

osg::Matrixd CustomCamera::getMatrix()	const {
	return(osg::Matrixd::identity());
}

osg::Matrixd CustomCamera::getInverseMatrix() const {
	const osg::Matrixd m = _cam->getViewMatrix();
	return(m);
}

void CustomCamera::setByMatrix( const osg::Matrixd &matrix ) {
	//
}

void CustomCamera::setByInverseMatrix( const osg::Matrixd &matrix ) {
	_cam->setViewMatrix(matrix);
}
