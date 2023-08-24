#pragma once
#include "Mesh.h"
#include <string>

class ModelPTN : public Mesh
{
public:
	ModelPTN();
	~ModelPTN();

	// ���� ���� �ʱ�ȭ �Լ� �������̵�.
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) override;
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, std::string modelFileName);
};