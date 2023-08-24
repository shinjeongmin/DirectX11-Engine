#include "D3DApp.h"

D3DApp::D3DApp(HINSTANCE hInstance, int width, int height, std::wstring title)
{
    // Window Ŭ������ �� ����.
    Window::SetInstance(hInstance);
    Window::SetWidth(width);
    Window::SetHeight(height);
    Window::SetTitle(title);
}

D3DApp::~D3DApp()
{

}

bool D3DApp::Initialize()
{
    if (Window::InitializeWindow() == false)
    {
        return false;
    }
    if (InitializeDirect3D() == false)
    {
        return false;
    }
    return true;
}

bool D3DApp::InitializeDirect3D()
{
    // ��ġ ����.
    // Device - ����.
    // DeviceContext - ��, ��ġ ����.
    // SwapChain - ǥ��.

    // ���� ü�� ���� ����. �������� �ʹ� ���Ƽ� ����ü�� ����������.
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 1;                          // ����� 1��. Double Buffering. Screen Tearing. ����Ʈ����, ���۹� ���ļ� �� 2�� ���ٴ� ��.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // ��� ����. ȭ�� ��¿����� ���ٴ� ��.
    swapChainDesc.OutputWindow = Window::WindowHandle();    // ����� ������ ����.
    swapChainDesc.Windowed = true;                          // â ��� ����.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;    // ����Ʈ���ۿ� ����۸� �ٲ� ��, ȿ�� �� ���ٴ� ��. (���� ���� �� ��).

    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // Ÿ��. RGBA�� 8��Ʈ�� ���. (0~255 ��.) UNORM�� ����ȭ. (0~255 ���� 0~1�� �ٲ�.)
    swapChainDesc.BufferDesc.Width = Window::Width();               // �ʺ�.
    swapChainDesc.BufferDesc.Height = Window::Height();             // ����.

    swapChainDesc.SampleDesc.Count = 1;             // ��Ƽ ���ø� ���� 1��. (�� ���ٴ� ��.) Anti-Alasing.
    swapChainDesc.SampleDesc.Quality = 0;           // Count - 1.

    // ��ġ ����.
    HRESULT result = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE, // �׷��� ���ӱ�. ���� �̰Ÿ� ��. ���� �� ȣȯ�Ѵٰ� ���� ����.
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        swapChain.GetAddressOf(),
        device.GetAddressOf(),
        NULL,
        deviceContext.GetAddressOf()
    );

    // ���� �˻�.
    if (FAILED(result))
    {
        MessageBox(nullptr, L"��ġ ���� ����", L"����", 0);
        return false;
    }

    // ����� ����?���ٴ� ���� �޾ƿ���. 
    // �츮�� ����ۿ� �ٷ� �� �׸�. View�� ���� ���������� ������.
    // ����� ������ �����ؼ� �ִϱ� ����.
    ID3D11Texture2D* backbufferTexture;
    result = swapChain->GetBuffer(
        NULL,
        __uuidof(ID3D11Texture2D), // Ÿ�� ���� ���. uuidof : ���⿡ ���۹� ���� �޶�.
        (void**)(&backbufferTexture) // Ÿ�Կ� ������� �ּҰ��� �ް� ���� �� void ������.
    );

    // ���� �˻�.
    if (FAILED(result))
    {
        MessageBox(nullptr, L"����� ���� �����µ� ����", L"����", 0);
        return false;
    }

    // ���� Ÿ�� ��(View)
    // ����ۿ� ���� �������� ���ϱ� ������ �並 ���� ���� ����.
    result = device->CreateRenderTargetView(
        backbufferTexture, // ���⿡ ���� �ְ�,
        nullptr,
        renderTargetView.GetAddressOf() // �ű⿡ ���缭 �����ش޶�.
    );

    // ���� �˻�.
    if (FAILED(result))
    {
        MessageBox(nullptr, L"���� Ÿ�� �� ���� ����", L"����", 0);
        return false;
    }

    // �ӽ� ����(���ҽ�) ����.
    backbufferTexture->Release(); // delete Ű����� �ϴ� ���� ������, Release�� �ؾ� �����ϰ� ���� ����.

    // ���� ���ٽ� �� (DepthStencilView)
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    memset(&depthStencilDesc, 0, sizeof(depthStencilDesc));
    depthStencilDesc.Width = Window::Width();
    depthStencilDesc.Height = Window::Height();
    depthStencilDesc.MipLevels = 1; // �Ӹ�. ���� �ϳ��� ���ٴ� ��.
    depthStencilDesc.ArraySize = 1; // �ٸ� ���ҽ� ���� �ʰ�, �̰͸� ���ٴ� ��.
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // D�� Depth(UNORM unsigned normalized), S�� Stencil. 24+8 �� 32bit

    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;

    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; // ��� ����. �� ������Ʈ������ ��� Default �� ��� ��.
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // ���� ���ٽǷ� �� ���̴�.
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    // ���� ���ٽ� ���� ����.
    ComPtr<ID3D11Texture2D> depthStecilBuffer;
    result = device.Get()->CreateTexture2D(
        &depthStencilDesc,
        NULL,
        depthStecilBuffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"���� ���ٽ� ���� ���� ����", L"����", 0);
        return false;
    }
    // ���� ���ٽ� ���۴� ���� ä������?

    // ���� ���ٽ� �� ����.
    result = device.Get()->CreateDepthStencilView(
        depthStecilBuffer.Get(),
        NULL,
        depthStencilView.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"���� ���ٽ� �� ���� ����", L"����", 0);
        return false;
    }

    // ���� Ÿ�� �� �Ҵ�.(����)
    // ���۵� ������ | ������ ������.
    deviceContext->OMSetRenderTargets( // OM : Output Merger �����شٴ� �ǹ�. ��� ���� ���� ��ȯ �� ��.
        1, // ȭ���� 4���� �����ٸ�, 4�� �Էµ�.
        renderTargetView.GetAddressOf(),
        depthStencilView.Get()
    );

    // ����Ʈ(ȭ��) - ũ�� ����.
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = (float)Window::Width();
    viewport.Height = (float)Window::Height();

    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    // ����Ʈ �Ҵ�.
    deviceContext->RSSetViewports(1, &viewport); // RS : �����Ͷ�����

    return true;
}
