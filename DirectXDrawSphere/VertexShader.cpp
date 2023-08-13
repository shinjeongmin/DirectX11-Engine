#include <d3dcompiler.h>

#include "VertexShader.h"

VertexShader::VertexShader()
	: Shader()
{
}

VertexShader::VertexShader(std::wstring filename)
	: Shader(filename)
{
	profile = "vs_5_0";
}

VertexShader::VertexShader(std::wstring filename, std::string entry, std::string profile)
	: Shader(filename, entry, profile), vertexShader(0)
{
}

VertexShader::~VertexShader()
{
}

bool VertexShader::Compile(ID3D11Device* device)
{
    // VS ������
    HRESULT result = D3DCompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        entry.c_str(),
        profile.c_str(),
        NULL,
        NULL,
        &shaderBuffer,
        NULL
    );
    if (FAILED(result)) { MessageBox(nullptr, L"���� ���̴� ������ ����", L"����", 0); }

    return true;
}

bool VertexShader::Create(ID3D11Device* device)
{
    // VS ����.
    HRESULT result = device->CreateVertexShader(
        shaderBuffer->GetBufferPointer(), // ���� ���� �ּ�.
        shaderBuffer->GetBufferSize(), // �󸶸�ŭ ���� ��.
        nullptr,
        &vertexShader
    );
    if (FAILED(result)) { MessageBox(nullptr, L"���� ���̴� ���� ����", L"����", 0); }

    return true;
}

void VertexShader::Bind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->VSSetShader(vertexShader, NULL, NULL);
}