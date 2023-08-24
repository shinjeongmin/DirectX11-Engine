#include "DiffuseShader.h"

bool DiffuseShader::Initialize(ID3D11Device* device, std::wstring textureFileName)
{
	vertexShader = VertexShader(L".//shader//DiffuseVS.hlsl", "main", "vs_5_0");
	pixelShader = PixelShader(L".//shader//DiffusePS.hlsl", "main", "ps_5_0");

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

bool DiffuseShader::Compile(ID3D11Device* device, std::wstring textureFileName)
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

bool DiffuseShader::Create(ID3D11Device* device)
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

void DiffuseShader::Bind(ID3D11DeviceContext* deviceContext)
{
	vertexShader.Bind(deviceContext);
	pixelShader.Bind(deviceContext);
	pixelShader.BindTextures(deviceContext);
	pixelShader.BindSamplerState(deviceContext);
}

ID3DBlob* DiffuseShader::ShaderBuffer()
{
	return vertexShader.ShaderBuffer();
}