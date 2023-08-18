#pragma once
#include "D3DApp.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Quad.h"
#include "QuadUV.h"

#include "Matrix4f.h"
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class Engine : public D3DApp
{
public:
	Engine(HINSTANCE hInstance, int width, int height, std::wstring title);
	~Engine();

	bool Initialize() override; // Ÿ�̸�, �� � ���� �ʱ�ȭ
	int Run() override;

protected:
	void Update() override;
	void DrawScene() override;
	
private:
	// ��� �ʱ�ȭ.
	bool InitializeScene();

	Quad quad;
	Triangle triangle;
	QuadUV quadUV;
};

