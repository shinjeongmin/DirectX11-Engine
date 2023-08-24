#include "ModelPTN.h"
#include "VertexPTN.h"

#include <vector>
#include "ResourceLoader.h"

ModelPTN::ModelPTN()
{
}

ModelPTN::~ModelPTN()
{
}

bool ModelPTN::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
    return true;
}

bool ModelPTN::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, std::string modelFileName)
{
    std::vector<VertexPTN> vertices;
    std::vector<unsigned int> indices;

    // ���ҽ� �ε�.
    ResourceLoader::LoadModel(modelFileName, &vertices, &indices);

    // ���ؽ� ���� ����.
    if (vertexBuffer.Initialize(device, vertices.data(), vertices.size(), sizeof(VertexPTN)) == false) // ũ�� �˷���� ��.
    {
        return false;
    }

    // �ε��� ���� ����.
    if (indexBuffer.Initialize(device, indices.data(), indices.size()) == false)
    {
        return false;
    }

    // ������ ���� �� ����� (�Է� ���̾ƿ�).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        // 0, 12, 20 ���� �Ŵ� �ڵ����� ����ϴ� D3D11_APPEND_ALIGNED_ELEMENT Ű���尡 ����.
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, // �տ� position�� float 4���� 12����Ʈ�ϱ� 12.
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}, // position 12����Ʈ + texcoord 8����Ʈ = 20
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