#include "Camera.h"


//. Constructors
Camera::Camera(float aspect, float fov, float nearPlane, float farPlane, glm::vec3 pos, glm::vec3 camFront,float speed)
	: m_fov(fov), m_nearPlane(nearPlane), m_farPlane(farPlane), m_pos(pos), m_speed(speed)
{
	m_projection = glm::perspective(
		glm::radians(this->m_fov),
		aspect,
		this->m_nearPlane,
		this->m_farPlane
	);

	this->m_rotation = glm::lookAt(this->m_pos, (this->m_pos + camFront), glm::vec3(0, 1, 0));
}
//.Destructor
Camera::~Camera()
{

}

//. Functions
glm::mat4 Camera::getViewMatrix()
{
	//!: Position vec3 ünü matrix versiyonuna çeviriyoruz.
	glm::mat4 posMatrix = glm::translate(glm::mat4(1.f), -(this->m_pos));
	//!: Quaternion'u rotation matrixine çeviriyoruz. Quaternion'u matrixe çeviren method glm::mat4_cast
	glm::mat4 rotationMatrix = glm::mat4_cast(this->m_rotation);
	//!: Ýlk rotation çarpýmý yapýyoruz. Sonra position.
	return rotationMatrix * posMatrix;

}

glm::mat4 Camera::getProjection()
{
	return this->m_projection;
}

void Camera::updateProjection(float aspect)
{
	m_projection = glm::perspective(
		glm::radians(this->m_fov),
		aspect,
		this->m_nearPlane,
		this->m_farPlane
	);
	
}

void Camera::move(CAMERA_DIR dir)
{
	auto viewMatrix = getViewMatrix();
	auto camFront = -(glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]));
	auto camRight = glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
	
	auto camUp = glm::cross(camRight,camFront);

	glm::vec3 movement = glm::vec3(0, 0, 0);

	if (dir & CAMERA_DIR_FRONT)
		movement += camFront;
	if (dir & CAMERA_DIR_BACK)
		movement -= camFront;
	if (dir & CAMERA_DIR_LEFT)
		movement -= camRight;
	if (dir & CAMERA_DIR_RIGHT)
		movement += camRight;
	if (dir & CAMERA_DIR_UP)
		movement += camUp;
	if (dir & CAMERA_DIR_DOWN)
		movement -= camUp;
	
	movement *= this->m_speed;

	m_pos += movement;
}

void Camera::updateUpVector()
{
	//!: View matrix içinden front vectörünü getireceðiz
	auto viewMatrix = getViewMatrix();
	auto camFront = -(glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]));
	this->m_rotation = glm::lookAt(this->m_pos, (this->m_pos + camFront), glm::vec3(0, 1, 0));

}
void Camera::updateInputs()
{

}
