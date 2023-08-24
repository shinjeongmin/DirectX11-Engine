#include "Engine.h"
#include <d3dcompiler.h>

#include "Vertex.h"

#include "InputProcessor.h"

#include "MathUtil.h"

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
    // ī�޶� �̵� ó��.
    static float moveSpeed = 2.0f;
    if (InputProcessor::IsKeyDown(Keyboard::Keys::W) == true)
    {
        camera.MoveForward(moveSpeed);
    }
    if (InputProcessor::IsKeyDown(Keyboard::Keys::S) == true)
    {
        camera.MoveForward(-moveSpeed);
    }
    if (InputProcessor::IsKeyDown(Keyboard::Keys::A) == true)
    {
        camera.MoveRight(-moveSpeed);
    }
    if (InputProcessor::IsKeyDown(Keyboard::Keys::D) == true)
    {
        camera.MoveRight(moveSpeed);
    }
    if (InputProcessor::IsKeyDown(Keyboard::Keys::Q) == true)
    {
        camera.MoveUp(moveSpeed);
    }
    if (InputProcessor::IsKeyDown(Keyboard::Keys::E) == true)
    {
        camera.MoveUp(-moveSpeed);
    }

    // ī�޶� ȸ�� ó��.
    Mouse::State state = InputProcessor::MouseState();
    static float rotationSpeed = 0.2f;
    if (state.leftButton == true)
    {
        camera.Yaw((float)state.x * rotationSpeed);
        camera.Pitch((float)state.y * rotationSpeed);
    }

    camera.UpdateCamera();

    modelPTN.UpdateBuffers(deviceContext.Get());

    static float lightXPos = lightBuffer.data.position.x;
    static float direction = 1.0f;
    lightXPos += 10.0f * direction;
    if (lightXPos >= 500.0f)
    {
        direction = -1.0f;
    }
    if (lightXPos <= -500.0f)
    {
        direction = 1.0f;
    }
    lightBuffer.data.position.x = lightXPos;
    lightBuffer.data.position.y = lightXPos;
}

void Engine::DrawScene()
{
    // ���� ����.
    float backgroundColor[4] = { 0.1f, 0.5f, 0.1f, 1.0f };
    
    // ����� (Clear) - �����δ� ������� ��ĥ�ϱ�.
    // Begin Draw(Render) - DX9.
    deviceContext->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

    // ���� �����
    deviceContext.Get()->ClearDepthStencilView(
        depthStencilView.Get(),
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, // ��Ʈ ������ ����.
        1.0f, 0 // ���� ������ 1�� �ʱ�ȭ, ���ٽ��� 0���� �ʱ�ȭ.
    );

    // ī�޶� ���ε�.
    camera.BindBuffer(deviceContext.Get());

    // ����Ʈ ���� ���ε�.  
    lightBuffer.Bind(deviceContext.Get());

    // �׸��� �غ�. (���̴� �ٲٱ�.)
    diffuseShader.Bind(deviceContext.Get());
    modelPTN.RenderBuffers(deviceContext.Get());

    // ������ �ٲٱ�. FrontBuffer <-> BackBuffer.
    swapChain->Present(1, 0);
}

bool Engine::InitializeScene()
{
    // ī�޶� ����.
    camera = Camera(
        70.0f * MathUtil::Deg2Rad,
        (float)Window::Width(),
        (float)Window::Height(),
        0.1f,
        10000.0f
    );
    // ī�޶� ��ġ ����.
    camera.SetPosition(0.0f, 0.0f, -200.0f);

    // ī�޶� ���� ����.
    if (camera.CreateBuffer(device.Get()) == false)
    {
        return false;
    }

    lightBuffer.data.position = Vector3f(500.0f, 500.0f, -500.0f);
    if (lightBuffer.Create(device.Get()) == false) 
    {
        return false;
    }

    if (diffuseShader.Initialize(device.Get(), L"T_CharM_Warrior_D.TGA") == false)
    {
        return false;
    }

    if (modelPTN.InitializeBuffers(device.Get(), diffuseShader.ShaderBuffer(), "SK_CharM_Warrior.fbx") == false)
    {
        return false;
    }
    modelPTN.SetPosition(0.0f, -90.0f, 0.5f);
    modelPTN.SetRotation(-90.0f, 0.0f, 0.0f);
    modelPTN.SetScale(1.0f, 1.0f, 1.0f);

    return true;
}
