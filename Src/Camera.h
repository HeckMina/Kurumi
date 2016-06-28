#pragma once
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"

namespace Kurumi
{
	class Camera 
	{
	public:
		Camera();
		glm::vec3 mPos;
		glm::vec3 mUp;
		glm::vec3 mViewPoint;

		void MoveStrafe(float delta);
		void Update();
	};
}