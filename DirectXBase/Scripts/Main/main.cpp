/**
* @file main.h
* @breif 
*
* @author �җI��
* @date 2021/06/28
* @details
*/
#include "main.h"
#include <System/DX11Manager.h>

#include <System/Input/input.h>
#include <System/Debug/DebugWindowManager.h>
#include <System/FrameManager.h>
#include <System/Debug/DemoImgui.h>

// macro
#ifdef _DEBUG
#define AllowImGui  // �����[�X�r���h��ImGui��\�����Ȃ�
#endif // _DEBUG

VertexShader* g_VS;
PixelShader* g_PS;
InputLayout* g_InputLayout;

VertexBuffer* g_VB;
//vector<UINT> idxs = { 0,1,2,0,2,3 };
vector<UINT> idxs = { 0, 3, 2, 0, 2, 1 };
IndexBuffer* g_IndexBuffer;

// Setup Dear ImGui context
DebugWindowManager* debugWindowManager;
FrameManagerWindow frameManager("frameManager");
DemoImgui demo("demo", false);

// ���_�����쐬
struct Vertex
{
    XMFLOAT3 pos;
    XMFLOAT4 col;
};
vector<Vertex> vertexs = {
    { XMFLOAT3(-0.5f,-0.5f,0.0f),XMFLOAT4(1,0,0,1) },
    { XMFLOAT3(0.5f,-0.5f,0.0f),XMFLOAT4(0,1,0,1) },
    { XMFLOAT3(0.5f, 0.5f,0.0f),XMFLOAT4(0,0,1,1) },
    { XMFLOAT3(-0.5f, 0.5f,0.0f),XMFLOAT4(0,0,0,1) },
};

HRESULT Initialize(HWND hwnd)
{
    // directx�̏�����
    if (FAILED(DXInit(hwnd)))
    {
        DXUninit();
        return E_FAIL;
    }
    debugWindowManager = new DebugWindowManager(hwnd, GetDevice(), GetContext());
    debugWindowManager->AddDebugWindow(&frameManager);
    debugWindowManager->AddDebugWindow(&demo);

    // Shadeer���쐬
    string ShaderFilePath = "Assets/Shaders/2DPipeLine.hlsl";
    g_VS = CreateVertexShader(ShaderFilePath, "vsMain");
    g_PS = CreatePixelShader(ShaderFilePath, "psMain");

    // InputLayout�̍쐬
    D3D11_INPUT_ELEMENT_DESC elem[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	0,  0,                           D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    g_InputLayout = CreateInputLayout(elem, 2, ShaderFilePath, "vsMain");


    g_VB = CreateVertexBuffer(vertexs.data(), static_cast<UINT>(vertexs.size()));

    // �C���f�b�N�X���̐ݒ�
    g_IndexBuffer = CreateIndexBuffer(idxs.data(), static_cast<UINT>(idxs.size()));

}
void Terminate()
{
    delete debugWindowManager;
    DXUninit();
}
void Update()
{
    frameManager.Update();
    KeyUpdate();    // Update�̍ŏ��ɌĂ�
    // �ȉ��ɃI�u�W�F�N�g����

}
void FixedUpdate()
{
    if (!frameManager.GetFlag()) return;
    // �ȉ��ɏ���
}
void Draw()
{
    DrawBegin();

    // �|���S���`��p�����[�^�Z�b�g
    SetVertexShader(g_VS);
    SetPixelShader(g_PS);
    SetInputLayout(g_InputLayout);

    SetVertexBuffer(g_VB, sizeof(Vertex));
    SetIndexBuffer(g_IndexBuffer);

    //DrawCall
    DrawIndexed(static_cast<UINT>(idxs.size()));

#ifdef AllowImGui
    debugWindowManager->Draw();
#endif // AllowImGui
    DrawEnd();

}