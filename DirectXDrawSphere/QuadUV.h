#pragma once
#include "Mesh.h"

class QuadUV : public Mesh
{
public:
	QuadUV();
	~QuadUV();

	// ���� ���� �ʱ�ȭ �Լ� �������̵�.
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) override;

};