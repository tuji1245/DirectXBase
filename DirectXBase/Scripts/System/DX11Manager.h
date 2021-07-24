#pragma once
/**
* @file DirectX11Manager.h
* @breif DirectX11�̃}�l�[�W���[
* 
* @date 2021/04/08
* @author �җI��
*/

#include <windows.h>
// DirectX11�̃R���p�C��
#include <d3d11.h>
// �V�F�[�_�̃R���p�C��
#include <d3dcompiler.h>
// �Z�p���C�u����
#include <DirectXMath.h>
// DirectX�̃X�}�[�g�|�C���^
#include <wrl/client.h>
//
#include <string>
#include <vector>

// DirectXAPI�֌W�̃����N
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace std;
// ComPtr(DirectX�ł̃X�}�[�g�|�C���^)
using Microsoft::WRL::ComPtr;

// typedef
typedef ID3D11Buffer				ConstantBuffer, VertexBuffer, IndexBuffer, StructureBuffer;
typedef ID3D11InputLayout			InputLayout;
typedef ID3D11VertexShader			VertexShader;
typedef ID3D11GeometryShader		GeometryShader;
typedef ID3D11PixelShader			PixelShader;
typedef ID3D11ComputeShader			ComputeShader;
typedef ID3D11Texture2D				Texture2D;
typedef ID3D11ShaderResourceView	ShaderTexture;
typedef ID3D11UnorderedAccessView	ComputeOutputView;

#define SAFE_RELEASE(p) {if(p == nullptr){ p->Release(); p = nullptr; }}

constexpr RECT defWindowRECT = { 0,0,1270,760 };

/** 
* �������֐� 
*
* @param[in] hWnd
*/
HRESULT DXInit(HWND hWnd);
void DXUninit();
/**
* CreateVertexShader
*
* @param[in] const std::string& filename
* @param[in] const std::string& entrypath = ""
* @param[in] bool error = true
*/
ID3D11VertexShader* CreateVertexShader(const string& filename, const string& entrypath = "", bool error = true);
/**
* CreatePixelShader
*
* @param[in] const std::string& filename
* @param[in] const std::string& entrypath = ""
* @param[in] bool error = true
*/
ID3D11PixelShader*  CreatePixelShader(const string& filename, const string& entrypath = "", bool error = true);
/**
* CreateInputLayout
*
* @param[in] D3D11_INPUT_ELEMENT_DESC* layout
* @param[in] UINT elem_num
* @param[in] const std::string& filename
* @param[in] const std::string& entrypath = ""
*/
ID3D11InputLayout* CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const string& filename, const string& entrypath = "");

template<class x>
ID3D11Buffer* CreateVertexBuffer(x* VertexData, UINT VertexNum)
{
	// ���_�o�b�t�@�쐬	
	D3D11_BUFFER_DESC hBufferDesc;
	ZeroMemory(&hBufferDesc, sizeof(hBufferDesc));
	hBufferDesc.ByteWidth = sizeof(x) * VertexNum;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA hSubResourceData;
	ZeroMemory(&hSubResourceData, sizeof(hSubResourceData));
	hSubResourceData.pSysMem = VertexData;

	ID3D11Buffer* hpBuffer;
	if (FAILED(GetDevice()->CreateBuffer(&hBufferDesc, &hSubResourceData,&hpBuffer)))
	{
		return nullptr;
	}
	return hpBuffer;
}
ID3D11Buffer* CreateIndexBuffer(UINT* Index, UINT IndexNum);

// PipelineSetting
void SetInputLayout(ID3D11InputLayout* VertexLayout);
void SetVertexShader(ID3D11VertexShader* vs);
void SetPixelShader(ID3D11PixelShader* ps);

void SetVertexBuffer(ID3D11Buffer* VertexBuffer, UINT VertexSize);
void SetIndexBuffer(ID3D11Buffer* IndexBuffer);

void SetTexture2D(UINT RegisterNo, ID3D11ShaderResourceView* Texture);
	
void CreateRenderTarget();
void CleanupRenderTarget();

HWND GetWindow();
ID3D11Device* GetDevice();
ID3D11DeviceContext* GetContext();


void DrawBegin();
void DrawEnd();
void DrawIndexed(UINT VertexNum);

void ReSize(WPARAM wParam, LPARAM lParam);