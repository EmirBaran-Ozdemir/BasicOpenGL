#pragma once

#include "libs.h"

template<class T> inline T operator~ (T a) { return (T)~(int)a; }
template<class T> inline T operator| (T a, T b) { return (T)((int)a | (int)b); }
template<class T> inline T operator& (T a, T b) { return (T)((int)a & (int)b); }
template<class T> inline T operator^ (T a, T b) { return (T)((int)a ^ (int)b); }
template<class T> inline T& operator|= (T& a, T b) { return (T&)((int&)a |= (int)b); }
template<class T> inline T& operator&= (T& a, T b) { return (T&)((int&)a &= (int)b); }
template<class T> inline T& operator^= (T& a, T b) { return (T&)((int&)a ^= (int)b); }

enum CAMERA_DIR
{
	
	CAMERA_DIR_NONE = 0,
	//  00001
	CAMERA_DIR_FRONT = 1, 
	//  000010
	CAMERA_DIR_BACK = 0b000010,
	//  000100
	CAMERA_DIR_LEFT = 0b000100,
	//  001000
	CAMERA_DIR_RIGHT = 0b001000,
	//  010000
	CAMERA_DIR_UP = 0b010000, 
	//  100000
	CAMERA_DIR_DOWN = 0b100000
};

class Camera
{
private:
	//. Variables
	glm::vec3 m_pos;
	glm::quat m_rotation;
	//! Projection
	glm::mat4 m_projection;
	float m_speed;
	float m_fov;
	float m_nearPlane;
	float m_farPlane;
public:
	//. Constructor-Destructor
	Camera(float aspect, float fov, float nearPlane, float farPlane, glm::vec3 pos,glm::vec3 camFront,float speed = 0.002f);
	~Camera();
	//. Functions
	glm::mat4 getViewMatrix();
	glm::mat4 getProjection();
	void updateProjection(float aspect);
	void move(CAMERA_DIR dir);
	void updateUpVector();

	void updateInputs();
};

