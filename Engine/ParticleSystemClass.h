#pragma once


class TextureClass;

class ParticleSystemClass
{
private:
	struct ParticleType
	{
		float positionX, positionY, positionZ;
		float red, green, blue;
		float velocity;
		bool active;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR4 color;
	};

public:
	ParticleSystemClass();
	ParticleSystemClass(const ParticleSystemClass&);
	~ParticleSystemClass();

	bool Initialize(ID3D11Device*,  WCHAR*);
	void Shutdown();
	bool Frame(float, ID3D11DeviceContext*,int);
	void Render(ID3D11DeviceContext*);

	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();

private:
	bool LoadTexture(ID3D11Device*,  WCHAR*);
	void ReleaseTexture();

	bool InitializeParticleSystem();
	void ShutdownParticleSystem();

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

	void EmitParticles(float,int);
	void UpdateParticles(float,int);
	void KillParticles();

	bool UpdateBuffers(ID3D11DeviceContext*);
	void RenderBuffers(ID3D11DeviceContext*);

private:
	float m_particleDeviationX = 0;
	float m_particleDeviationY = 0;
	float m_particleDeviationZ = 0;
	float m_particleVelocity = 0;
	float m_particleVelocityVariation = 0;
	float m_particleSize = 0;
	float m_particlesPerSecond = 0;
	int m_maxParticles = 0;

	int m_currentParticleCount = 0;
	float m_accumulatedTime = 0;

	TextureClass* m_Texture = nullptr;
	ParticleType* m_particleList = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
	VertexType* m_vertices = nullptr;
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
};