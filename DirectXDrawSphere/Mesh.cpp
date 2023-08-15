#include "Mesh.h"

Mesh::Mesh()
    : vertexCount(0), vertexBuffer(0), inputLayout(0),
    transform(), // transform(TransformBuffer())�� ����.
    position(Vector3f::Zero),
    rotation(Vector3f::Zero),
    scale(Vector3f::One)
{
}

Mesh::~Mesh()
{
}

bool Mesh::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
    // ���� ������ �����.
    // ����(Vertex) �迭.
    // �޼� ��ǥ��.
    Vertex vertices[] =
    {
        Vertex(0.0f, 0.5f, 0.5f),
        Vertex(0.5f, -0.5f, 0.5f),
        Vertex(-0.5f, -0.5f, 0.5f)
    };

    // ������ ����.
    vertexCount = ARRAYSIZE(vertices);

    // ���� ���� �����.
    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
    vertexBufferDesc.ByteWidth = sizeof(vertices); // �󸶸�ŭ ������.
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ���� ������ ���۷� �� ���̴�.
    vertexBufferDesc.CPUAccessFlags = 0; // ������ �ø��� ���� CPU�� GPU ������ �� �ְ� �ұ�? �츮�� ���� ���ؼ� �ڵ��� �� ������ �����ϰ� ���� ��. 0�� �� �����ϰ�.
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // ������ ���.
    D3D11_SUBRESOURCE_DATA vertexBufferData;
    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    vertexBufferData.pSysMem = vertices;

    // ���� ���� ����.
    HRESULT result = device->CreateBuffer(
        &vertexBufferDesc,
        &vertexBufferData,
        vertexBuffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"���� ���� ���� ����", L"����", 0);
        return false;
    }

    // ������ ���� �� ����� (�Է� ���̾ƿ�).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    // �Է� ���̾ƿ� ����.
    result = device->CreateInputLayout(
        layout,
        ARRAYSIZE(layout),
        vertexShaderBuffer->GetBufferPointer(),
        vertexShaderBuffer->GetBufferSize(),
        inputLayout.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"�Է� ���̾ƿ� ���� ����", L"����", 0);
        return false;
    }

    // ��� ����.
    if (transform.Create(device) == false)
    {
        return false;
    }

    return true;
}

void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
    BindBuffers(deviceContext);
    DrawBuffers(deviceContext);
}

void Mesh::BindBuffers(ID3D11DeviceContext* deviceContext)
{
    // Bind
    unsigned int stride = sizeof(Vertex); // �ѹ��� �� ���� ���� ��.
    unsigned int offset = 0;

    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    deviceContext->IASetInputLayout(inputLayout.Get());
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // ���� �׸� ���� LineList.

    transform.Bind(deviceContext);
}

void Mesh::DrawBuffers(ID3D11DeviceContext* deviceContext)
{
    // Draw
    deviceContext->Draw(vertexCount, 0); // �̰� DrawCall�̴�.
}

void Mesh::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
    transform.transformMatrix = Matrix4f::Scale(scale) * Matrix4f::Rotation(rotation) * Matrix4f::Translation(position);
}

void Mesh::SetPosition(float x, float y, float z)
{
    position = Vector3f(x, y, z);
}

void Mesh::SetPosition(Vector3f position)
{
    this->position = position;
}

void Mesh::SetRotation(float x, float y, float z)
{
    rotation = Vector3f(x, y, z);
}

void Mesh::SetRotation(Vector3f rotation)
{
    this->rotation = rotation;
}

void Mesh::SetScale(float x, float y, float z)
{
    scale = Vector3f(x, y, z);
}

void Mesh::SetScale(Vector3f scale)
{
    this->scale = scale;
}