#include "Engine.h"
#include <d3dcompiler.h>

#include "Vertex.h"

#include "BasicShader.h"

Engine::Engine(HINSTANCE hInstance, int width, int height, std::wstring title)
    : D3DApp(hInstance, width, height, title)
{

}

Engine::~Engine()
{
}

bool Engine::Initialize()
{
    // â �����.
    // ��ġ ����.
    if (D3DApp::Initialize() == false)
    {
        return false;
    }

    // ��� �ʱ�ȭ.
    if (InitializeScene() == false)
    {
        return false;
    }

    return true;
}

// 1. �޽��� ó�� ����.
// 2. ���� ����.
int Engine::Run()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Update();
            DrawScene();
        }
    }

    return 0;
}

void Engine::Update()
{
    //modelUV.UpdateBuffers(deviceContext.Get());
}

void Engine::DrawScene()
{
    // ���� ����.
    float backgroundColor[4] = { 0.1f, 0.5f, 0.1f, 1.0f };
    
    // ����� (Clear) - �����δ� ������� ��ĥ�ϱ�.
    // Begin Draw(Render) - DX9.
    deviceContext.Get()->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

    // �׸��� �غ�.
    //BasicShader::Bind(deviceContext.Get());


    // ������ �ٲٱ�. FrontBuffer <-> BackBuffer.
    swapChain->Present(1, 0);
}

bool Engine::InitializeScene()
{
    if (BasicShader::Compile(device.Get()) == false)
    {
        return false;
    }
    if (BasicShader::Create(device.Get()) == false)
    {
        return false;
    }

    // �޽� �ʱ�ȭ

    //// shader parameter�κ� textureshader ���� �ʰ� BasicShader�� ��ü
    //if (modelUV.InitializeBuffers(device.Get(), BasicShader::ShaderBuffer(), "sphere.fbx") == false)
    //{
    //    return false;
    //}
    //modelUV.SetScale(0.002f, 0.002f, 0.002f);
    ////modelUV.SetScale(0.2f, 0.2f, 0.2f);
    //modelUV.SetRotation(45.0f, 45.0f, 0.0f);

    return true;
}
