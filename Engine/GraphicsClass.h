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
#include "textureshaderclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
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


	bool bIsDLight;
	bool bIsSLight;
	bool bIsALight;
	int	 m_numOfPolygons;
};
#endif