#include "Camera.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Kurumi
{
	Camera::Camera()
	{
		mPos.x = 0;
		mPos.y = 0;
		mPos.z = 0;
		mUp.x = 0;
		mUp.y = 1.0f;
		mUp.z = 0;
		mViewPoint.x = 0;
		mViewPoint.y = 0;
		mViewPoint.z = -1.0f;
	}

	void Camera::MoveStrafe(float delta)
	{
		mPos.x += delta;
		mViewPoint.x += delta;
	}

	void Camera::Update()
	{
		gluLookAt(mPos.x, mPos.y, mPos.z,
			mViewPoint.x, mViewPoint.y, mViewPoint.z,
			mUp.x, mUp.y, mUp.z);
	}
}