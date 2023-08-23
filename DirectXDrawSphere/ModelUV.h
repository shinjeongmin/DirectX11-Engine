#pragma once
#include "Mesh.h"
#include <string>

class ModelUV : public Mesh
{
public:
	ModelUV();
	~ModelUV();

	// ���� ���� �ʱ�ȭ �Լ� �������̵�.
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) override;
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, std::string modelFileName);

private:
	void BindBuffers(ID3D11DeviceContext* deviceContext) override;

};