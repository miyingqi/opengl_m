#pragma once
#include<glad.h>
#include<gtc/matrix_transform.hpp>
enum DIRECTION {
	C_FRONT,
	C_BACK,
	C_LEFT,
	C_RIGHT,
	C_SHIFT,
	C_UP
};

struct CAMERA_IN {
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
};
struct CAMERA_EULER {
	float lastX,
		lastY,
		YAW,
		PITCH,
		FOV;
	bool firstMouse;
};
struct SPEED {
	float M_speed;
	float S_speed;
};
class Camera {
public:
	CAMERA_IN base;
	CAMERA_EULER euler;
	SPEED speed{ 3.0f,10.0f };
	unsigned int wid, hei;
	Camera(glm::vec3 camerapos, int width, int height);
	glm::mat4 lookAT()const;
	glm::mat4 lookpro()const;
	void cameraMove(DIRECTION dire, float dTime);
	void ProcessMouseMovement(float xpos, float ypos);
	void ProcessMouseScroll(double yoffset);
private:
	void updateEuler();
};