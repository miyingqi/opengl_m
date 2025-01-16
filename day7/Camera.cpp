#include"Camera.h"
Camera::Camera(glm::vec3 camerapos, int width, int height) {
	base.cameraPos = camerapos;
	if( camerapos.y==0)
	{
		base.cameraFront.y = 1.0f;
	}
	base.cameraFront=glm::normalize(glm::vec3(0.0f,0.0f,-camerapos.z));
	
	base.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	euler.lastX = width / 2.0;
	euler.lastY = height / 2.0;
	euler.YAW = -90.0f;
	euler.PITCH = 0.0f;
	euler.FOV = 45.0f;
	euler.firstMouse = true;
	wid = width; hei = height;
}
glm::mat4 Camera::lookAT() const {
	return glm::lookAt(base.cameraPos, base.cameraPos + base.cameraFront, base.cameraUp);
}
glm::mat4 Camera::lookpro() const {
	return glm::perspective(glm::radians(euler.FOV), (float)wid / (float)hei, 0.1f, 100.0f);
}
void Camera::cameraMove(DIRECTION dire, float dTime) {
	float sp = speed.M_speed * dTime;

	if (dire == C_SHIFT)
		base.cameraPos -= base.cameraUp * sp;
	if (dire == C_FRONT)
		base.cameraPos += glm::vec3(base.cameraFront.x, 0.0f, base.cameraFront.z) * sp;
	if (dire == C_BACK)
		base.cameraPos -= glm::vec3(base.cameraFront.x, 0.0f, base.cameraFront.z) * sp;
	if (dire == C_LEFT)
		base.cameraPos -= glm::normalize(glm::cross(base.cameraFront, base.cameraUp)) * sp;
	if (dire == C_RIGHT)
		base.cameraPos += glm::normalize(glm::cross(base.cameraFront, base.cameraUp)) * sp;
	if (dire == C_UP)
		base.cameraPos += base.cameraUp * sp;
}
void Camera::ProcessMouseMovement(float xpos, float ypos) {
	if (euler.firstMouse)
	{
		euler.lastX = xpos;
		euler.lastY = ypos;
		euler.firstMouse = false;
	}

	float xoffset = xpos - euler.lastX;
	float yoffset = euler.lastY - ypos;
	euler.lastX = xpos;
	euler.lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	euler.YAW += xoffset;
	euler.PITCH += yoffset;

	if (euler.PITCH > 89.0f)
		euler.PITCH = 89.0f;
	if (euler.PITCH < -89.0f)
		euler.PITCH = -89.0f;
	updateEuler();
}
void Camera::ProcessMouseScroll(double yoffset) {
	if (euler.FOV >= 1.0f && euler.FOV <= 45.0f)
		euler.FOV -= yoffset;
	if (euler.FOV <= 1.0f)
		euler.FOV = 1.0f;
	if (euler.FOV >= 45.0f)
		euler.FOV = 45.0f;
}
void Camera::updateEuler() {
	glm::vec3 front;
	front.x = cos(glm::radians(euler.YAW)) * cos(glm::radians(euler.PITCH));
	front.y = sin(glm::radians(euler.PITCH));
	front.z = sin(glm::radians(euler.YAW)) * cos(glm::radians(euler.PITCH));
	base.cameraFront = glm::normalize(front);
}