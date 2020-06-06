////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PCH.h"
#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_Light = 0;
	bIsALight = true;
	bIsDLight = false;
	bIsSLight = false;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, InputClass* pInput)
{
	bool result;
	D3DXMATRIX baseViewMatrix;
	// Create the Direct3D object.
	m_Input = pInput;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 2.0f, -20.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	char* fileNames[] = {
		"../Engine/data/sword.obj",
		"../Engine/data/doll.obj",
		"../Engine/data/M1911.obj",
		"../Engine/data/cube.obj"
	};

	WCHAR* textures[] = {
		L"../Engine/data/t_sword.dds",
		L"../Engine/data/t_doll.dds",
		L"../Engine/data/t_M1911.dds",
		L"../Engine/data/seafloor.dds"
	};

	// Create the model object.
	for (int i = 0; i < 4; i++)
	{
		ModelClass* newModel = new ModelClass;
		result = newModel->Initialize(m_D3D->GetDevice(), fileNames[i], textures[i]);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

		m_Models.push_back(newModel);
	}

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}
	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth,
		screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-0.5f, -2.0f, 0.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(30.0f);

	m_spaceship = new ModelClass;
	result = m_spaceship->Initialize(m_D3D->GetDevice(),
		"../Engine/data/spaceship.obj", L"../Engine/data/spaceship.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	for (auto it = m_Models.begin(); it != m_Models.end(); )
	{
		if (*it)
		{
			(*it)->Shutdown();
			delete (*it);
			it = m_Models.erase(it);
		}
		else ++it;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	return;
}


bool GraphicsClass::Frame(int fps, float frameTime, int cpu, int screenWidth, int screenHeight)
{
	bool result;
	int dir = 1;
	int deltaX, deltaY;
	const int cameraSpeed = m_Camera->GetSpeed();
	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	m_Input->GetMouseDeltaPosition(deltaX, deltaY);
	m_Camera->Yaw(deltaX * frameTime * 0.00018f);
	m_Camera->Pitch(deltaY * frameTime * 0.00018f);


	if (m_Input->GetKey(KeyCode::W)) m_Camera->MoveForward(dir * frameTime);
	if (m_Input->GetKey(KeyCode::A)) m_Camera->Strafe(-dir * frameTime);
	if (m_Input->GetKey(KeyCode::S)) m_Camera->MoveForward(-dir * frameTime);
	if (m_Input->GetKey(KeyCode::D)) m_Camera->Strafe(dir * frameTime);

	if (m_Input->GetKey(KeyCode::SPACE)) { m_Camera->SetSpeed(cameraSpeed * 1.2f); }
	else { m_Camera->SetSpeed(cameraSpeed); }

	result = m_Text->SetFPS(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_Text->SetCPU(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	m_numOfPolygons = 0;
	for (auto model : m_Models) m_numOfPolygons += model->GetPolygonsCount();
	
	result = m_Text->SetPoly(m_numOfPolygons, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix , orthoMatrix , objRotateMatrix[4];
	D3DXVECTOR3 cameraPosition;
	D3DXMATRIX rotationX, rotationY, rotationZ;
	bool result;


	cameraPosition = m_Camera->GetPosition();
	D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	for (int i = 0; i < 4; ++i) objRotateMatrix[i] = worldMatrix;
	D3DXMatrixTranslation(&objRotateMatrix[0], 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&objRotateMatrix[1], -4.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&objRotateMatrix[2], 4.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&objRotateMatrix[3], 0.0f, -2.0f, 0.0f);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMatrixIdentity(&rotationX);
	D3DXMatrixIdentity(&rotationY);
	D3DXMatrixIdentity(&rotationZ);
	D3DXMatrixRotationY(&rotationX, rotation);
	D3DXMatrixRotationY(&rotationY, rotation);
	D3DXMatrixRotationY(&rotationZ, rotation);



	D3DXMatrixMultiply(&objRotateMatrix[0], &objRotateMatrix[0], &rotationX);
	D3DXMatrixMultiply(&objRotateMatrix[1], &objRotateMatrix[1], &rotationY);
	D3DXMatrixMultiply(&objRotateMatrix[2], &objRotateMatrix[2], &rotationZ);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	for (int i = 0; i < m_Models.size() - 1; i++)
	{
		m_Models[i]->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
			objRotateMatrix[i], viewMatrix, projectionMatrix,
			m_Models[i]->GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) return false;
	}

	m_Models[3]->Render(m_D3D->GetDeviceContext());
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[3]->GetIndexCount(),
		objRotateMatrix[3], viewMatrix, projectionMatrix,
		m_Models[3]->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) return false;


	D3DXMATRIX SpaceShipMatrix;
	D3DXMATRIX mat, ShipView;
	D3DXMatrixScaling(&mat, 0.03f, 0.03f, 0.03f);
	D3DXMatrixRotationYawPitchRoll(&ShipView, m_Camera->GetYaw(), -m_Camera->GetPitch(), 0);
	cameraPosition = m_Camera->GetPosition();
	D3DXMatrixTranslation(&SpaceShipMatrix, cameraPosition.x  , cameraPosition.y - 0.2f, cameraPosition.z + 0.2f );
	SpaceShipMatrix = mat * ShipView * SpaceShipMatrix;


	//Render the player gun
	  m_spaceship->Render(m_D3D->GetDeviceContext());
	  result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_spaceship->GetIndexCount(),
		SpaceShipMatrix, viewMatrix, projectionMatrix, m_spaceship->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) return false;

	m_D3D->TurnOnAlphaBlending();
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	m_D3D->TurnOffAlphaBlending();

	m_D3D->EndScene();

	return true;
}