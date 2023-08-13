#include "Engine.h"
#include <d3dcompiler.h>

#include "Vertex.h"

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
    modelUV.UpdateBuffers(deviceContext.Get());
}

void Engine::DrawScene()
{
    // ���� ����.
    float backgroundColor[4] = { 0.1f, 0.5f, 0.1f, 1.0f };
    
    // ����� (Clear) - �����δ� ������� ��ĥ�ϱ�.
    // Begin Draw(Render) - DX9.
    deviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);

    // �׸���
    vertexShader.Bind(deviceContext);
    pixelShader.Bind(deviceContext);

    mesh.RenderBuffers(deviceContext);

    // ������ �ٲٱ�. FrontBuffer <-> BackBuffer.
    swapChain->Present(1, 0);
}

bool Engine::InitializeScene()
{
    vertexShader = VertexShader(L".//shader//BasicVS.hlsl", "main", "vs_5_0");
    pixelShader = PixelShader(L".//shader//BasicPS.hlsl", "main", "ps_5_0");

    // ������
    if (vertexShader.Compile(device) == false)
    {
        return false;
    }
    if (pixelShader.Compile(device) == false)
    {
        return false;
    }
    // ����
    if (vertexShader.Create(device) == false)
    {
        return false;
    }
    if (pixelShader.Create(device) == false)
    {
        return false;
    }

    // �޽� �ʱ�ȭ
    if (mesh.InitializeBuffers(device, vertexShader.ShaderBuffer()) == false)
    {
        return false;
    }

    return true;
}
