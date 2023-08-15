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
     // ��� ������Ʈ.
    static float xPos = 0.0f;
    static float direction = 1.0f;
    xPos = xPos + (0.01f * direction);

    if (xPos > 1.0f)
    {
        direction = -1.0f;
    }
    if (xPos < -1.0f)
    {
        direction = 1.0f;
    }

    // ������.
    static float scale = 0.5f;
    static float scaleDirection = 1.0f;
    scale = scale + (0.01f * scaleDirection);

    if (scale > 1.5f)
    {
        scaleDirection = -1.0f;
    }
    if (scale < 0.5f)
    {
        scaleDirection = 1.0f;
    }

    // ȸ��.
    static float zRot = 0.0f;
    static float rotationDirection = 1.0f;
    zRot = zRot + (1.0f * rotationDirection);

    if (zRot >= 360.0f)
    {
        zRot = 0.0f;
    }

    mesh.SetPosition(xPos, 0.0f, 0.0f);
    mesh.SetRotation(0.0f, 0.0f, zRot);
    mesh.SetScale(scale, scale, 1.0f);

    // ����Ʈ������ ���� �ʿ�
    //mesh.UpdateBuffers(deviceContext.Get());
}

void Engine::DrawScene()
{
    // ���� ����.
    float backgroundColor[4] = { 0.1f, 0.5f, 0.1f, 1.0f };
    
    // ����� (Clear) - �����δ� ������� ��ĥ�ϱ�.
    // Begin Draw(Render) - DX9.
    deviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);

    // �׸���
    BasicShader::Bind(deviceContext);

    mesh.RenderBuffers(deviceContext);

    // ������ �ٲٱ�. FrontBuffer <-> BackBuffer.
    swapChain->Present(1, 0);
}

bool Engine::InitializeScene()
{
    // Compile
    if (BasicShader::Compile(device) == false) {
        return false;
    }
    // Create
    if (BasicShader::Create(device) == false) {
        return false;
    }

    // �޽� �ʱ�ȭ
    if (mesh.InitializeBuffers(device, BasicShader::ShaderBuffer()) == false)
    {
        return false;
    }

    return true;
}
