#include "SpecularShader.h"

bool SpecularShader::Initialize(ID3D11Device* device, std::wstring textureFileName)
{
	vertexShader = VertexShader(L".//shader//SpecularVS.hlsl", "main", "vs_5_0");
	pixelShader = PixelShader(L".//shader//SpecularPS.hlsl", "main", "ps_5_0");

	if (Compile(device, textureFileName) == false)
	{
		return false;
	}
	if (Create(device) == false)
	{
		return false;
	}

	return true;
}

bool SpecularShader::Compile(ID3D11Device* device, std::wstring textureFileName)
{
	if (vertexShader.Compile(device) == false)
	{
		return false;
	}
	if (pixelShader.Compile(device) == false)
	{
		return false;
	}

	// �ؽ��� �ε�.
	if (pixelShader.LoadTexture(device, textureFileName) == false)
	{
		return false;
	}

	return true;
}

bool SpecularShader::Create(ID3D11Device* device)
{
	if (vertexShader.Create(device) == false)
	{
		return false;
	}
	if (pixelShader.Create(device) == false)
	{
		return false;
	}

	// ���÷� ������Ʈ ����.
	if (pixelShader.CreateSamplerState(device) == false)
	{
		return false;
	}

	return true;
}

void SpecularShader::Bind(ID3D11DeviceContext* deviceContext)
{
	vertexShader.Bind(deviceContext);
	pixelShader.Bind(deviceContext);
	pixelShader.BindTextures(deviceContext);
	pixelShader.BindSamplerState(deviceContext);
}

ID3DBlob* SpecularShader::ShaderBuffer()
{
	return vertexShader.ShaderBuffer();
}