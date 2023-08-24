#include "Engine.h"
#include <d3dcompiler.h>

#include "Vertex.h"

#include "BasicShader.h"
#include "TextureMappingShader.h"

#include "InputProcessor.h"

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
            // ESC ����.
            if (InputProcessor::IsKeyDown(Keyboard::Keys::Escape) == true)
            {
                if (MessageBox(nullptr, L"�����Ͻðڽ��ϱ�?", L"����", MB_YESNO) == IDYES)
                {
                    DestroyWindow(Window::WindowHandle());
                    return 0;
                }
            }

            Update();
            DrawScene();
        }
    }

    return 0;
}

void Engine::Update()
{

    // ����Ʈ������ ���� �ʿ�
    quad.UpdateBuffers(deviceContext.Get());
    triangle.UpdateBuffers(deviceContext.Get());
    quadUV.UpdateBuffers(deviceContext.Get());
    modelUV.UpdateBuffers(deviceContext.Get());

}

void Engine::DrawScene()
{
    // ���� ����.
    float backgroundColor[4] = { 0.1f, 0.5f, 0.1f, 1.0f };
    
    // ����� (Clear) - �����δ� ������� ��ĥ�ϱ�.
    // Begin Draw(Render) - DX9.
    deviceContext->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

    // �׸��� �غ�
    BasicShader::Bind(deviceContext.Get());
    // �׸���
    quad.RenderBuffers(deviceContext.Get());
    triangle.RenderBuffers(deviceContext.Get());

    // �׸��� �غ�. (���̴� �ٲٱ�.)
    textureShader.Bind(deviceContext.Get());
    // �׸���.
    quadUV.RenderBuffers(deviceContext.Get());
    modelUV.RenderBuffers(deviceContext.Get());

    // ������ �ٲٱ�. FrontBuffer <-> BackBuffer.
    swapChain->Present(1, 0);
}

bool Engine::InitializeScene()
{
    // Compile
    if (BasicShader::Compile(device.Get()) == false) {
        return false;
    }
    // Create
    if (BasicShader::Create(device.Get()) == false) {
        return false;
    }

    if (textureShader.Initialize(device.Get(), L"dog.jpg") == false)
    {
        return false;
    }

    // �簢�� �ʱ�ȭ
    if (quad.InitializeBuffers(device.Get(), BasicShader::ShaderBuffer()) == false)
    {
        return false;
    }
    quad.SetPosition(-0.7f, 0.0f, 0.0f);
    quad.SetScale(0.4f, 0.4f, 0.4f);

    // �ﰢ�� �ʱ�ȭ
    if (triangle.InitializeBuffers(device.Get(), BasicShader::ShaderBuffer()) == false)
    {
        return false;
    }
    triangle.SetPosition(-0.7f, 0.6f, 0.0f);
    triangle.SetScale(0.4f, 0.4f, 0.4f);

    if (quadUV.InitializeBuffers(device.Get(), textureShader.ShaderBuffer()) == false)
    {
        return false;
    }
    quadUV.SetPosition(-0.7f, -0.6f, 0.0f);
    quadUV.SetScale(0.4f, 0.4f, 0.4f);

    if (modelUV.InitializeBuffers(device.Get(), textureShader.ShaderBuffer(), "cube.fbx") == false)
    {
        return false;
    }
    modelUV.SetScale(0.2f, 0.2f, 0.2f);
    modelUV.SetRotation(45.0f, 45.0f, 0.0f);

    return true;
}
