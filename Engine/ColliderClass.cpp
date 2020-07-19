#include "PCH.h"
#include "ColliderClass.h"

ColliderClass::ColliderClass()
{
}

ColliderClass::ColliderClass(const ColliderClass &)
{
}

ColliderClass::~ColliderClass()
{
}

bool ColliderClass::ColliderCheck(D3DXMATRIX objmatrix, D3DXVECTOR3 playerpos, float radius, ModelClass *model)
{
	float fplayerRadius = 1.0f;
	D3DXVECTOR3 objpos;

	objpos.x = objmatrix._41;
	objpos.y = objmatrix._42;
	objpos.z = objmatrix._43;
	
	float fDistance = fplayerRadius + radius;
	float fLength = D3DXVec3Length(&(objpos - playerpos));

	if (fLength <= fDistance && !model->GetCheckColl())
	{
		model->SetCheckColl(true);
		return true;
	}
	else if(fLength > fDistance && model->GetCheckColl())
	{
		model->SetCheckColl(false);
	}

	return false;
}
