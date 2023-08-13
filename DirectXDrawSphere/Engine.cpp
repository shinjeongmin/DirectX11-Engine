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
    //modelUV.UpdateBuffers(deviceContext.Get());
}

void Engine::DrawScene()
{
    // 색상 고르기.
    float backgroundColor[4] = { 0.1f, 0.5f, 0.1f, 1.0f };
    
    // 지우기 (Clear) - 실제로는 덮어씌워서 색칠하기.
    // Begin Draw(Render) - DX9.
    deviceContext.Get()->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

    // 그리기 준비.
    //BasicShader::Bind(deviceContext.Get());


    // 프레임 바꾸기. FrontBuffer <-> BackBuffer.
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

    // 메쉬 초기화

    //// shader parameter부분 textureshader 넣지 않고 BasicShader로 대체
    //if (modelUV.InitializeBuffers(device.Get(), BasicShader::ShaderBuffer(), "sphere.fbx") == false)
    //{
    //    return false;
    //}
    //modelUV.SetScale(0.002f, 0.002f, 0.002f);
    ////modelUV.SetScale(0.2f, 0.2f, 0.2f);
    //modelUV.SetRotation(45.0f, 45.0f, 0.0f);

    return true;
}
