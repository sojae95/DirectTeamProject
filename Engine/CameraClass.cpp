////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PCH.h"
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_maxYaw = D3DXToRadian(.0f);
	m_maxPitch = D3DXToRadian(5.0f);
	m_maxVelocity = 1.0f;
	m_speed = 1.0f;
	m_invertY = FALSE;
	m_invertX = FALSE;
	m_enableYMovement = TRUE;
	m_position = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}

void CameraClass::MoveForward(float units)
{
	if (m_enableYMovement)
	{
		m_velocity += m_look * units;
	}
	else
	{
		D3DXVECTOR3 moveVector(m_look.x, 0.0f, m_look.z);
		D3DXVec3Normalize(&moveVector, &moveVector);
		moveVector *= units;
		m_velocity += moveVector;
	}
}

void CameraClass::Strafe(float units)
{
	m_velocity += m_right * units;
}

void CameraClass::Yaw(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}

	//radians = (m_invertX) ? -radians : radians;
	//m_maxYaw -= radians;
	//if (m_yaw > m_maxYaw)
	//{
	//	radians += m_yaw - m_maxYaw;
	//}
	//else if (m_yaw < -m_maxYaw)
	//{
	//	radians += m_yaw + m_maxYaw;
	//}

	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &m_up, radians);
	D3DXVec3TransformNormal(&m_right, &m_right, &rotation);
	D3DXVec3TransformNormal(&m_look, &m_look, &rotation);

}

void CameraClass::Pitch(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}

	radians = (m_invertY) ? -radians : radians;
	m_pitch -= radians;
	if (m_pitch > m_maxPitch)
	{
		radians += m_pitch - m_maxPitch;
	}
	else if (m_pitch < -m_maxPitch)
	{
		radians += m_pitch + m_maxPitch;
	}

	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &m_right, radians);
	D3DXVec3TransformNormal(&m_up, &m_up, &rotation);
	D3DXVec3TransformNormal(&m_look, &m_look, &rotation);
}
void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void CameraClass::SetSpeed(float speed)
{
	m_speed = speed;
}

D3DXVECTOR3 CameraClass::GetPosition()
{
	return m_position;
}

D3DXVECTOR3 CameraClass::GetRotation()
{
	return m_rotation;
}

float CameraClass::GetSpeed()
{
	return m_speed;
}


void CameraClass::Render()
{
	// Cap velocity to max velocity
	if (D3DXVec3Length(&m_velocity) > m_maxVelocity)
	{
		m_velocity = *(D3DXVec3Normalize(&m_velocity, &m_velocity)) * m_maxVelocity;
	}

	// Move the camera
	m_position += m_velocity * m_speed;
	// Could decelerate here. I'll just stop completely.
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_lookAt = m_position + m_look;

	// Calculate the new view matrix
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_lookAt, &up);

	// Set the camera axes from the view matrix
	m_right.x = m_viewMatrix._11;
	m_right.y = m_viewMatrix._21;
	m_right.z = m_viewMatrix._31;
	m_up.x = m_viewMatrix._12;
	m_up.y = m_viewMatrix._22;
	m_up.z = m_viewMatrix._32;
	m_look.x = m_viewMatrix._13;
	m_look.y = m_viewMatrix._23;
	m_look.z = m_viewMatrix._33;

	// Calculate yaw and pitch
	float lookLengthOnXZ = sqrtf(m_look.z * m_look.z + m_look.x * m_look.x);
	m_pitch = atan2f(m_look.y, lookLengthOnXZ);
	m_yaw = atan2f(m_look.x, m_look.z);

	return;
}



float CameraClass::GetYaw()
{
	return m_yaw;
}

float CameraClass::GetPitch()
{
	return m_pitch;
}

void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}