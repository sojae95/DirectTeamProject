////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////



////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void MoveForward(float units);
	void Strafe(float units);
	void Yaw(float radians);
	void Pitch(float radians);

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void SetSpeed(float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	float GetSpeed();
	float GetYaw();
	float GetPitch();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

private:
	D3DXMATRIX  m_viewMatrix;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_look;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_lookAt;
	D3DXVECTOR3 m_velocity;
	float       m_yaw;
	float       m_pitch;
	float       m_maxPitch;
	float       m_maxYaw;
	float       m_maxVelocity;
	float       m_fov;
	float       m_aspect;
	float       m_nearPlane;
	float       m_farPlane;
	float		m_speed;
	bool        m_invertY;
	bool        m_invertX;
	bool        m_enableYMovement;
};

#endif