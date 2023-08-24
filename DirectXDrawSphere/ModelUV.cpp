#include "ModelUV.h"
#include "VertexUV.h"

#include <vector>
#include "ResourceLoader.h"

ModelUV::ModelUV()
{
}

ModelUV::~ModelUV()
{
}

bool ModelUV::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
    return true;
}

bool ModelUV::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, std::string modelFileName)
{
    std::vector<VertexUV> vertices;
    std::vector<unsigned int> indices;

    // ���ҽ� �ε�.
    ResourceLoader::LoadModel(modelFileName, &vertices, &indices);


    // ���ؽ� ���� ����.
    if (vertexBuffer.Initialize(device, vertices.data(), vertices.size(), sizeof(VertexUV)) == false)
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
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0} // �տ� position�� float 4���� 12����Ʈ�ϱ� 12.
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