#include "QuadUV.h"
#include "VertexUV.h"

QuadUV::QuadUV()
{
}

QuadUV::~QuadUV()
{
}

bool QuadUV::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
    // ���� ������ �����.
    // ����(Vertex) �迭.
    // �޼� ��ǥ��.
    VertexUV vertices[] =
    {
        VertexUV(Vector3f(-0.5f, -0.5f, 0.5f), Vector2f(0.0f, 1.0f)),
        VertexUV(Vector3f(-0.5f, 0.5f, 0.5f), Vector2f(0.0f, 0.0f)),
        VertexUV(Vector3f(0.5f, 0.5f, 0.5f), Vector2f(1.0f, 0.0f)),

        VertexUV(Vector3f(-0.5f, -0.5f, 0.5f), Vector2f(0.0f, 1.0f)),
        VertexUV(Vector3f(0.5f, 0.5f, 0.5f), Vector2f(1.0f, 0.0f)),
        VertexUV(Vector3f(0.5f, -0.5f, 0.5f), Vector2f(1.0f, 1.0f))
    };

    if (vertexBuffer.Initialize(device, vertices, ARRAYSIZE(vertices), sizeof(VertexUV)) == false)
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
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0} // �տ� position�� float 4���� 12����Ʈ�ϱ� 12.
    };

    // �Է� ���̾ƿ� ����.
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