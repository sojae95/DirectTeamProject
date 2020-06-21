#include "PCH.h"
#include "ColliderClass.h"

ColliderClass::ColliderClass()
{
	m_bIsCheckCol = false;
}

ColliderClass::ColliderClass(const ColliderClass &)
{
}

ColliderClass::~ColliderClass()
{
}

bool ColliderClass::ColliderCheck(D3DXMATRIX objmatrix, D3DXVECTOR3 playerpos, float radius)
{
	float fplayerRadius = 1.0f;
	D3DXVECTOR3 objpos;


	objpos.x = objmatrix._41;
	objpos.y = objmatrix._42;
	objpos.z = objmatrix._43;
	
	float fDistance = fplayerRadius + radius;
	float fLength = D3DXVec3Length(&(objpos - playerpos));

	if (fLength <= fDistance && !m_bIsCheckCol)
	{
		m_bIsCheckCol = true;
		return true;
	}
	else if(fLength > fDistance && m_bIsCheckCol)
	{
		m_bIsCheckCol = false;
		return false;
	}

	return false;

}
