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
    // 창 만들기.
    // 장치 생성.
    if (D3DApp::Initialize() == false)
    {
        return false;
    }

    // 장면 초기화.
    if (InitializeScene() == false)
    {
        return false;
    }

    return true;
}

// 1. 메시지 처리 루프.
// 2. 엔진 루프.
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

    // 스마트포인터 수정 필요
    quad.UpdateBuffers(deviceContext.Get());
    triangle.UpdateBuffers(deviceContext.Get());

}

void Engine::DrawScene()
{
    // 색상 고르기.
    float backgroundColor[4] = { 0.1f, 0.5f, 0.1f, 1.0f };
    
    // 지우기 (Clear) - 실제로는 덮어씌워서 색칠하기.
    // Begin Draw(Render) - DX9.
    deviceContext->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

    // 그리기 준비
    BasicShader::Bind(deviceContext.Get());
    // 그리기
    quad.RenderBuffers(deviceContext.Get());
    triangle.RenderBuffers(deviceContext.Get());

    // 프레임 바꾸기. FrontBuffer <-> BackBuffer.
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

    // 사각형 초기화
    if (quad.InitializeBuffers(device.Get(), BasicShader::ShaderBuffer()) == false)
    {
        return false;
    }
    quad.SetPosition(-0.5f, 0.0f, 0.0f);
    quad.SetScale(0.5f, 0.5f, 0.5f);

    // 삼각형 초기화
    if (triangle.InitializeBuffers(device.Get(), BasicShader::ShaderBuffer()) == false)
    {
        return false;
    }
    triangle.SetPosition(0.5f, 0.0f, 0.0f);
    triangle.SetScale(0.5f, 0.5f, 0.5f);


    return true;
}
