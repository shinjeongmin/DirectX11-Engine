#pragma once

#include "Window.h"
#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance, int width, int height, std::wstring title);

	virtual ~D3DApp();

	virtual bool Initialize();

	// �������̽�
	virtual int Run() = 0; // ���� ���� �Լ�.

protected:
	virtual void Update() = 0;
	virtual void DrawScene() = 0;

	bool InitializeDirect3D();

	// ����Ʈ ������ ���
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11RenderTargetView> renderTargetView;	// ����Ÿ��.

	D3D11_VIEWPORT viewport;					// ����Ʈ (ȭ��)
};

