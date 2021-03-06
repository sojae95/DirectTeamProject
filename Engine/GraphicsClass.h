////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "InputClass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "TextClass.h"
#include "BitmapClass.h"
#include "textureshaderclass.h"
#include "SoundClass.h"
#include "ColliderClass.h"
#include "ParticleSystemClass.h"
#include "ParticleShaderClass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 5000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND, InputClass*);
	void Shutdown();
	bool Frame(int, float, int, int, int);

private:
	bool Render(float);

private:
	TextClass* m_Text;
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	InputClass* m_Input;
	std::vector<ModelClass*> m_Models;
	vector<D3DXMATRIX>	 m_objMatrices;
	ModelClass* m_spaceship;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	TextureShaderClass* m_TextureShader;
	BitmapClass	*m_Bitmap;
	std::vector<BitmapClass*> m_UI;
	int m_screenHeight, m_screenWidth;
	D3DXMATRIX m_baseViewMatrix;
	int	 m_numOfPolygons;
	int  m_numOfObject;
	D3DXMATRIX m_TextMatrix;
	SoundClass *m_BackGroundSound;
	SoundClass *m_EffectSound;
	ColliderClass * m_Col;
	float  m_radius[30];
	bool m_bIsTextControl;
	int m_iHp;

	bool m_bIsClear;
	bool m_bIsColParticle;
	bool m_bIsGameStart;

	float m_fParticleTime = 0.0f;

	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;
	ParticleSystemClass* m_CollisionParticleSystem;

};
#endif