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

    // ������ ����.
    vertexCount = vertices.size();

    // ���� ���� �����.
    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
    vertexBufferDesc.ByteWidth = sizeof(VertexUV) * vertexCount; // �󸶸�ŭ ������.
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ���� ������ ���۷� �� ���̴�.
    vertexBufferDesc.CPUAccessFlags = 0; // ������ �ø��� ���� CPU�� GPU ������ �� �ְ� �ұ�? �츮�� ���� ���ؼ� �ڵ��� �� ������ �����ϰ� ���� ��. 0�� �� �����ϰ�.
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // ������ ���.
    D3D11_SUBRESOURCE_DATA vertexBufferData;
    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    //vertexBufferData.pSysMem = &vertices;  // ����.
    vertexBufferData.pSysMem = vertices.data();

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

    // �ε��� ����
    indexCount = indices.size();

    D3D11_BUFFER_DESC indexBufferDesc;
    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
    indexBufferDesc.ByteWidth = sizeof(unsigned int) * indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // ������ ���.
    D3D11_SUBRESOURCE_DATA indexBufferData;
    ZeroMemory(&indexBufferData, sizeof(indexBufferData));
    indexBufferData.pSysMem = indices.data();

    // �ε��� ���� ����.
    result = device->CreateBuffer(
        &indexBufferDesc,
        &indexBufferData,
        indexBuffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"�ε��� ���� ���� ����", L"����", 0);
        return false;
    }

    // ������ ���� �� ����� (�Է� ���̾ƿ�).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0} // �տ� position�� float 4���� 12����Ʈ�ϱ� 12.
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

void ModelUV::BindBuffers(ID3D11DeviceContext* deviceContext)
{
    // Bind
    unsigned int stride = sizeof(VertexUV); // �ѹ��� �� ���� ���� ��.
    unsigned int offset = 0;

    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    deviceContext->IASetInputLayout(inputLayout.Get());
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // ���� �׸� ���� LineList.

    transform.Bind(deviceContext);
}