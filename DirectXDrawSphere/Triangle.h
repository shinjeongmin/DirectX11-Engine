#pragma once
#include "Mesh.h"
class Triangle : public Mesh
{
public:
	Triangle();
	~Triangle();

	// ���� ���� �ʱ�ȭ �Լ� �������̵�.
	bool InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) override;
private:

};