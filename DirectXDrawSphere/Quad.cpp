#include "Quad.h"

Quad::Quad()
{
}

Quad::~Quad()
{
}

bool Quad::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
    // ���� ������ �����.
    // ����(Vertex) �迭.
    // �޼� ��ǥ��.
    Vertex vertices[] =
    {
        Vertex(-0.5f, -0.5f, 0.5f),
        Vertex(-0.5f, 0.5f, 0.5f),
        Vertex(0.5f, 0.5f, 0.5f),
        Vertex(-0.5f, -0.5f, 0.5f),
        Vertex(0.5f, 0.5f, 0.5f),
        Vertex(0.5f, -0.5f, 0.5f)
    };

    if (vertexBuffer.Initialize(device, vertices, ARRAYSIZE(vertices), sizeof(Vertex)) == false)
    {
        return false;
    }

    // �ε��� ����
    unsigned int indices[] =
    {
        0, 1, 2, // �ð� �������θ� �����ָ�
        0, 2, 3
    };

    if (indexBuffer.Initialize(device, indices, ARRAYSIZE(indices)) == false)
    {
        return false;
    }

    // ������ ���� �� ����� (�Է� ���̾ƿ�).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    if (inputLayout.Initialize(device, layout, ARRAYSIZE(layout), vertexShaderBuffer) == false)
    {
        return false;
    }

    // ��� ����.
    if (transform.Create(device) == false)
    {
        return false;
    }

    return true;
}