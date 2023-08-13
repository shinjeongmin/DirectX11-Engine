#pragma once

#include <string>

#include <d3d11.h>
#include <Windows.h>

#include "Vector2f.h"
#include "Vector3f.h"

#include "Vertex.h"
#include "VertexUV.h"

// assimp ���̺귯�� include
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <vector>

class ResourceLoader
{
public:
	//static ID3D11ShaderResourceView* LoadTextureFromFile(
	//	ID3D11Device* device,
	//	std::wstring filename
	//);
	
	// �� �ε�
	static void LoadModel(std::string filename, std::vector<Vertex>* vertices);
	static void LoadModel(std::string filename, std::vector<VertexUV>* vertices);

	static std::wstring GetExtension(std::wstring str);

private:
	//static HRESULT GetScratchImage(
	//	std::wstring filename,
	//	DirectX::ScratchImage* image
	//);
};