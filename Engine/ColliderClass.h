////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLIDERCLASS_H_
#define _COLLIDERCLASS_H_


//////////////
// INCLUDES //
//////////////


class ColliderClass
{
public:
	ColliderClass();
	ColliderClass(const ColliderClass&);
	~ColliderClass();

	bool ColliderCheck(D3DXMATRIX objmatrix, D3DXVECTOR3 playerpos, float radius);

private:
	bool m_bIsCheckCol;


};

#endif