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
	m_TextureShader = 0;
	m_Light = 0;
	m_screenHeight = 0;
	m_screenWidth = 0;
	m_BackGroundSound = 0;
	m_EffectSound = 0;
	m_Col = 0;
	m_iHp = 3;
	m_ParticleShader = 0;
	m_ParticleSystem = 0;
	m_CollisionParticleSystem = 0;
	m_bIsClear = false;
	m_bIsColParticle = false;
	m_bIsGameStart = false;
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

	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;
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
	m_Camera->SetPosition(0.0f, 2.0f, -300.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);
	m_baseViewMatrix = baseViewMatrix;

	// ��ü ��
	const int NumOfModel = 30;
	const int NumOfUi = 6;
	// Obj ����
	char* fileNames[NumOfModel] = {
		"../Engine/data/SkyBoxTestCube.obj", //��� 
		"../Engine/data/mars.obj", // ����
		"../Engine/data/mars.obj", // ȭ��
		"../Engine/data/mars.obj",  // ��
		"../Engine/data/mars.obj", // �¾�

		"../Engine/data/mars.obj", // ����
		"../Engine/data/mars.obj", // �ݼ�
		"../Engine/data/Satalite1.obj",  // ����
		"../Engine/data/Satalite1.obj",  // ����
		"../Engine/data/Satalite1.obj",  // ����

		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺

		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺

		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺

		// ȭ������ ������ ���ƿ��� ���༺�� (25- 29)
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj", // ���༺
		"../Engine/data/Asteroid1.obj" // ���༺
	};



	// Text ����
	WCHAR* textures[NumOfModel] = {
		L"../Engine/data/SpaceBackGround.dds", // ��� �ؽ�ó
		L"../Engine/data/earth.dds",  // ���� �ؽ�ó
		L"../Engine/data/mars.dds",  // ȭ�� �ؽ�ó
		L"../Engine/data/Jupiter_diff.dds",   // �� �ؽ�ó 
		L"../Engine/data/sun.dds", // �¾�

		L"../Engine/data/mercury.dds", // ����
		L"../Engine/data/venus.dds", // �ݼ�
		L"../Engine/data/Satalite1.dds", // ����
		L"../Engine/data/Satalite1.dds", // ����
		L"../Engine/data/Satalite1.dds", // ����

		L"../Engine/data/Rock.dds", // ���༺R
		L"../Engine/data/Asteroid.dds", // ���༺
		L"../Engine/data/Asteroid.dds", // ���༺R
		L"../Engine/data/Rock.dds", // ���༺R
		L"../Engine/data/Asteroid.dds", // ���༺R

		L"../Engine/data/Asteroid.dds", // ���༺
		L"../Engine/data/Rock.dds", // ���༺R
		L"../Engine/data/Asteroid.dds",// ���༺
		L"../Engine/data/Rock.dds", // ���༺R
		L"../Engine/data/Rock.dds", // ���༺R

		L"../Engine/data/Rock.dds", // ���༺R
		L"../Engine/data/Asteroid.dds", // ���༺
		L"../Engine/data/Rock.dds",// ���༺R
		L"../Engine/data/Rock.dds", // ���༺R
		L"../Engine/data/Rock.dds", // ���༺R

		// ȭ������ ������ ���ƿ��� ���༺�� (25- 29)
		L"../Engine/data/Rock.dds", // ���༺R
		L"../Engine/data/Asteroid.dds", // ���༺
		L"../Engine/data/Rock.dds",// ���༺R
		L"../Engine/data/Rock.dds", // ���༺R
		L"../Engine/data/Asteroid.dds" // ���༺
	};

	D3DXVECTOR3 positions[] = {
		{ 0.0f, 0.0f, 0.0f},
		{ 0.0f, 0.0f, -450.0f}, // ����
		{ 0.0f, 0.0f, 500.0f},  // ȭ��
		{ -150.0f, 0.0f, 1300.0f}, // ��
		{0.0f, 500.0f, -1500.0f}, // �¾�

		{-50.0f, 0.0f, -900},     // ����
		{100.0f, 0.0f, -750},      // �ݼ�
		{100.0f, 60.0f, -450.0f}, // ���� - ���� ��
		{-50.0f, 50.0f, 500.0f}, // ���� - ȭ�� ��
		{1000.0f, 400.0f, 1000.0f}, // ���� - �ָ� �ִ� ����

		// ���� - ȭ�� (z �� ���� - (-450) ~ 500  )
		{-150.0f, 50.0f, 300.0f},//���༺R
		{150.0f, 50.0f, -100.0f},//���༺
		{-100.0f, -50.0f, 50.0f},//���༺
		{-50.0f, 30.0f, 0.0f},//���༺R
		{-150.0f, -50.0f, 100.0f},//���༺

		{-100.0f, -30.0f,-150.0f},	// ���༺
		{ 50.0f, -50.0f, -150.0f},	// ���༺R
		{ 80.0f, 80.0f, -300.0f},	// ���༺
		{ 150.0f, -150.0f, -250.0f},	// ���༺R
		{ 200.0f, 0.0f, 0.0f},	// ���༺R

		{-150.0f, 60.0f,-150.0f},	// ���༺
		{ 50.0f, -50.0f, 0.0f},	// ���༺
		{ -100.0f, 20.0f, 300.0f},	// ���༺
		{ 150.0f, -150.0f, 200.0f},	// ���༺
		{ -100.0f, 40.0f, 0.0f},	// ���༺

		// ȭ������ ������ ���ƿ��� ���༺�� (25- 29)
		{ 30.0f, 60.0f, 450.0f},	// ���༺
		{ 50.0f, -50.0f, 500.0f},	// ���༺
		{ -100.0f, 0.0f, 400.0f},	// ���༺
		{ -50.0f, 0.0f, 450.0f},	// ���༺
		{ -25.0f, -20.0f, 400.0f}	// ���༺2
	};

	// ũ�⸦ 
	D3DXVECTOR3 scales[] = {
		{ 3000.0f, 3000.0f, 3000.0f},
		{ 20.0f, 20.0f, 20.0f},    // ����
		{ 10.0f, 10.0f, 10.0f},    // ȭ��
		{ 50.0f, 50.0f, 50.0f},    // ��
		{ 100.0f, 100.0f, 100.0f}, // �¾�

		{ 10.0f, 10.0f, 10.0f}, // ����
		{ 20.0f, 20.0f, 20.0f}, // �ݼ�
		{ 0.2f, 0.2f, 0.2f},	// ����
		{ 0.2f, 0.2f, 0.2f},    // ����
		{ 3.0f, 3.0f, 3.0f},    // ���� 

		{ 0.5f, 0.5f, 0.5f}, //���༺R
		{ 0.5f, 0.5f, 0.5f}, //���༺
		{ 1.0f, 1.0f, 1.0f}, //���༺
		{ 0.5f, 0.5f, 0.5f}, //���༺R
		{ 0.5f, 0.5f, 0.5f}, //���༺

		{ 0.2f, 0.2f, 0.2f}, //���༺
		{ 0.5f, 0.5f, 0.5f}, //���༺R
		{ 0.7f, 0.7f, 0.7f}, //���༺
		{ 0.2f, 0.2f, 0.2f}, //���༺R
		{ 0.5f, 0.5f, 0.5f}, //���༺R

		{ 0.5f, 0.5f, 0.5f}, //���༺
		{ 0.8f, 0.8f, 0.8f}, //���༺
		{ 0.5f, 0.5f, 0.5f}, //���༺
		{ 0.1f, 0.1f, 0.1f}, //���༺
		{ 0.5f, 0.5f, 0.5f}, //���༺

		// ȭ������ ������ ���ƿ��� ���༺�� (25- 29)
		{ 0.5f, 0.5f, 0.5f}, //���༺
		{ 0.8f, 0.8f, 0.8f}, //���༺
		{ 0.5f, 0.5f, 0.5f}, //���༺
		{ 0.1f, 0.1f, 0.1f}, //���༺
		{ 0.5f, 0.5f, 0.5f}, //���༺
	};

	float radius[] = {
		{ 3000.0f},
		{ 20.0f},  // ����
		{ 30.0f},  // ȭ��
		{ 50.0f},  // ��
		{ 100.0f}, // �¾�

		{ 10.0f},  // ����
		{ 20.0f},  // �ݼ�
		{ 3.0f}, //����
		{ 3.0f}, //����
		{ 3.0f}, //����

		{ 15.0f},   // ���༺
		{ 15.0f},   // ���༺
		{ 30.0f},   // ���༺
		{ 15.0f},   // ���༺
		{ 15.0f},   // ���༺

		{ 6.0f},   // ���༺2
		{ 15.0f},   // ���༺2
		{ 21.0f},   // ���༺2
		{ 6.0f},   // ���༺2
		{ 15.0f},   // ���༺2

		{ 15.0f},   // ���༺2
		{ 24.0f},   // ���༺2
		{ 15.0f},   // ���༺2
		{ 3.0f},   // ���༺2
		{ 15.0f},   // ���༺2

		// ȭ������ ������ ���ƿ��� ���༺�� (25- 29)
		{ 25.0f},   // ���༺2
		{ 40.0f},   // ���༺2
		{ 25.0f},   // ���༺2
		{ 5.0f},   // ���༺2
		{ 25.0f},   // ���༺2
	};

	for (int j = 0; j < NumOfModel; ++j)
	{
		m_radius[j] = radius[j];
	}

	// UI ��ȣ 1 --> 4
	// HP      3 --> 0
	// UI�ø���� ���λ� , UI_ �ø���� �ʷϻ�

	WCHAR* Uitextures[NumOfUi] = {
		L"../Engine/data/UI4.dds", //  0 
		L"../Engine/data/UI3.dds", //  1
		L"../Engine/data/UI2.dds", //  2
		L"../Engine/data/UI1.dds",  // 3
		L"../Engine/data/ClearScene.dds", // ClearScene
		L"../Engine/data/StartScene.dds"  // StartScene
	};

	pair<int, int> UiScales[NumOfUi] = {
		{ screenWidth , screenHeight },
		{ screenWidth , screenHeight },
		{ screenWidth , screenHeight },
		{ screenWidth , screenHeight },
		{ screenWidth , screenHeight },
		{ screenWidth , screenHeight }
	};


	// Create the model object.
	D3DXMATRIX objMat, scaleMat;
	// Create the model object.
	for (int i = 0; i < NumOfModel; ++i)
	{
		ModelClass* newModel = new ModelClass;
		result = newModel->Initialize(m_D3D->GetDevice(), fileNames[i], textures[i]);
		
		
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

		m_D3D->GetWorldMatrix(objMat);
		D3DXMatrixIdentity(&scaleMat);
		D3DXMatrixTranslation(&objMat, positions[i].x, positions[i].y, positions[i].z);
		D3DXMatrixScaling(&scaleMat, scales[i].x, scales[i].y, scales[i].z);
		D3DXMatrixMultiply(&objMat, &scaleMat, &objMat);

		m_Models.push_back(newModel);
		m_objMatrices.push_back(objMat);
	}

	m_numOfObject = NumOfModel + 1; // ��� ������Ʈ + ���ۼ� 

	////////////////////////////// Ui ////////////////////////////////////////////////////////////
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

	D3DXMATRIX worldMatrix;

	m_D3D->GetWorldMatrix(worldMatrix);

	D3DXMatrixScaling(&m_TextMatrix, 3.f, 1.4f, 0.0f);
	D3DXMatrixMultiply(&m_TextMatrix, &m_TextMatrix, &worldMatrix);

	////////////////////////////// Ui ////////////////////////////////////////////////////////////

	for (int i = 0; i < NumOfUi; ++i)
	{
		BitmapClass* newUI = new BitmapClass;
		// Initialize the bitmap object.
		result = newUI->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
			Uitextures[i], UiScales[i].first, UiScales[i].second);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
			return false;
		}

		m_UI.push_back(newUI);
		// Initialize the bitmap object.
	

	}
	
	////////////////////////////// Ui ////////////////////////////////////////////////////////////

	m_Col = new ColliderClass;
	if (!m_Col)
	{
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

	// Create the texture shader object. 
	//just for SkyBox
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the textureshader object.", L"Error", MB_OK);
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
	m_Light->SetDirection(-0.5f, -2.0f, 3.0f);
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

	m_BackGroundSound = new SoundClass;

	if (!m_BackGroundSound) {
		return false;
	}

	result = m_BackGroundSound->Initialize(hwnd, "../Engine/data/BGM.wav");

	if (!result) {
		return false;
	}

	result =  m_BackGroundSound->PlayWaveFile(-2000, true);
	//m_BackGroundSound->PlayWaveFile(-2000, true);
	if (!result) {
		return false;
	}

	m_EffectSound = new SoundClass;

	if (!m_BackGroundSound) {
		return false;
	}

	result = m_EffectSound->Initialize(hwnd, "../Engine/data/Crack.wav");

	if (!result) {
		return false;
	}



	m_ParticleShader = new ParticleShaderClass;
	
	if (!m_ParticleShader) {
		return false;
	}

	result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);

	if (!result) {
		return false;
	}

	m_ParticleSystem = new ParticleSystemClass;

	if (!m_ParticleSystem) {
		return false;
	}

	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"../Engine/data/star.dds");

	if (!result) {
		return false;
	}

	m_CollisionParticleSystem = new ParticleSystemClass;

	if (!m_CollisionParticleSystem) {
		return false;
	}

	result = m_CollisionParticleSystem->Initialize(m_D3D->GetDevice(), L"../Engine/data/Smoke.dds");

	if (!result) {
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

	// Release the light shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
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

	for (auto it = m_UI.begin(); it != m_UI.end(); )
	{
		if (*it)
		{
			(*it)->Shutdown();
			delete (*it);
			it = m_UI.erase(it);
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

	if (m_BackGroundSound)
	{
		m_BackGroundSound->Shutdown();
		delete m_BackGroundSound;
		m_BackGroundSound = 0;
	}

	if (m_EffectSound)
	{
		m_EffectSound->Shutdown();
		delete m_EffectSound;
		m_EffectSound = 0;
	}

	if (m_Col)
	{
		delete m_Col;
		m_Col = 0;
	}

	if (m_ParticleShader) {
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}


	if (m_ParticleSystem) {
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	if (m_CollisionParticleSystem) {
		m_CollisionParticleSystem->Shutdown();
		delete m_CollisionParticleSystem;
		m_CollisionParticleSystem = 0;
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

	if (m_bIsColParticle)
	{
		m_fParticleTime += frameTime;

		if (m_fParticleTime > 1000.f)
		{
			m_fParticleTime = 0.0f;
			m_bIsColParticle = false;
		}
	}
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	m_Input->GetMouseDeltaPosition(deltaX, deltaY);
	m_Camera->Yaw(deltaX * frameTime * 0.00018f);
	m_Camera->Pitch(deltaY * frameTime * 0.00018f);

	if (m_Input->GetKey(KeyCode::Q)) m_Camera->MoveUpDown(dir * frameTime);
	if (m_Input->GetKey(KeyCode::E)) m_Camera->MoveUpDown(-dir * frameTime);
	if (m_Input->GetKey(KeyCode::W)) m_Camera->MoveForward(dir * frameTime);
	if (m_Input->GetKey(KeyCode::A)) m_Camera->Strafe(-dir * frameTime);
	if (m_Input->GetKey(KeyCode::S)) m_Camera->MoveForward(-dir * frameTime);
	if (m_Input->GetKey(KeyCode::D)) m_Camera->Strafe(dir * frameTime);
	if (m_Input->GetKey(KeyCode::ENTER)) m_bIsGameStart = true;

	if (m_Input->GetKey(KeyCode::SPACE)) { m_Camera->SetSpeed(cameraSpeed * 1.7f); }
	else { m_Camera->SetSpeed(cameraSpeed); }

	if (!m_bIsClear)
	{
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

		result = m_Text->SetNumOfObjects(m_numOfObject, m_D3D->GetDeviceContext());
		if (!result)
		{
			return false;
		}

		result = m_Text->SetScreen(m_screenWidth, m_screenHeight, m_D3D->GetDeviceContext());
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

		result = m_Text->SetSpeed(m_Camera->GetSpeed() * 10.f, m_D3D->GetDeviceContext());
		if (!result)
		{
			return false;
		}

		float fHeight = m_Camera->GetPosition().y;

		result = m_Text->SetHeight(fHeight + 1000.0f, m_D3D->GetDeviceContext());
		if (!result)
		{
			return false;
		}
	}
	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	//particleSystem========================
	result = m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext(),0);

	if (!result)
	{
		return false;
	}

	result = m_CollisionParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext(), 1);

	if (!result)
	{
		return false;
	}



	return true;
}

bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix , orthoMatrix , objRotateMatrix[5], skyBoxScalMatrix;
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

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	for (int i = 0; i < m_Models.size(); ++i)
	{
		// Set the radius of the sphere to 1.0 since this is already known.
		const float radius = 1.0f;
		// Check if the sphere model is in the view frustum.
		bool renderModel = true;
		// If it can be seen then render it, if not skip this model and check the next sphere.
		if (renderModel)
		{
			D3DXMATRIX objMat, rotMatX, rotMatY, rotMatZ,transMat;
			
			static float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f ,transZ =0.0f;
			objMat = m_objMatrices[i];

			rotX += 0.0006f;
			rotY += 0.0006f;
			rotZ += 0.0006f;
			transZ += 0.02f;

			D3DXMatrixIdentity(&rotMatX);
			D3DXMatrixIdentity(&rotMatY);
			D3DXMatrixIdentity(&rotMatZ);
			D3DXMatrixIdentity(&transMat);

			D3DXMatrixRotationX(&rotMatX, rotX);
			D3DXMatrixRotationY(&rotMatY, rotY);
			D3DXMatrixRotationZ(&rotMatZ, rotZ);

			D3DXMatrixTranslation(&transMat, 0.0f, 0.0f, -transZ);

			if (i == 0) {
				objMat._41 = m_Camera->GetPosition().x;
				objMat._42 = m_Camera->GetPosition().y;
				objMat._43 = m_Camera->GetPosition().z;
			}

			if (i>0 && i<7) // (1~6) ������ �༺��
			{
				D3DXMatrixMultiply(&objMat, &rotMatY, &objMat);
			}

			//25~29������ �̵��ϴ� ��ֹ� 
			if (i>9)  
			{
		
				if(i < 14) {
					D3DXMatrixMultiply(&objMat, &rotMatX, &objMat);
					D3DXMatrixMultiply(&objMat, &rotMatY, &objMat);
				}
				else if (i < 17) {
					D3DXMatrixMultiply(&objMat, &rotMatZ, &objMat);
					D3DXMatrixMultiply(&objMat, &rotMatY, &objMat);
				}
				else if (i < 21) {
					D3DXMatrixMultiply(&objMat, &rotMatZ, &objMat);
					D3DXMatrixMultiply(&objMat, &rotMatX, &objMat);
				}
				else if (i < 23) {
					D3DXMatrixMultiply(&objMat, &rotMatY, &objMat);
				}
				else if (i < 26) {
					D3DXMatrixMultiply(&objMat, &rotMatX, &objMat);
				}
				else if (i > 25 && i < 30) {
					D3DXMatrixMultiply(&objMat, &transMat, &objMat);
					D3DXMatrixMultiply(&objMat, &rotMatX, &objMat);
					D3DXMatrixMultiply(&objMat, &rotMatY, &objMat);
				}
			}

			// �浹  =============================================================�浹 üũ================
			if (i > 9) // 9 ���ĺ��� ���༺�� 20��
			{
				if (m_Col->ColliderCheck(objMat, m_Camera->GetPosition(), m_radius[i],m_Models[i]))
				{
					if (m_iHp > 0)
					{
						result = m_EffectSound->PlayWaveFile(-500, false);
						
						if (!result) {
							return false;
						}

						m_iHp--;

						m_bIsColParticle = true;
					}
				}

			}

			if (i == 2)
			{
				if (m_Col->ColliderCheck(objMat, m_Camera->GetPosition(), m_radius[i], m_Models[i]))
				{
					if (m_iHp > 0)
					{
						m_bIsClear = true;
						m_iHp = 4;
					}
				}
			}


			m_Models[i]->Render(m_D3D->GetDeviceContext());
			//Render the model using the light shader.
			//result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
			//	objMat, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix,
			//	m_Models[i]->GetTexture(), m_RenderTexture->GetShaderResourceView(),
			//	m_Light->GetPosition(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());

			//result = m_ShaderManager->RenderPointLightShader(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
			//	worldMatrix, viewMatrix, projectionMatrix, m_Models[i]->GetTexture(), diffuseColor, lightPosition);
			//if (!result) { return false; }

			//����� ��ī�� �ڽ� �κ� (�� ������Ʈ�� �ؽ�Ʈ ���̴��� �����մϴ�.)
			if (i == 0 || i ==4)
			{
				result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
					objMat, viewMatrix, projectionMatrix,
					m_Models[i]->GetTexture());
				if (!result) return false;
			}
			else
			{
				result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
					objMat, viewMatrix, projectionMatrix,
					m_Models[i]->GetTexture(), m_Light->GetDirection(),
					m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
					m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
				if (!result) return false;
			}
	
		}
	}

	D3DXMATRIX SpaceShipMatrix;
	D3DXMATRIX mat, ShipView;


	D3DXMatrixScaling(&mat, 0.03f, 0.03f, 0.03f);
	D3DXMatrixRotationYawPitchRoll(&ShipView, m_Camera->GetYaw(), -m_Camera->GetPitch(), 0);
	cameraPosition = m_Camera->GetPosition();
	D3DXMatrixTranslation(&SpaceShipMatrix, cameraPosition.x  , cameraPosition.y - 0.2f, cameraPosition.z + 0.2f );
	SpaceShipMatrix = mat * ShipView * SpaceShipMatrix;


	//Render the player Ship
	  m_spaceship->Render(m_D3D->GetDeviceContext());
	  result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_spaceship->GetIndexCount(),
		SpaceShipMatrix, viewMatrix, projectionMatrix, m_spaceship->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) return false;

	//ParticleSystem===============

	//D3DXMatrixTranslation(&trans, 0.0f, 50.0f, 500.0f);



	//m_D3D->TurnOnAlphaBlending();

	//m_ParticleSystem->Render(m_D3D->GetDeviceContext());

	//if (!m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(),
	//	worldMatrix, viewMatrix, projectionMatrix, m_ParticleSystem->GetTexture())) {
	//
	//	return false;
	//}

	//m_D3D->TurnOffAlphaBlending();


	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->DisableZBuffer();

	m_D3D->TurnOnAlphaBlending();
	

	if (m_bIsGameStart)
	{
		result = m_UI[m_iHp]->Render(m_D3D->GetDeviceContext(), 0, 0);
		if (!result)
		{
			return false;
		}

		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_UI[m_iHp]->GetIndexCount(),
			worldMatrix, m_baseViewMatrix, orthoMatrix, m_UI[m_iHp]->GetTexture());
		if (!result)
		{
			return false;
		}
	}
	else
	{
		result = m_UI[5]->Render(m_D3D->GetDeviceContext(), 0, 0);
		if (!result)
		{
			return false;
		}

		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_UI[5]->GetIndexCount(),
			worldMatrix, m_baseViewMatrix, orthoMatrix, m_UI[5]->GetTexture());
		if (!result)
		{
			return false;
		}
	}


	if (!m_bIsClear && m_bIsGameStart)
	{
		result = m_Text->Render(m_D3D->GetDeviceContext(), m_TextMatrix, orthoMatrix);
		if (!result)
		{
			return false;
		}


	}

	D3DXMATRIX ParticleScale, trans;

	D3DXMatrixIdentity(&ParticleScale);
	D3DXMatrixScaling(&ParticleScale, 1000.f, 1000.f, 1000.f);

	D3DXMatrixMultiply(&worldMatrix, &ParticleScale, &worldMatrix);

	if (m_bIsClear) {
		m_ParticleSystem->Render(m_D3D->GetDeviceContext());

		if (!m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(),
			worldMatrix, m_baseViewMatrix, orthoMatrix, m_ParticleSystem->GetTexture())) {

			return false;
		}
	}

	D3DXMatrixTranslation(&trans, 0.0f, 0.0f, 3.0f);
	D3DXMatrixMultiply(&worldMatrix, &trans, &worldMatrix);

	if (m_bIsColParticle)
	{
		m_CollisionParticleSystem->Render(m_D3D->GetDeviceContext());

		if (!m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_CollisionParticleSystem->GetIndexCount(),
			worldMatrix, m_baseViewMatrix, orthoMatrix, m_CollisionParticleSystem->GetTexture())) {

			return false;
		}
	}

	m_D3D->TurnOffAlphaBlending();

	m_D3D->EnableZBuffer();

	m_D3D->EndScene();

	return true;
}
